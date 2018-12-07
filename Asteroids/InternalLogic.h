#ifndef INTERNAL_LOGIC
#define INTERNAL_LOGIC

#include "EntityFactory.h"
#include "PhysicsEngine.h"
#include "EntitySpawner.h"

class InternalLogic {

	int score, lifes;

	EntityFactory* const entityFactory;
	EntitySpawner entitySpawner;
	PhysicsEngine physicsEngine;

	void checkForOutOfBoundsObjects(GameObject* obj) const;
	void resolveColliions(const vector<GameObject*> objects);
	void breakAsteroidIntoPieces(GameObject const * const object);
	void createAsteroidPiece(GameObject const * const object);
	Vec2 calcMovementOfChildAsteroid(const Vec2 parentMovement) const;
	void updateScore(const vector<GameObject*> objects);
	void createPlayer();
	void checkForMissingPlayer();
	void checkSaucerBehaviour(Saucer* saucer);

public:
	InternalLogic(EntityFactory* const entityFactory);
	~InternalLogic() {};

	void update(const float dt);

	void createInitialEntities();
	void rotatePlayerLeft(const float dt);
	void rotatePlayerRight(const float dt);
	void moveShip(const bool moving, const float dt);
	void shipShoot();
	void hyperspace();

	int getScore() const { return score; };
	int getLifes() const { return lifes; };
	vector<GameObject*> getEntities() { return entityFactory->get(); };
	vector<RenderUnit> getRenderUnits() const;



};

#endif INTERNAL_LOGIC
