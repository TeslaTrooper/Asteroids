#include "InternalLogic.h"

void InternalLogic::update(const float dt) {
	vector<GameObject*> objects = entityFactory->get();

	physicsEngine.update(objects, dt);
	resolveColliions(objects);
	updateScore(objects);
	entityFactory->update();
	checkForMissingPlayer(dt);

	for each (GameObject* obj in objects) {
		obj->update(dt);
	}

	for each (GameObject* obj in objects) {
		checkForOutOfBoundsObjects(obj);
	}

	for each (Saucer* saucer in entityFactory->get(ModelClass::CLASS_SAUCER)) {
		checkSaucerBehaviour(saucer);
	}

	entitySpawner.update(dt);
	shipController.update(dt);
}

void InternalLogic::checkForOutOfBoundsObjects(GameObject* obj) const {
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

void InternalLogic::shipShoot() {
	// Prevent player from shooting more than MAX_PROJECTILE entities
	if (entityFactory->getPlayerProjectileCount() >= MAX_PROJECTILE) {
		return;
	}

	Ship* player = (Ship*) entityFactory->getPlayer();
	if (player == nullptr || player->isInHyperspace())
		return;

	// Determine position of player head for new projectile
	Vec2 shipHead = Vec2(ModelData::shipVertices[2], ModelData::shipVertices[3]);
	Vec2 transformedHead = player->getRenderUnit().transformation.transform(shipHead);
	Vec2 shipDirection = Vec2::getRotatedInstance(player->getAngle());
	Vec2 position = transformedHead + GAP_PROJECTILE_SHIP * shipDirection;

	// Calculate movement vector
	Vec2 movement = shipDirection.mul(PROJECTILE_SPEED + player->getMovement().length());

	// Create projectile
	entityFactory->createPlayerProjectile(position, SIZE_MEDIUM, movement);
}

void InternalLogic::resolveColliions(const vector<GameObject*> objects) {
	for each (GameObject* obj in objects) {
		if (!obj->hasIntersection()) {
			continue;
		}

		if (obj->getModelClass() == CLASS_ASTEROID) {
			breakAsteroidIntoPieces(obj);
		}

		if (obj->getModelClass() == ModelClass::CLASS_SHIP) {
			entityFactory->createShipParticleEffect(obj->getCollisionInfo().collisionLocation);
		} else {
			entityFactory->createSimpleParticleEffect(obj->getCollisionInfo().collisionLocation);
		}

		obj->markForCleanup();
	}
}

void InternalLogic::breakAsteroidIntoPieces(GameObject const * const object) {
	if (object->getScale() <= SIZE_SMALL) {
		return;
	}

	for (int i = 0; i < ASTEROID_PIECE_COUNT; i++) {
		createAsteroidPiece(object);
	}
}

void InternalLogic::createAsteroidPiece(GameObject const * const object) {
	Vec2 position = object->getPosition();
	Vec2 parentMovement = object->getMovement();

	Vec2 childMovement = calcMovementOfChildAsteroid(parentMovement);
	Model randomAsteroidModel = (Model) random(0, 3);
	float childScale = object->getScale() - 0.5f;

	entityFactory->createAsteroid(randomAsteroidModel, position, childScale, childMovement);
}

Vec2 InternalLogic::calcMovementOfChildAsteroid(const Vec2 parentMovement) const {
	// We want a movement, which has similar direction related to parent movemnt
	// and some small change in velocity (slower or faster is possible)

	// First, let's define a random rotation in a predefined zone
	Mat4 rotation = Mat4::rotateZ((float) random(-ROTATION_ZONE, ROTATION_ZONE));
	// Apply it to parent movement
	Vec2 rotatedMovement = rotation.transform(parentMovement);

	// Next step is to change velocity
	// To keep it simple, the new velocity is just a random number
	int randomVelocity = random(ASTEROID_MIN_VELOCITY, ASTEROID_MAX_VELOCITY);
	float velocity = randomVelocity / 10.f;

	return rotatedMovement.norm().mul(velocity);
}

// TODO
void InternalLogic::updateScore(const vector<GameObject*> objects) {
	// When does the current score need to be updated?
	// - Intersection Asteroid <-> Projectile (player)
	// - Intersection Asteroid <-> Ship
	// - Intersection Saucer <-> Projectile (player)
	// - Intersection Saucer <-> Ship

	// We need to know, which objects had a collision
	// Currently, we only know, if a single entity had a collision, or not.
	// So we have to store at collision time, which objects caused that collision

	// Maybe there is another way, to recognize that - without any complex collision-info-storage-stuff

	for each (GameObject* obj in objects) {
		if (!obj->hasIntersection()) {
			continue;
		}

		CollisionInfo intersector = obj->getCollisionInfo();
		ModelClass classOfObj = obj->getModelClass();
		ModelClass classOfIntersector = intersector.classOfObj;

		bool isShip = classOfObj == ModelClass::CLASS_SHIP;
		bool isPlayerProjectile = classOfObj == ModelClass::CLASS_PROJECTILE && obj->isPlayerProjectile();

		// Make sure, we have a valid collision, which affects current score
		// This is only the case, if either the ship, or the ship projectile has intersection
		if (isShip || isPlayerProjectile) {
			score += determineGainedScore(intersector.objSize, classOfIntersector);

			updateRemainingLifes();
		}
	}
}

float InternalLogic::determineGainedScore(const float objSize, const ModelClass classOfIntersector) {
	float gainedScore = 0;

	if (classOfIntersector == ModelClass::CLASS_SAUCER) {
		gainedScore = objSize == SIZE_MEDIUM ? SCORE_MEDIUM_SAUCER : SCORE_SMALL_SAUCER;
	}

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

void InternalLogic::updateRemainingLifes() {
	// Every LIFE_PER_SCORE points, player gains one extra life
	if (score >= lifePerScore) {
		lifes++;
		lifePerScore += LIFE_PER_SCORE;
	}
}

void InternalLogic::checkForMissingPlayer(const float dt) {
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

void InternalLogic::createPlayer() {
	entityFactory->createPlayerInCenter(SIZE_LARGE);
	lifes--;
}

void InternalLogic::checkSaucerBehaviour(Saucer* saucer) {
	if (!saucer->canShoot()) {
		return;
	}

	// Calculate center of player ship mx, my
	GameObject* player = entityFactory->getPlayer();
	if (player == nullptr)
		return;


	Vec2 p1 = Vec2(ModelData::shipVertices[0], ModelData::shipVertices[1]);
	Vec2 p2 = Vec2(ModelData::shipVertices[2], ModelData::shipVertices[3]);
	Vec2 p3 = Vec2(ModelData::shipVertices[4], ModelData::shipVertices[5]);

	Mat4 transformation = player->getRenderUnit().transformation;

	p1 = transformation.transform(p1);
	p2 = transformation.transform(p2);
	p3 = transformation.transform(p3);

	float mx = (p1.x + p2.x + p3.x) / 3;
	float my = (p1.y + p2.y + p3.y) / 3;

	ProjectileParams params = saucer->getProjectileParams(Vec2(mx, my));

	// Create projectile
	entityFactory->createSaucerProjectile(params.position, SIZE_MEDIUM, params.movement);
}

void InternalLogic::rotatePlayerLeft(const float dt) {
	shipController.rotatePlayerLeft(dt);
}

void InternalLogic::rotatePlayerRight(const float dt) {
	shipController.rotatePlayerRight(dt);
}

void InternalLogic::moveShip(const bool moving, const float dt) {
	shipController.moveShip(moving, dt);
}

void InternalLogic::hyperspace() {
	shipController.hyperspace();
}

vector<RenderUnit> InternalLogic::getRenderUnits() const {
	vector<RenderUnit> units;
	vector<GameObject*> entities = entityFactory->get();

	for each (GameObject* entity in entities) {
		if (!entity->isVisible())
			continue;

		units.push_back(entity->getRenderUnit());
	}

	return units;
}

