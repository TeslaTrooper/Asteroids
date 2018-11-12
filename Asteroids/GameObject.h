#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Util.h"
#include "Vec2.h"

class GameObject {

	Model model;

	Vec2 position;
	Vec2 direction;
	
	float size;
	float speed;
	float acceleration;
	float vmax;
	int angle;

	bool friction;

public:

	static const int POSITIVE_ROTATION = 1;
	static const int NEGATIVE_ROTATION = -1;

	GameObject(const Model model, const Vec2 position, const float size);
	~GameObject() {};

	void useFriction();
	void setAcceleration(const float value);
	void setDirection(const Vec2 direction);
	void setSpeed(const float value);
	void setVMax(const float value);
	void setPosition(const Vec2 position);
	void setAngle(const int angle);
	void rotate(const int direction, const float dt);

	bool hasFriction() const { return friction; };
	Vec2 getPosition() { return position; };
	Vec2 getDirection() const { return direction; };
	float getSpeed() const { return speed; };
	float getAcceleration() const { return acceleration; };
	float getVMax() const { return vmax; };
	int getAngle() const { return angle; };
	RenderUnit getRenderUnit() const;

};

#endif GAME_OBJECT
