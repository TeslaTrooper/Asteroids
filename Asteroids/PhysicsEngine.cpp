#include "PhysicsEngine.h"

void PhysicsEngine::update(const vector<GameObject*> objects, const float dt) const {
	updatePosition(objects, dt);
	// checkCollisions
	updateSpeed(objects, dt);
}

void PhysicsEngine::updatePosition(const vector<GameObject*> objects, const float dt) const {
	for each (GameObject* obj in objects) {
		// Fetch all data for physx calculations
		Vec2 position = obj->getPosition();
		Vec2 direction = obj->getDirection();
		float currentSpeed = obj->getSpeed();

		// v = dv * currentSpeed 
		Vec2 movement = currentSpeed * direction;

		// update position: pn = pn-1+vn-1
		obj->setPosition(position + movement);
	}
}

void PhysicsEngine::updateSpeed(const vector<GameObject*> objects, const float dt) const {
	for each (GameObject* obj in objects) {
		// Fetch all data for physx calculations
		float currentSpeed = obj->getSpeed();
		float acceleration = obj->getAcceleration();

		if (currentSpeed >= obj->getVMax()) {
			continue;
		}

		// dv = a * t
		float deltaSpeed = acceleration * dt;
		obj->setSpeed(currentSpeed + deltaSpeed);
	}
}