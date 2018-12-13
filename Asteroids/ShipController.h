#ifndef SHIP_CONTROLLER
#define SHIP_CONTROLLER

#include "EntityFactory.h"

#define DELAY 1

class ShipController {

	EntityFactory* const entityFactory;

	float delayCtr;
	bool inProgress;

	void showShipAfterHyperspace();

public:
	ShipController(EntityFactory* const entityFactory);
	~ShipController() {};

	void update(const float dt);

	void rotatePlayerLeft(const float dt);
	void rotatePlayerRight(const float dt);
	void moveShip(const bool moving, const float dt);
	void hyperspace();

};

#endif SHIP_CONTROLLER