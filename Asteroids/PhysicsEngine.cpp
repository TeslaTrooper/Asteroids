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
		Vec2 movement = obj->getMovement();

		// v = dv * currentSpeed

		// update position: pn = pn-1+vn-1
		obj->setPosition(position + movement);
	}
}

void PhysicsEngine::updateSpeed(const vector<GameObject*> objects, const float dt) const {
	for each (GameObject* obj in objects) {
		// Fetch all data for physx calculations
		Vec2 movement = obj->getMovement();
		float acceleration = obj->getAcceleration();

		Vec2 acc;

		if (acceleration == 0) {
			// Calculate a "friction-like" acceleration
			acc = movement.inv().mul(0.5f);
			//acceleration = movement.length() / 2;
			//acceleration = -acceleration;
		} else {
			acc = acceleration * obj->getDirection();
		}

		// dv = a * t
		Vec2 deltaSpeed = acc * dt;
		Vec2 resultSpeed = movement + deltaSpeed;

		if (resultSpeed.length() >= obj->getVMax()) {
			resultSpeed = resultSpeed.norm() * obj->getVMax();
		}
		
		obj->setMovement(resultSpeed);
	}
}