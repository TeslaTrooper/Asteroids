#include "Ship.h"

void Ship::update(const float dt) {
	GameObject::update(dt);

	updateMoveAnimation(dt);
}

void Ship::updateMoveAnimation(const float dt) {
	if (acceleration == 0) {
		model = Model::SHIP;
	} else if (lifetime > ANIMATION_SPEED) {
		if (model == Model::SHIP)
			model = Model::SHIP_MOVING;
		else
			model = Model::SHIP;

		lifetime = 0;
	}
}