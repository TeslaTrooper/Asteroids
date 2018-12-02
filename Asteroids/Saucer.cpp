#include "Saucer.h"

Saucer::Saucer(const Vec2 position, const float scale) : GameObject(Model::SAUCER, position, scale) {
	this->lastDirectionChangeTimeStamp = 0;
	this->lastRotationDirection = 1;
}

void Saucer::update(const float dt) {
	GameObject::update(dt);

	updateMovement();
}

void Saucer::updateMovement() {
	if ((lifetime - lastDirectionChangeTimeStamp) > DIRECTION_CHANGE_INTERVAL) {
		lastDirectionChangeTimeStamp = lifetime;

		float angleChange = getDirection().getAngleToXAxis() + lastRotationDirection * ANGLE_CHANGE;
		Vec2 rotatedMovement = Vec2::getRotatedInstance((int) angleChange);

		setDirection(rotatedMovement);
		setMovement(rotatedMovement.mul(getMovement().length()));

		if (lastRotationDirection == 1)
			lastRotationDirection = -1;
		else
			lastRotationDirection = 1;
	}
}

bool Saucer::canShoot() {
	if ((lifetime - lastShootingTimeStamp) > SHOOTING_INTERVAL) {
		lastShootingTimeStamp = lifetime;

		return true;
	}

	return false;
}

ProjectileParams Saucer::getProjectileParams(const Vec2 shipPosition) const {
	if (getScale() == SIZE_LARGE) {
		return getBySimpleBehaviour();
	}

	return getByAdvancedBehaviour(shipPosition);
}

ProjectileParams Saucer::getBySimpleBehaviour() const {
	int randomAngle = random(0, 359);
	Vec2 direction = Vec2::getRotatedInstance(randomAngle);
	Vec2 movement = direction.mul(PROJECTILE_SPEED);

	float r = (ModelData::SAUCER_CROP_BOX.width / 2) * getScale();
	Vec2 circleOrigin = getPosition().add(Vec2(r, (ModelData::SAUCER_CROP_BOX.height / 2) * getScale()));
	Vec2 position = circleOrigin + r * direction;

	return { position, movement };
}

ProjectileParams Saucer::getByAdvancedBehaviour(const Vec2 shipPosition) const {
	float r = (ModelData::SAUCER_CROP_BOX.width / 2) * getScale();
	Vec2 circleOrigin = getPosition().add(Vec2(r, (ModelData::SAUCER_CROP_BOX.height / 2) * getScale()));

	Vec2 direction = circleOrigin.rotateTo(shipPosition, 1);
	Vec2 position = circleOrigin + r * direction;
	Vec2 movement = direction.mul(PROJECTILE_SPEED);

	return { position, movement };
}