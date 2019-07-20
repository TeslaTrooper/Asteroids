#include "GameLogic.h"

void GameLogic::update(const float dt) {
	const vector<Entity*> entities = entityFactory->getAsEntities();
	printf("Entity count:%i\n", entities.size());

	physicsEngine.update(entities, dt);
	entityFactory->update();
	entitySpawner.update(dt);
	shipController.update(dt);
	soundPlayer.update(dt);
	checkForMissingPlayer(dt);

	const vector<GameObject*> objects = entityFactory->get();
	for each (GameObject* obj in objects)
		obj->update(dt);

	gameWorld.update(dt, entities);

	for each (Saucer* saucer in entityFactory->get(ModelClass::CLASS_SAUCER))
		checkSaucerBehaviour(saucer);

	checkSaucerSound(SIZE_LARGE);
	checkSaucerSound(SIZE_MEDIUM);
}

void GameLogic::checkForOutOfBoundsObjects(GameObject* obj) const {
	Vec2 cPos = obj->getPosition();
	// Take width as crop box for repositioning
	float a = ModelData::getCropBox(obj->getModelClass(), obj->getScale()).width;

	int x = (int) ((int) (WIN_WIDTH + cPos.x) % (int) WIN_WIDTH);
	int y = (int) ((int) (WIN_HEIGHT + cPos.y) % (int) WIN_HEIGHT);

	// It works, but it would be better, if we can get rid of these if-conditions
	// and replace it with some calculations

	// Update correspondig value, only if necessary
	if (cPos.x > WIN_WIDTH)
		obj->setPosition(Vec2((float) (x - a), cPos.y));
	if (cPos.x < -a)
		obj->setPosition(Vec2((float) (x + a), cPos.y));

	cPos = obj->getPosition();

	if (cPos.y > WIN_HEIGHT)
		obj->setPosition(Vec2(cPos.x, (float) (y - a)));
	if (cPos.y < -a)
		obj->setPosition(Vec2(cPos.x, (float) (y + a)));
}

void GameLogic::shipShoot() {
	// Prevent player from shooting more than MAX_PROJECTILE entities
	if (entityFactory->getPlayerProjectileCount() >= MAX_PROJECTILE)
		return;

	Ship* player = (Ship*) entityFactory->getPlayer();
	if (player == nullptr || player->isInHyperspace())
		return;

	// Determine position of player head for new projectile
	Vec2 shipHead = Vec2(ModelData::shipVertices[2], ModelData::shipVertices[3]);
	Vec2 transformedHead = player->getRenderUnit().transformation.transform(shipHead);
	Vec2 shipDirection = Vec2::getRotatedInstance(player->getAngle());
	Vec2 position = transformedHead + (shipDirection * GAP_PROJECTILE_SHIP);

	// Calculate movement vector
	Vec2 movement = shipDirection.mul(PROJECTILE_SPEED + player->getMovement().length());

	// Create projectile
	entityFactory->createPlayerProjectile(position, SIZE_MEDIUM, movement);

	soundPlayer.playFire();
}

void GameLogic::resolveCollision(Entity* e1, Entity* e2, const Vec2& location) const {
	GameObject* o1 = (GameObject*) e1;
	GameObject* o2 = (GameObject*) e2;

	if (o1->getModelClass() == CLASS_ASTEROID)
		breakAsteroidIntoPieces(o1);

	if (o2->getModelClass() == CLASS_ASTEROID)
		breakAsteroidIntoPieces(o2);

	if (o1->getModelClass() == ModelClass::CLASS_SHIP || o2->getModelClass() == ModelClass::CLASS_SHIP)
		entityFactory->createShipParticleEffect(location);
	else
		entityFactory->createSimpleParticleEffect(location);

	updateScore(o1, o2);

	o1->markForCleanup();
	o2->markForCleanup();
}

void GameLogic::breakAsteroidIntoPieces(GameObject const * const object) const {
	soundPlayer.playBang(object->getScale());

	if (object->getScale() <= SIZE_SMALL)
		return;

	for (int i = 0; i < ASTEROID_PIECE_COUNT; i++)
		createAsteroidPiece(object);
}

void GameLogic::createAsteroidPiece(GameObject const * const object) const {
	Vec2 position = object->getPosition();
	Vec2 parentMovement = object->getMovement();

	Vec2 childMovement = calcMovementOfChildAsteroid(parentMovement);
	Model randomAsteroidModel = (Model) random(0, 3);
	float childScale = object->getScale() - 0.5f;

	entityFactory->createAsteroid(randomAsteroidModel, position, childScale, childMovement);
}

Vec2 GameLogic::calcMovementOfChildAsteroid(const Vec2 parentMovement) const {
	// We want a movement, which has similar direction related to parent movemnt
	// and some small change in velocity (slower or faster is possible)

	// First, let's define a random rotation in a predefined zone
	Mat4 rotation = Mat4::rotateZ((float) random(-ROTATION_ZONE, ROTATION_ZONE));
	// Apply it to parent movement
	Vec2 rotatedMovement = rotation.transform(parentMovement);

	// Next step is to change velocity
	// To keep it simple, the new velocity is just a random number
	int randomVelocity = random(ASTEROID_MIN_VELOCITY, ASTEROID_MAX_VELOCITY);

	return rotatedMovement.norm() * randomVelocity;
}

// TODO
void GameLogic::updateScore(const GameObject* const o1, const GameObject* const o2) const {
	// When does the current score need to be updated?
	// - Intersection Asteroid <-> Projectile (player)
	// - Intersection Asteroid <-> Ship
	// - Intersection Saucer <-> Projectile (player)
	// - Intersection Saucer <-> Ship

	// Scoring only makes sense, if the ship or a player-projectile 
	// is involved in the collision.

	ModelClass c1 = o1->getModelClass();
	ModelClass c2 = o2->getModelClass();

	bool c1IsShip = c1 == ModelClass::CLASS_SHIP;
	bool c2IsShip = c2 == ModelClass::CLASS_SHIP;
	bool o1IsPlayerProjectile = o1->isPlayerProjectile() && o1->getModelClass() == ModelClass::CLASS_PROJECTILE;
	bool o2IsPlayerProjectile = o2->isPlayerProjectile() && o2->getModelClass() == ModelClass::CLASS_PROJECTILE;

	// Make sure, we have a valid collision, which affects current score
	// This is only the case, if either the ship, or the ship projectile has intersection
	// XOR operator prevents scoring, if player hits own ship.
	if ((c1IsShip || c2IsShip) ^ (o1IsPlayerProjectile || o2IsPlayerProjectile)) {
		int gain = 0;

		if (c1IsShip || o1IsPlayerProjectile)
			gain = determineGainedScore(o2->getScale(), c2);

		if (c2IsShip || o2IsPlayerProjectile)
			gain = determineGainedScore(o1->getScale(), c1);

		stats->score += gain;
		printf("Gain: %i\n", gain);

		updateRemainingLifes();
	}
}

int GameLogic::determineGainedScore(const float objSize, const ModelClass classOfIntersector) const {
	int gainedScore = 0;

	if (classOfIntersector == ModelClass::CLASS_SAUCER)
		gainedScore = objSize == SIZE_MEDIUM ? SCORE_MEDIUM_SAUCER : SCORE_LARGE_SAUCER;

	if (classOfIntersector == ModelClass::CLASS_ASTEROID) {
		if (objSize == SIZE_LARGE) {
			gainedScore = SCORE_LARGE_ASTEROID;
		}
		if (objSize == SIZE_MEDIUM) {
			gainedScore = SCORE_MEDIUM_ASTEROID;
		}
		if (objSize == SIZE_SMALL) {
			gainedScore = SCORE_SMALL_ASTEROID;
		}
	}

	return gainedScore;
}

void GameLogic::updateRemainingLifes() const {
	// Every LIFE_PER_SCORE points, player gains one extra life
	if (stats->score >= stats->lifePerScore) {
		stats->lifes++;
		stats->lifePerScore += LIFE_PER_SCORE;
		soundPlayer.playExtraShip();
	}
}

void GameLogic::checkForMissingPlayer(const float dt) {
	if (entityFactory->getPlayer() == nullptr)
		playerIsMissing = true;

	if (playerIsMissing)
		shipCreationCtr -= dt;

	if (shipCreationCtr <= 0) {
		playerIsMissing = false;
		shipCreationCtr = PLAYER_CREATION_DELAY;

		createPlayer();
	}
}

void GameLogic::createPlayer() {
	entityFactory->createPlayerInCenter(SIZE_LARGE);
	stats->lifes--;
}

void GameLogic::checkSaucerBehaviour(Saucer* saucer) {
	if (!saucer->canShoot())
		return;

	// Calculate center of player ship mx, my
	GameObject* player = entityFactory->getPlayer();
	if (player == nullptr)
		return;

	Vec2 p1 = Vec2(ModelData::shipVertices[0], ModelData::shipVertices[1]);
	Vec2 p2 = Vec2(ModelData::shipVertices[2], ModelData::shipVertices[3]);
	Vec2 p3 = Vec2(ModelData::shipVertices[4], ModelData::shipVertices[5]);

	Mat4 transformation = player->getTransformation();

	p1 = transformation.transform(p1);
	p2 = transformation.transform(p2);
	p3 = transformation.transform(p3);

	float mx = (p1.x + p2.x + p3.x) / 3;
	float my = (p1.y + p2.y + p3.y) / 3;

	ProjectileParams params = saucer->getProjectileParams(Vec2(mx, my));

	// Create projectile
	entityFactory->createSaucerProjectile(params.position, SIZE_MEDIUM, params.movement);
}

void GameLogic::checkSaucerSound(const float size) const {
	if (entityFactory->saucerExist(size))
		soundPlayer.playSaucer(size);
	else
		soundPlayer.stopSaucer(size);
}

void GameLogic::rotatePlayerLeft(const float dt) {
	shipController.rotatePlayerLeft(dt);
}

void GameLogic::rotatePlayerRight(const float dt) {
	shipController.rotatePlayerRight(dt);
}

void GameLogic::moveShip(const bool moving, const float dt) {
	shipController.moveShip(moving, dt);

	Ship* player = (Ship*) entityFactory->getPlayer();
	if (moving && player != nullptr && !player->isInHyperspace())
		soundPlayer.playThrust();
	else
		soundPlayer.stopThrust();
}

void GameLogic::hyperspace() {
	shipController.hyperspace();
}

vector<RenderUnit> GameLogic::getRenderUnits() const {
	vector<RenderUnit> units;
	vector<GameObject*> entities = entityFactory->get();

	for each (GameObject* entity in entities) {
		if (!entity->isVisible())
			continue;

		units.push_back(entity->getRenderUnit());
	}

	return units;
}

