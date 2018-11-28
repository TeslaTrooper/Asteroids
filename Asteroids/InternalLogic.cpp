#include "InternalLogic.h"

void InternalLogic::createInitialEntities() {
	GameObject* player = entityFactory.createPlayer(Vec2(100, 350), SIZE_LARGE);
	player->setVMax(5);

	entityFactory.createStatic(Model::ASTEROID1, Vec2(), SIZE_LARGE, Vec2(2, 1));

	/*GameObject* asteroid2 = entityFactory.create(Model::ASTEROID2, Vec2(150, 0), SIZE_SMALL);
	asteroid2->setAngle(0);
	asteroid2->setVMax(2);
	asteroid2->setAcceleration(2);
	asteroid2->setDirection(Vec2(1, -1));

	GameObject* asteroid3 = entityFactory.create(Model::ASTEROID3, Vec2(300, 0), SIZE_MEDIUM);
	asteroid3->setAngle(0);
	asteroid3->setVMax(2);
	asteroid3->setAcceleration(2);
	asteroid3->setDirection(Vec2(-1, 1));

	GameObject* asteroid4 = entityFactory.create(Model::ASTEROID4, Vec2(300, 300), SIZE_MEDIUM);
	asteroid4->setAngle(0);
	asteroid4->setVMax(2);
	asteroid4->setAcceleration(2);
	asteroid4->setDirection(Vec2(-1, -1));

	GameObject* saucer = entityFactory.create(Model::SAUCER, Vec2(300, 450), SIZE_MEDIUM);
	saucer->setAngle(0);
	saucer->setVMax(2);
	saucer->setAcceleration(2);
	saucer->setDirection(Vec2(1.f, 0.5f));*/
}

void InternalLogic::update(const float dt) {
	vector<GameObject*> objects = entityFactory.get();

	physicsEngine.update(objects, dt);
	resolveColliions(objects);
	entityFactory.update();

	for each (GameObject* obj in objects) {
		obj->update(dt);
	}

	for each (GameObject* projectile in entityFactory.get(ModelClass::CLASS_PROJECTILE)) {
		markForCleanupIfRequired(projectile);
	}

	for each (GameObject* obj in objects) {
		checkForOutOfBoundsObjects(obj);
	}
}

void InternalLogic::markForCleanupIfRequired(GameObject* obj) {
	if (obj->getLifetime() >= PROJECTILE_MAX_LIFETIME) {
		obj->markForCleanup();
	}

	if (obj->hasIntersection()) {
		obj->markForCleanup();
	}
}

void InternalLogic::checkForOutOfBoundsObjects(GameObject* obj) const {
	// Modulo operator only works with intergers
	// Cast from float to int required -> information loss
	// Causes small "jumps" in repositioning
	// => Precision value needed to keep more digits
	const int precision = 100000;

	float w = windowSize.width * precision;
	float h = windowSize.height * precision;
	float cx = obj->getPosition().x * precision;
	float cy = obj->getPosition().y * precision;

	int x = (int) (w + cx) % (int) w;
	int y = (int) (h + cy) % (int) h;

	obj->setPosition(Vec2((float) x / (float) precision, (float) y / (float) precision));
}

void InternalLogic::shipShoot() {
	// Prevent player from shooting more than MAX_PROJECTILE entities
	if (entityFactory.get(ModelClass::CLASS_PROJECTILE).size() >= MAX_PROJECTILE) {
		return;
	}

	GameObject* player = entityFactory.getPlayer();
	// Determine position of player head for new projectile
	Vec2 shipHead = Vec2(ModelData::shipVertices[2], ModelData::shipVertices[3]);
	Vec2 transformedHead = player->getRenderUnit().transformation.transform(shipHead);
	Vec2 shipDirection = Vec2::getRotatedInstance(player->getAngle());
	Vec2 position = transformedHead + GAP_PROJECTILE_SHIP * shipDirection;

	// Calculate movement vector
	Vec2 movement = shipDirection.mul(PROJECTILE_SPEED);

	// Create projectile
	entityFactory.createStatic(Model::PROJECTILE, position, 1, movement);
}

void InternalLogic::resolveColliions(const vector<GameObject*> objects) {
	for each (GameObject* obj in objects) {
		if (!obj->hasIntersection() || obj->getModelClass() == ModelClass::CLASS_SHIP) {
			continue;
		}

		if (obj->getModelClass() == CLASS_ASTEROID) {
			breakAsteroidIntoPieces(obj);
		}

		updateScore();
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

	entityFactory.createStatic(randomAsteroidModel, position, childScale, childMovement);
}

Vec2 InternalLogic::calcMovementOfChildAsteroid(const Vec2 parentMovement) const {
	// We want a movement, which has similar direction related to parent movemnt
	// and some small change in velocity (slower or faster is possible)

	// First, let's define a random rotation in a predefined zone
	Mat4 rotation = Mat4::rotateZ(random(-ROTATION_ZONE, ROTATION_ZONE));
	// Apply it to parent movement
	Vec2 rotatedMovement = rotation.transform(parentMovement);

	// Next step is to change velocity
	// To keep it simple, the new velocity is just a random number
	int randomVelocity = random(MIN_VELOCITY, MAX_VELOCITY);
	float velocity = randomVelocity / 10.f;

	return rotatedMovement.norm().mul(velocity);
}

// TODO
void InternalLogic::updateScore() {
	// When does the current score need to be updated?
	// - Intersection Asteroid <-> Projectile (player)
	// - Intersection Asteroid <-> Ship
	// - Intersection Saucer <-> Projectile (player)
	// - Intersection Saucer <-> Ship

	// We need to know, which objects had a collision
	// Currently, we only know, if a single entity had a collision, or not.
	// So we have to store at collision time, which objects caused that collision

	// Maybe there is another way, to recognize that - without any complex collision-info-storage-stuff
}

void InternalLogic::rotatePlayerLeft(const float dt) {
	GameObject* player = entityFactory.getPlayer();

	if (player == nullptr) {
		return;
	}

	player->rotate(GameObject::NEGATIVE_ROTATION, dt);
};

void InternalLogic::rotatePlayerRight(const float dt) {
	GameObject* player = entityFactory.getPlayer();

	if (player == nullptr) {
		return;
	}

	player->rotate(GameObject::POSITIVE_ROTATION, dt);
};

void InternalLogic::moveShip(const bool moving, const float dt) {
	GameObject* player = entityFactory.getPlayer();

	if (player == nullptr) {
		return;
	}

	player->setAcceleration(moving ? 1.f : 0.f);
};

vector<RenderUnit> InternalLogic::getRenderUnits() const {
	vector<RenderUnit> units;
	vector<GameObject*> entities = entityFactory.get();

	for each (GameObject* entity in entities) {
		units.push_back(entity->getRenderUnit());
	}

	return units;
}

