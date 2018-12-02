#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Util.h"
#include "Vec2.h"
#include "ModelData.h"

#define UNDEFINED_LIFETIME -1

class GameObject {

	Model model;
	ModelClass modelClass;

	Vec2 position;
	Vec2 direction;
	Vec2 movement;

	CollisionInfo* collisionInfo;

	float lifetime, maxLifetime;
	float scale;
	float acceleration;
	float vmax;

	int angle;

	bool alive, playerProjectile, visible, invincible;

	friend class Ship;
	friend class Saucer;

public:

	static const int POSITIVE_ROTATION = 1;
	static const int NEGATIVE_ROTATION = -1;

	GameObject(const Model model, const Vec2 position, const float scale);
	~GameObject() {};

	virtual void update(const float dt);

	void setAcceleration(const float value);
	void setDirection(const Vec2 direction);
	void setMovement(const Vec2 movement);
	void setVMax(const float value);
	void setPosition(const Vec2 position);
	void setAngle(const int angle);
	void rotate(const int direction, const float dt);
	void setCollisionInfo(const CollisionInfo info);
	void setIsPlayerProjectile(const bool value);
	void setInvincible(const bool value);
	void setMaxLifetime(const float value);
	void markForCleanup();

	Vec2 getPosition() const { return position; };
	Vec2 getDirection() const { return direction; };
	float getAcceleration() const { return acceleration; };
	float getVMax() const { return vmax; };
	int getAngle() const { return angle; };
	Vec2 getMovement() const { return movement; };
	Model getModel() const { return model; };
	CollisionInfo getCollisionInfo() const { return *collisionInfo; };
	ModelClass getModelClass() const { return modelClass; };
	float getLifetime() const { return lifetime; };
	bool isAlive() const { return alive; };
	float getScale() const { return scale; };
	bool hasIntersection() const { return collisionInfo != nullptr; };
	bool isPlayerProjectile() const { return playerProjectile; };
	bool isVisible() const { return visible; };
	bool isInvincible() const { return invincible; };
	RenderUnit getRenderUnit() const;

};

#endif GAME_OBJECT