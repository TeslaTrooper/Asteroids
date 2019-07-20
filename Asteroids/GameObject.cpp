#include "GameObject.h"

GameObject::GameObject(const Model model, const Vec2 position, const float scale) : Entity() {
	this->model = model;
	this->scale = scale;
	this->angle = 270;
	this->lifetime = 0;
	this->maxLifetime = UNDEFINED_LIFETIME;
	this->alive = true;
	this->playerProjectile = true;
	this->visible = true;
	this->invincible = false;

	this->modelClass = getClassFromModel(model);

	// Default direction points upwards
	setDirection(Vec2(0, 1));
	setPosition(position);

	Dimension d = ModelData::getCropBox(getModelClass(), scale);
	setBbox(Vec2(d.width, d.height));
}

void GameObject::update(const float dt) {
	if (!isAlive())
		return;

	this->lifetime += dt;

	if (maxLifetime != UNDEFINED_LIFETIME && lifetime > maxLifetime) {
		markForCleanup();
	}

	updateTransformation();
}

void GameObject::setDirection(const Vec2 direction) {
	// We dont want zero vector as direction
	if (direction.x == 0 && direction.y == 0) {
		return;
	}

	Entity::setDirection(direction);
}

void GameObject::setAcceleration(const float value) {
	if (value == 0) {
		Entity::setAcceleration(0);
	} else {
		setDirection(Vec2::getRotatedInstance(angle));
		Entity::setAcceleration(getVMax() / value);
	}
}

void GameObject::setInvincible(const bool value) {
	this->invincible = value;
}

void GameObject::setMaxLifetime(const float value) {
	this->maxLifetime = value;
}

void GameObject::setVisible(const bool value) {
	this->visible = value;
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
	if (getAcceleration() > 0) {
		setDirection(Vec2::getRotatedInstance(angle));
	}
}

RenderUnit GameObject::getRenderUnit() const {
	return { getTransformation() , model };
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

bool GameObject::canCollide() const {
	if (!this->isVisible())
		return false;

	if (this->isInvincible())
		return false;

	if (!isAlive())
		return false;

	return true;
}

bool GameObject::canCollideWith(const Entity* const e) const {
	GameObject* o = (GameObject*) e;

	return this->getModelClass() != o->getModelClass();
}

void GameObject::updateTransformation() {
	Dimension modelDim = ModelData::getCropBox(modelClass, 1);
	Vec2 rotationOrigin = Vec2(modelDim.width / 2, modelDim.height / 2);

	setTransformation(Mat4::getTransformation(getPosition(), Vec2(scale, scale), (float) angle, rotationOrigin));
}

VertexData GameObject::getVertexData() const {
	return ModelData::getBindable(model).vertexData;
}

IndexData GameObject::getTriangulatedIndexData() const {
	return ModelData::getTriangulatedIndexData(model);
}