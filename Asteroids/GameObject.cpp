#include "GameObject.h"

GameObject::GameObject(const Model model, const Vec2 position, const float size) {
	this->model = model;
	this->position = position;
	this->size = size;
	this->speed = 0;
	this->acceleration = 0;
	this->vmax = 0;

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

RenderUnit GameObject::getRenderUnit() const {
	return { Mat4::getTransformation(position, Vec2(size, size)), model };
}