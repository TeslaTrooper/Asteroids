#include "GameObject.h"

GameObject::GameObject(const Model model, const Vec2 position, const float size) {
	this->model = model;
	this->position = position;
	this->size = size;
	this->speed = 0;
	this->acceleration = 0;
	this->vmax = 0;
	this->angle = 0;

	// Default direction points downwards
	this->direction = Vec2(1,0);
}

void GameObject::useFriction() {
	this->friction = true;
}

void GameObject::setDirection(const Vec2 direction) {
	// We dont want zero vector as direction
	if (direction.x == 0 && direction.y == 0) {
		return;
	}

	this->direction = direction;
}

void GameObject::setAcceleration(const float value) {
	if (value == 0) {
		this->acceleration = 0;
	} else {
		this->acceleration = vmax / value;
	}
}

void GameObject::setSpeed(const float value) {
	this->speed = value;
}

void GameObject::setVMax(const float value) {
	this->vmax = value;
}

void GameObject::setPosition(const Vec2 position) {
	this->position = position;
}

void GameObject::setAngle(const int angle) {
	if (angle < 0) {
		this->angle = 360 + angle;
	} else {
		this->angle = angle;
	}

	this->angle %= 360;
}

RenderUnit GameObject::getRenderUnit() const {
	return { Mat4::getTransformation(position, Vec2(size, size), angle), model };
}

void GameObject::rotate(const int direction, const float dt) {
	int angle = getAngle();
	// We want a complete rotation to take 2 seconds
	// So, we have a rotation velocity of 180 degrees per second
	// s = v * t | dAngle = 180 * dt
	int dAngle = (int)(180.f * dt);

	if (direction == POSITIVE_ROTATION) {
		setAngle(angle + dAngle);
	} else {
		setAngle(angle - dAngle);
	}
}