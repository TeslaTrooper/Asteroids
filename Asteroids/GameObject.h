#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Util.h"
#include "Vec2.h"
#include "ModelData.h"

class GameObject {

	Model model;
	ModelClass modelClass;

	Vec2 position;
	Vec2 direction;
	Vec2 movement;

	float lifetime;

	float scale;
	float acceleration;
	float vmax;
	int angle;

	bool isIntersecting;
	bool alive;

	friend class Ship;

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
	void setIsIntersecting(const bool value);
	void markForCleanup();

	Vec2 getPosition() { return position; };
	Vec2 getDirection() const { return direction; };
	float getAcceleration() const { return acceleration; };
	float getVMax() const { return vmax; };
	int getAngle() const { return angle; };
	Vec2 getMovement() const { return movement; };
	Model getModel() const { return model; };
	bool hasIntersection() const { return isIntersecting; };
	ModelClass getModelClass() const { return modelClass; };
	float getLifetime() const { return lifetime; };
	bool isAlive() const { return alive; };
	RenderUnit getRenderUnit() const;

};

#endif GAME_OBJECT
