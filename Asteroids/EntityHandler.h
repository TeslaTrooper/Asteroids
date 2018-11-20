#ifndef ENTITY_HANDLER
#define ENTITY_HANDLER

#include <vector>

#include "GameObject.h"
#include "Ship.h"
#include "Util.h"

class EntityHandler {

	vector<GameObject*> gameObjects;

public:
	EntityHandler() {};
	~EntityHandler() {};

	GameObject* create(const Model model, const Vec2 position, const float size);
	GameObject* createPlayer(const Vec2 position, const float size);

	void clear();
	vector<GameObject*> get() const;
};

#endif ENTITY_HANDLER