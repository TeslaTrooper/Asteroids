#include "GameObject.h"

GameObject::GameObject(const Model model, const Vec2 position, const float scale) {
	this->model = model;
	this->position = position;
	this->scale = scale;
	this->acceleration = 0;
	this->vmax = 0;
	this->angle = 270;
	this->intersectingObject = nullptr;
	this->lifetime = 0;
	this->alive = true;
	this->playerProjectile = true;

	this->modelClass = getClassFromModel(model);

	// Default direction points upwards
	this->direction = Vec2(0, 1);
}

void GameObject::update(const float dt) {
	this->lifetime += dt;
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
		this->direction = Vec2::getRotatedInstance(angle);
		this->acceleration = vmax / value;
	}
}

void GameObject::setVMax(const float value) {
	this->vmax = value;
}

void GameObject::setPosition(const Vec2 position) {
	this->position = position;
}

void GameObject::setMovement(const Vec2 movement) {
	this->movement = movement;
}

void GameObject::setIntersectingObject(GameObject* object) {
	this->intersectingObject = object;
}

void GameObject::setIsPlayerProjectile(const bool value) {
	this->playerProjectile = value;
}

void GameObject::markForCleanup() {
	this->alive = false;
}

void GameObject::setAngle(const int angle) {
	if (angle < 0) {
		this->angle = 360 + angle;
	} else {
		this->angle = angle;
	}

	this->angle %= 360;
	if (acceleration > 0) {
		this->direction = Vec2::getRotatedInstance(angle);
	}
}

RenderUnit GameObject::getRenderUnit() const {
	Dimension modelDim = ModelData::getCropBox(modelClass);
	Vec2 rotationOrigin = Vec2(modelDim.width / 2, modelDim.height / 2);
	Mat4 transformation = Mat4::getTransformation(position, Vec2(scale, scale), (float) angle, rotationOrigin);

	return { transformation , model };
}

void GameObject::rotate(const int direction, const float dt) {
	int angle = getAngle();
	// We want a complete rotation to take 2 seconds
	// So, we have a rotation velocity of 180 degrees per second
	// s = v * t | dAngle = 180 * dt
	int dAngle = (int) (180.f * dt);

	if (direction == POSITIVE_ROTATION) {
		setAngle(angle - dAngle);
	} else {
		setAngle(angle + dAngle);
	}
}