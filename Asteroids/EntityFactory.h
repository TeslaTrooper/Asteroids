#ifndef ENTITY_HANDLER
#define ENTITY_HANDLER

#include <vector>

#include "GameObject.h"
#include "Ship.h"
#include "Util.h"

class EntityFactory {

	map<ModelClass, vector<GameObject*>> entities;

	vector<GameObject*> linearizeMap() const;
	void remove(GameObject* object);

public:
	EntityFactory();
	~EntityFactory() {};

	void update();

	GameObject* create(const Model model, const Vec2 position, const float size);
	GameObject* createPlayer(const Vec2 position, const float size);

	void clear();
	vector<GameObject*> get() const;
	GameObject* getPlayer() const;
	vector<GameObject*> get(const ModelClass modelClass) const;
};

#endif ENTITY_HANDLER