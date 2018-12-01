#ifndef SAUCER_CLASS
#define SAUCER_CLASS

#include "GameObject.h"

#define DIRECTION_CHANGE_INTERVAL 2
#define ANGLE_CHANGE 45
#define SHOOTING_INTERVAL 3

struct ProjectileParams {
	Vec2 position;
	Vec2 movement;
};

class Saucer : public GameObject {

	float lastDirectionChangeTimeStamp;
	float lastShootingTimeStamp;
	char lastRotationDirection;

	void updateMovement();
	ProjectileParams getBySimpleBehaviour() const;
	ProjectileParams getByAdvancedBehaviour(const Vec2 shipPosition) const;

public:

	Saucer(const Vec2 position, const float scale);
	~Saucer() { GameObject::~GameObject(); };

	void update(const float dt) override;
	bool canShoot();
	ProjectileParams getProjectileParams(const Vec2 shipPosition) const;
};

#endif SAUCER_CLASS