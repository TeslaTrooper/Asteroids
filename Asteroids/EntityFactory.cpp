#include "EntityFactory.h"

EntityFactory::EntityFactory() {
	entities[ModelClass::CLASS_ASTEROID] = vector<GameObject*>();
	entities[ModelClass::CLASS_PROJECTILE] = vector<GameObject*>();
	entities[ModelClass::CLASS_SAUCER] = vector<GameObject*>();
	entities[ModelClass::CLASS_SHIP] = vector<GameObject*>();
}

void EntityFactory::update() {
	vector<GameObject*> objects = linearizeMap();

	for each (GameObject* obj in objects) {
		if (!obj->isAlive()) {
			remove(obj);
		}
	}
}

GameObject* EntityFactory::create(const Model model, const Vec2 position, const float size) {
	GameObject* object = new GameObject(model, position, size);
	entities[object->getModelClass()].push_back(object);

	return object;
}

GameObject* EntityFactory::createPlayer(const Vec2 position, const float size) {
	GameObject* object = new Ship(position, size);
	entities[object->getModelClass()].push_back(object);

	return object;
}

GameObject* EntityFactory::createStatic(const Model model, const Vec2 position, const float size, const Vec2 movement) {
	GameObject* object = new GameObject(model, position, size);
	object->setAngle(0);
	object->setVMax(movement.length());
	object->setAcceleration(1);
	object->setDirection(movement.norm());
	object->setMovement(movement);

	entities[object->getModelClass()].push_back(object);

	return object;
}

vector<GameObject*> EntityFactory::get() const {
	return linearizeMap();
}

GameObject* EntityFactory::getPlayer() const {
	vector<GameObject*> playerVector = entities.at(ModelClass::CLASS_SHIP);

	if (playerVector.size() == 0) {
		printf("No player created!");
		return nullptr;
	}

	return playerVector.at(0);
}

vector<GameObject*> EntityFactory::get(const ModelClass modelClass) const {
	return entities.at(modelClass);
}

void EntityFactory::clear() {
	linearizeMap().clear();
}

vector<GameObject*> EntityFactory::linearizeMap() const {
	vector<GameObject*> result;

	for (const pair<ModelClass, vector<GameObject*>>& pair : entities) {
		for each (GameObject* obj in pair.second) {
			result.push_back(obj);
		}
	}

	return result;
}

void EntityFactory::remove(GameObject* object) {
	vector<GameObject*>* vec = &entities.at(object->getModelClass());

	auto it = std::find(vec->begin(), vec->end(), object);
	if (it != vec->end())
		vec->erase(it);
}