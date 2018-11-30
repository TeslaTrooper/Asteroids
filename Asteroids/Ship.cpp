#include "Ship.h"

Ship::Ship(const Vec2 position, const float scale) : GameObject(Model::SHIP, position, scale) {
	this->invincible = true;

	lastMovingAnimationTimeStamp = 0;
	lastInvincibleAnimationTimeStamp = 0;
}

void Ship::update(const float dt) {
	GameObject::update(dt);

	updateMoveAnimation();
	updateInvincibleAnimation();
}

void Ship::updateMoveAnimation() {
	// If there is no acceleration, switch to default model
	if (acceleration == 0) {
		model = Model::SHIP;
		return;
	}

	// If last animation exceeds interval
	if ((lifetime - lastMovingAnimationTimeStamp) > MOVING_ANIMATION_INTERVAL) {
		lastMovingAnimationTimeStamp = lifetime;

		// Switching models
		if (model == Model::SHIP)
			model = Model::SHIP_MOVING;
		else
			model = Model::SHIP;
	}
}

void Ship::updateInvincibleAnimation() {
	// Ship is invincible in first few seconds
	if (lifetime > INVINCIBLE_DURATION) {
		invincible = false;
		visible = true;
		return;
	}

	if ((lifetime - lastInvincibleAnimationTimeStamp) > INVINCIBLE_ANIMATION_INTERVAL) {
		lastInvincibleAnimationTimeStamp = lifetime;

		visible = !visible;
	}
}