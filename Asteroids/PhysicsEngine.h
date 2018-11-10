#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <vector>
#include "GameObject.h"

class PhysicsEngine {

	void updatePosition(const vector<GameObject*> objects, const float dt) const;
	void updateSpeed(const vector<GameObject*> objects, const float dt) const;

public:
	PhysicsEngine() {};
	~PhysicsEngine() {};

	void update(const vector<GameObject*> objects, const float dt) const;

};

#endif PHYSICS_ENGINE