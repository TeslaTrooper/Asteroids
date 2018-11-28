#ifndef INTERNAL_LOGIC
#define INTERNAL_LOGIC

#include "EntityFactory.h"
#include "PhysicsEngine.h"

#define MAX_PROJECTILE 100
#define PROJECTILE_MAX_LIFETIME 3
#define GAP_PROJECTILE_SHIP 10
#define PROJECTILE_SPEED 10
#define ROTATION_ZONE 45
#define MIN_VELOCITY 20
#define MAX_VELOCITY 50
#define ASTEROID_PIECE_COUNT 2

class InternalLogic {

	int score, lifes;

	EntityFactory entityFactory;
	PhysicsEngine physicsEngine;

	void checkForOutOfBoundsObjects(GameObject* obj) const;
	void resolveColliions(const vector<GameObject*> objects);
	void breakAsteroidIntoPieces(GameObject const * const object);
	void createAsteroidPiece(GameObject const * const object);
	Vec2 calcMovementOfChildAsteroid(const Vec2 parentMovement) const;
	void updateScore(const vector<GameObject*> objects);
	void createPlayer();
	void checkForMissingPlayer();

public:
	InternalLogic() : score(0), lifes(4) {};
	~InternalLogic() {};

	void update(const float dt);
	void markForCleanupIfRequired(GameObject* obj);

	void createInitialEntities();
	void rotatePlayerLeft(const float dt);
	void rotatePlayerRight(const float dt);
	void moveShip(const bool moving, const float dt);
	void shipShoot();

	int getScore() const { return score; };
	int getLifes() const { return lifes; };
	vector<GameObject*> getEntities() { return entityFactory.get(); };
	vector<RenderUnit> getRenderUnits() const;



};

#endif INTERNAL_LOGIC
