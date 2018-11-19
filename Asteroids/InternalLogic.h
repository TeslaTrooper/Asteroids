#ifndef INTERNAL_LOGIC
#define INTERNAL_LOGIC

#include "EntityHandler.h"

class InternalLogic {

	Dimension windowSize;
	EntityHandler entityHandler;

	GameObject* player;

	void checkForOutOfBoundsObjects(const vector<GameObject*> objects) const;

public:
	InternalLogic(const Dimension windowSize) : windowSize(windowSize) {};
	~InternalLogic() {};

	void update(const float dt);

	void createInitialEntities();
	void rotatePlayerLeft(const float dt) { player->rotate(GameObject::NEGATIVE_ROTATION, dt); };
	void rotatePlayerRight(const float dt) { player->rotate(GameObject::POSITIVE_ROTATION, dt); };
	void moveShip(const bool moving, const float dt) { player->setAcceleration(moving ? 1.f : 0.f); };

	vector<GameObject*> getEntities() { return entityHandler.get(); };
	vector<RenderUnit> getRenderUnits() const;



};

#endif INTERNAL_LOGIC
