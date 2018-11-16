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

		// update position: pn = pn-1+vn-1
		obj->setPosition(position + movement);
	}
}

void PhysicsEngine::updateSpeed(const vector<GameObject*> objects, const float dt) const {
	for each (GameObject* obj in objects) {
		// Fetch all data for physx calculations
		Vec2 movement = obj->getMovement();
		float acceleration = obj->getAcceleration();
		
		// Friction is an acceleration pointing in the opposite direction of current movement
		Vec2 friction = movement.inv().mul(0.5f);
		Vec2 directionalAcceleration = acceleration * obj->getDirection();

		// Sum up all accelerations
		Vec2 resultAcceleration = friction + directionalAcceleration;
		
		// dv = a * t
		Vec2 deltaMovement = resultAcceleration * dt;
		Vec2 tmpMovement = movement + deltaMovement;

		float currentSpeed = tmpMovement.length();

		// Cap value is based on current speed and the maximum speed the object can have
		// If current speed is greater, the movement vector gets capped to vmax
		float capValue = currentSpeed >= obj->getVMax() ? obj->getVMax() : currentSpeed;

		// Cap velocity to capValue
		Vec2 resultMovement = tmpMovement.norm() * capValue;
		
		obj->setMovement(resultMovement);
	}
}