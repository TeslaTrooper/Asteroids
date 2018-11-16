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
		// And we have the normal acceleration, which is triggered by player input
		Vec2 directionalAcceleration = acceleration * obj->getDirection();
		// Sum up all accelerations
		Vec2 resultAcceleration = friction + directionalAcceleration;
		
		// We want to know delta movement (step) since last frame
		// => dV = a * t
		Vec2 deltaMovement = resultAcceleration * dt;
		// We want to know the overall movement
		// => V = a * t + V0 = dV + V0
		Vec2 tmpMovement = movement + deltaMovement;

		float currentSpeed = tmpMovement.length();
		// To prevent the ship from endless acceleration, we have to cap movement to vmax
		// Cap value is based on current speed and the maximum speed the object can have
		// Therefore, the resulting cap value is min(vmax, currentSpeed)
		float capValue = customMath::min(currentSpeed, obj->getVMax());

		// Cap velocity based on capValue
		Vec2 resultMovement = tmpMovement.norm() * capValue;
		
		obj->setMovement(resultMovement);
	}
}