#ifndef SHIP_CLASS
#define SHIP_CLASS

#include "GameObject.h"

#define ANIMATION_SPEED 0.05f

class Ship : public GameObject {

	void updateMoveAnimation(const float dt);

public:
	Ship(const Vec2 position, const float scale) : GameObject(Model::SHIP, position, scale) {};
	~Ship() { GameObject::~GameObject(); };

	// @Override
	void update(const float dt);
};

#endif SHIP_CLASS
