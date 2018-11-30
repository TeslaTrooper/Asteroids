#include "InternalLogic.h"

void InternalLogic::createInitialEntities() {
	createPlayer();

	//entityFactory.createAsteroid(Model::ASTEROID1, Vec2(), SIZE_LARGE, Vec2(2, 1));
	entityFactory.createSaucer(Vec2(300, 450), SIZE_MEDIUM, Vec2(1.f, 0.f));
}

void InternalLogic::update(const float dt) {
	vector<GameObject*> objects = entityFactory.get();

	physicsEngine.update(objects, dt);
	resolveColliions(objects);
	updateScore(objects);
	entityFactory.update();
	checkForMissingPlayer();

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
}

void InternalLogic::checkForOutOfBoundsObjects(GameObject* obj) const {
	Vec2 cPos = obj->getPosition();

	int x = (int) (WIN_WIDTH + cPos.x) % (int) WIN_WIDTH;
	int y = (int) (WIN_HEIGHT + cPos.y) % (int) WIN_HEIGHT;

	// It works, but it would be better, if we can get rid of these if-conditions
	// and replace it with some calculations

	// Update correspondig value, only if necessary
	if (cPos.x > WIN_WIDTH || cPos.x < 0)
		obj->setPosition(Vec2((float) x, cPos.y));

	cPos = obj->getPosition();

	if (cPos.y > WIN_HEIGHT || cPos.y < 0)
		obj->setPosition(Vec2(cPos.x, (float) y));
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
	entityFactory.createPlayerProjectile(position, SIZE_MEDIUM, movement);
}

void InternalLogic::resolveColliions(const vector<GameObject*> objects) {
	for each (GameObject* obj in objects) {
		if (!obj->hasIntersection()) {
			continue;
		}

		if (obj->getModelClass() == CLASS_ASTEROID) {
			breakAsteroidIntoPieces(obj);
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

	entityFactory.createAsteroid(randomAsteroidModel, position, childScale, childMovement);
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

		GameObject* intersector = obj->getIntersectingObject();
		ModelClass classOfObj = obj->getModelClass();
		ModelClass classOfIntersector = intersector->getModelClass();

		bool isShip = classOfObj == ModelClass::CLASS_SHIP;
		bool isPlayerProjectile = classOfObj == ModelClass::CLASS_PROJECTILE && obj->isPlayerProjectile();

		if (isShip || isPlayerProjectile) {
			if (classOfIntersector == ModelClass::CLASS_SAUCER) {
				score += intersector->getScale() == SIZE_MEDIUM ? 200 : 1000;
			}

			if (classOfIntersector == ModelClass::CLASS_ASTEROID) {
				if (intersector->getScale() == SIZE_LARGE) {
					score += 20;
				}
				if (intersector->getScale() == SIZE_MEDIUM) {
					score += 50;
				}
				if (intersector->getScale() == SIZE_SMALL) {
					score += 100;
				}
			}
		}
	}
}

void InternalLogic::createPlayer() {
	GameObject* player = entityFactory.createPlayerInCenter(SIZE_LARGE);
	lifes--;
}

void InternalLogic::checkForMissingPlayer() {
	if (entityFactory.getPlayer() == nullptr) {
		createPlayer();
	}
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
		if (!entity->isVisible())
			continue;

		units.push_back(entity->getRenderUnit());
	}

	return units;
}

