#ifndef INTERNAL_LOGIC
#define INTERNAL_LOGIC

#include "EntityFactory.h"
#include "PhysicsEngine.h"
#include "EntitySpawner.h"
#include "ShipController.h"

#define PLAYER_CREATION_DELAY 2

class InternalLogic {

	int score, lifes;
	float shipCreationCtr;
	bool playerIsMissing;

	EntityFactory* const entityFactory;
	EntitySpawner entitySpawner;
	PhysicsEngine physicsEngine;
	ShipController shipController;

	void checkForOutOfBoundsObjects(GameObject* obj) const;
	void resolveColliions(const vector<GameObject*> objects);
	void breakAsteroidIntoPieces(GameObject const * const object);
	void createAsteroidPiece(GameObject const * const object);
	Vec2 calcMovementOfChildAsteroid(const Vec2 parentMovement) const;
	void updateScore(const vector<GameObject*> objects);
	void createPlayer();
	void checkForMissingPlayer(const float dt);
	void checkSaucerBehaviour(Saucer* saucer);

public:
	InternalLogic(EntityFactory* const entityFactory) : score(0), lifes(4), playerIsMissing(false), shipCreationCtr(PLAYER_CREATION_DELAY),
		entityFactory(entityFactory), entitySpawner(entityFactory), shipController(ShipController(entityFactory)) {
		entityFactory->createSaucer(Vec2(100, 100), SIZE_SMALL, Vec2(1, 0));
	};
	~InternalLogic() {};

	// Main logic loop
	void update(const float dt);

	// Player steerings
	void rotatePlayerLeft(const float dt);
	void rotatePlayerRight(const float dt);
	void moveShip(const bool moving, const float dt);
	void shipShoot();
	void hyperspace();

	// Methods for UI
	int getScore() const { return score; };
	int getLifes() const { return lifes; };
	vector<GameObject*> getEntities() { return entityFactory->get(); };
	vector<RenderUnit> getRenderUnits() const;
};

#endif INTERNAL_LOGIC
