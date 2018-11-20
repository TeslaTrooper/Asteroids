#include "InternalLogic.h"

void InternalLogic::createInitialEntities() {
	this->player = entityHandler.createPlayer(Vec2(100, 350), 1.f);
	this->player->setVMax(5);

	GameObject* asteroid1 = entityHandler.create(Model::ASTEROID1, Vec2(0, 0), 1.f);
	asteroid1->setAngle(0);
	asteroid1->setVMax(2);
	asteroid1->setAcceleration(2);
	asteroid1->setDirection(Vec2(1, 1));

	GameObject* asteroid2 = entityHandler.create(Model::ASTEROID2, Vec2(150, 0), 1.f);
	asteroid2->setAngle(0);
	asteroid2->setVMax(2);
	asteroid2->setAcceleration(2);
	asteroid2->setDirection(Vec2(1, -1));

	GameObject* asteroid3 = entityHandler.create(Model::ASTEROID3, Vec2(300, 0), 1.f);
	asteroid3->setAngle(0);
	asteroid3->setVMax(2);
	asteroid3->setAcceleration(2);
	asteroid3->setDirection(Vec2(-1, 1));

	GameObject* asteroid4 = entityHandler.create(Model::ASTEROID4, Vec2(300, 300), 1.f);
	asteroid4->setAngle(0);
	asteroid4->setVMax(2);
	asteroid4->setAcceleration(2);
	asteroid4->setDirection(Vec2(-1, -1));

	GameObject* saucer = entityHandler.create(Model::SAUCER, Vec2(300, 450), 1.f);
	saucer->setAngle(0);
	saucer->setVMax(2);
	saucer->setAcceleration(2);
	saucer->setDirection(Vec2(1.f, 0.5f));
}

void InternalLogic::update(const float dt) {
	vector<GameObject*> objects = entityHandler.get();

	for each (GameObject* obj in objects) {
		obj->update(dt);
	}

	checkForOutOfBoundsObjects(objects);
}

void InternalLogic::checkForOutOfBoundsObjects(const vector<GameObject*> objects) const {
	for each (GameObject* obj in objects) {
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
}

vector<RenderUnit> InternalLogic::getRenderUnits() const {
	vector<RenderUnit> units;
	vector<GameObject*> entities = entityHandler.get();

	for each (GameObject* entity in entities) {
		units.push_back(entity->getRenderUnit());
	}

	return units;
}

