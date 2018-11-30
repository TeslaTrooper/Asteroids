#ifndef SHIP_CLASS
#define SHIP_CLASS

#include "GameObject.h"

#define MOVING_ANIMATION_INTERVAL 0.05f
#define INVINCIBLE_ANIMATION_INTERVAL 0.2f
#define INVINCIBLE_DURATION 3

class Ship : public GameObject {

	float lastMovingAnimationTimeStamp;
	float lastInvincibleAnimationTimeStamp;

	void updateMoveAnimation();
	void updateInvincibleAnimation();

public:
	Ship(const Vec2 position, const float scale);
	~Ship() { GameObject::~GameObject(); };

	void update(const float dt) override;
};

#endif SHIP_CLASS