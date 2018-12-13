#include "Ship.h"

Ship::Ship(const Vec2 position, const float scale) : GameObject(Model::SHIP, position, scale) {
	this->invincible = true;
	this->invincibleAnimationDone = false;
	this->inHyperspace = false;

	lastMovingAnimationTimeStamp = 0;
	lastInvincibleAnimationTimeStamp = 0;
}

void Ship::update(const float dt) {
	if (inHyperspace)
		return;

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
	if (invincibleAnimationDone)
		return;

	// Ship is invincible in first few seconds
	if (lifetime > INVINCIBLE_DURATION) {
		invincible = false;
		visible = true;
		invincibleAnimationDone = true;

		return;
	}

	if ((lifetime - lastInvincibleAnimationTimeStamp) > INVINCIBLE_ANIMATION_INTERVAL) {
		lastInvincibleAnimationTimeStamp = lifetime;

		visible = !visible;
	}
}

void Ship::enterHyperspace() {
	if (inHyperspace)
		return;

	Dimension dim = ModelData::getCropBox(ModelClass::CLASS_SHIP, getScale());
	Vec2 cropBox = Vec2(dim.width, dim.height);

	setPosition(getRandomPosition().sub(cropBox).absolut());
	setMovement(Vec2());
	setInvincible(true);
	setVisible(false);

	inHyperspace = true;
}

void Ship::leaveHyperspace() {
	setInvincible(false);
	setVisible(true);

	inHyperspace = false;
}