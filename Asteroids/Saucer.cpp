#include "Saucer.h"

Saucer::Saucer(const Vec2 position, const float scale) : GameObject(Model::SAUCER, position, scale) {
	this->lastDirectionChangeTimeStamp = 0;
	this->lastRotationDirection = 1;
}

void Saucer::update(const float dt) {
	GameObject::update(dt);

	updateMovement();
	updateShooting();
}

void Saucer::updateMovement() {
	if ((lifetime - lastDirectionChangeTimeStamp) > DIRECTION_CHANGE_INTERVAL) {
		lastDirectionChangeTimeStamp = lifetime;

		float angleChange = getDirection().getAngleToXAxis() + lastRotationDirection * ANGLE_CHANGE;
		Vec2 rotatedMovement = Vec2::getRotatedInstance(angleChange);

		setDirection(rotatedMovement);
		setMovement(rotatedMovement.mul(getMovement().length()));

		if (lastRotationDirection == 1)
			lastRotationDirection = -1;
		else
			lastRotationDirection = 1;
	}
}

void Saucer::updateShooting() {

}