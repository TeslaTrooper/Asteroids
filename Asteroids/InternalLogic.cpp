#include "InternalLogic.h"

void InternalLogic::createInitialEntities() {
	GameObject* player = entityFactory.createPlayer(Vec2(100, 350), 1);
	player->setVMax(5);

	GameObject* asteroid1 = entityFactory.create(Model::ASTEROID1, Vec2(0, 0), 1.f);
	asteroid1->setAngle(0);
	asteroid1->setVMax(2);
	asteroid1->setAcceleration(2);
	asteroid1->setDirection(Vec2(1, 1));

	GameObject* asteroid2 = entityFactory.create(Model::ASTEROID2, Vec2(150, 0), 1.f);
	asteroid2->setAngle(0);
	asteroid2->setVMax(2);
	asteroid2->setAcceleration(2);
	asteroid2->setDirection(Vec2(1, -1));

	GameObject* asteroid3 = entityFactory.create(Model::ASTEROID3, Vec2(300, 0), 1.f);
	asteroid3->setAngle(0);
	asteroid3->setVMax(2);
	asteroid3->setAcceleration(2);
	asteroid3->setDirection(Vec2(-1, 1));

	GameObject* asteroid4 = entityFactory.create(Model::ASTEROID4, Vec2(300, 300), 1.f);
	asteroid4->setAngle(0);
	asteroid4->setVMax(2);
	asteroid4->setAcceleration(2);
	asteroid4->setDirection(Vec2(-1, -1));

	GameObject* saucer = entityFactory.create(Model::SAUCER, Vec2(300, 450), 1.f);
	saucer->setAngle(0);
	saucer->setVMax(2);
	saucer->setAcceleration(2);
	saucer->setDirection(Vec2(1.f, 0.5f));
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
		observeProjectiles(projectile);
	}

	for each (GameObject* obj in objects) {
		checkForOutOfBoundsObjects(obj);
	}
}

void InternalLogic::observeProjectiles(GameObject* obj) {
	if (obj->getLifetime() >= PROJECTILE_MAX_LIFETIME) {
		obj->markForCleanup();
	}

	if (obj->hasIntersection()) {
		obj->markForCleanup();
	}
}

void InternalLogic::checkForOutOfBoundsObjects(GameObject* obj) const {
	if (obj->getPosition().x >= windowSize.width) {
		obj->setPosition(Vec2(0.f, obj->getPosition().y));
	}
	if (obj->getPosition().x < 0) {
		obj->setPosition(Vec2((float) windowSize.width, obj->getPosition().y));
	}
	if (obj->getPosition().y >= windowSize.height) {
		obj->setPosition(Vec2(obj->getPosition().x, 0.f));
	}
	if (obj->getPosition().y < 0) {
		obj->setPosition(Vec2(obj->getPosition().x, windowSize.height));
	}
}

void InternalLogic::shipShoot() {
	if (entityFactory.get(ModelClass::CLASS_PROJECTILE).size() >= MAX_PROJECTILE) {
		return;
	}

	GameObject* player = entityFactory.getPlayer();
	Vec2 shipHead = Vec2(ModelData::shipVertices[2], ModelData::shipVertices[3]);
	Vec2 transformedHead = player->getRenderUnit().transformation.transform(shipHead);
	Vec2 shipDirection = Vec2::getRotatedInstance(player->getAngle());
	Vec2 position = transformedHead + GAP_PROJECTILE_SHIP * shipDirection;

	GameObject* projectile = entityFactory.create(Model::PROJECTILE, position, 1);
	projectile->setAngle(player->getAngle());
	projectile->setDirection(shipDirection);
	projectile->setVMax(PROJECTILE_SPEED);
	projectile->setAcceleration(1);
	projectile->setMovement(shipDirection.mul(PROJECTILE_SPEED));
}

void InternalLogic::resolveColliions(const vector<GameObject*> objects) {
	for each (GameObject* obj in objects) {
		if (!obj->hasIntersection()) {
			continue;
		}

		obj->setAcceleration(0);
		obj->setMovement(Vec2());
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
		units.push_back(entity->getRenderUnit());
	}

	return units;
}

