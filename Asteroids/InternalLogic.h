#ifndef INTERNAL_LOGIC
#define INTERNAL_LOGIC

#include "EntityFactory.h"
#include "PhysicsEngine.h"

#define MAX_PROJECTILE 100
#define PROJECTILE_MAX_LIFETIME 3
#define GAP_PROJECTILE_SHIP 10
#define PROJECTILE_SPEED 10

class InternalLogic {

	Dimension windowSize;
	EntityFactory entityFactory;
	PhysicsEngine physicsEngine;

	void checkForOutOfBoundsObjects(GameObject* obj) const;
	void resolveColliions(const vector<GameObject*> objects);

public:
	InternalLogic(const Dimension windowSize) : windowSize(windowSize) {};
	~InternalLogic() {};

	void update(const float dt);
	void observeProjectiles(GameObject* obj);

	void createInitialEntities();
	void rotatePlayerLeft(const float dt);
	void rotatePlayerRight(const float dt);
	void moveShip(const bool moving, const float dt);
	void shipShoot();

	vector<GameObject*> getEntities() { return entityFactory.get(); };
	vector<RenderUnit> getRenderUnits() const;



};

#endif INTERNAL_LOGIC
