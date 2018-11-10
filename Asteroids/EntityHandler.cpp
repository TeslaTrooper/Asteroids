#include "EntityHandler.h"

GameObject* EntityHandler::create(const Model model, const Vec2 position, const float size) {
	GameObject* object = new GameObject(model, position, size);
	gameObjects.push_back(object);

	return object;
}

vector<GameObject*> EntityHandler::get() {
	return gameObjects;
}

void EntityHandler::clear() {
	gameObjects.clear();
}