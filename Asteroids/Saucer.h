#ifndef SAUCER_CLASS
#define SAUCER_CLASS

#include "GameObject.h"

#define DIRECTION_CHANGE_INTERVAL 2
#define ANGLE_CHANGE 45

class Saucer : public GameObject {

	float lastDirectionChangeTimeStamp;
	char lastRotationDirection;

	void updateMovement();
	void updateShooting();

public:
	Saucer(const Vec2 position, const float scale);
	~Saucer() { GameObject::~GameObject(); };

	void update(const float dt) override;
};

#endif SAUCER_CLASS