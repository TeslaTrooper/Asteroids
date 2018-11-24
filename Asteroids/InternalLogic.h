#ifndef INTERNAL_LOGIC
#define INTERNAL_LOGIC

#include "EntityFactory.h"

#define MAX_PROJECTILE 4
#define PROJECTILE_MAX_LIFETIME 3
#define GAP_PROJECTILE_SHIP 10
#define PROJECTILE_SPEED 10

class InternalLogic {

	Dimension windowSize;
	EntityFactory entityFactory;

	void checkForOutOfBoundsObjects(GameObject* obj) const;

public:
	InternalLogic(const Dimension windowSize) : windowSize(windowSize) {};
	~InternalLogic() {};

	void update(const float dt);
	void observeProjectiles(GameObject* obj);

	void createInitialEntities();
	void rotatePlayerLeft(const float dt) { entityFactory.getPlayer()->rotate(GameObject::NEGATIVE_ROTATION, dt); };
	void rotatePlayerRight(const float dt) { entityFactory.getPlayer()->rotate(GameObject::POSITIVE_ROTATION, dt); };
	void moveShip(const bool moving, const float dt) { entityFactory.getPlayer()->setAcceleration(moving ? 1.f : 0.f); };
	void shipShoot();

	vector<GameObject*> getEntities() { return entityFactory.get(); };
	vector<RenderUnit> getRenderUnits() const;



};

#endif INTERNAL_LOGIC
