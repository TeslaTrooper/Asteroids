#ifndef INTERNAL_LOGIC
#define INTERNAL_LOGIC

#include <PhysicsEngine.h>

#include "EntityFactory.h"
#include "EntitySpawner.h"
#include "ShipController.h"
#include "SoundPlayer.h"

#define PLAYER_CREATION_DELAY 2

#define SCORE_MEDIUM_SAUCER 1000
#define SCORE_LARGE_SAUCER 200
#define SCORE_LARGE_ASTEROID 20
#define SCORE_MEDIUM_ASTEROID 50
#define SCORE_SMALL_ASTEROID 100

#define INITIAL_LIFE_COUNT 4
#define LIFE_PER_SCORE 10000

class InternalLogic : CollisionCallback {

	struct GameStats {
		int score;
		int lifes;
		int lifePerScore;

		GameStats() : score(0), lifes(INITIAL_LIFE_COUNT), lifePerScore(LIFE_PER_SCORE) {};
	};

	float shipCreationCtr;
	bool playerIsMissing;

	GameStats* const stats;
	EntityFactory* const entityFactory;
	EntitySpawner entitySpawner;
	PhysicsEngine physicsEngine;
	ShipController shipController;
	SoundPlayer soundPlayer;

	void checkForOutOfBoundsObjects(GameObject* obj) const;
	void breakAsteroidIntoPieces(GameObject const * const object) const;
	void createAsteroidPiece(GameObject const * const object) const;
	Vec2 calcMovementOfChildAsteroid(const Vec2 parentMovement) const;
	void updateScore(const GameObject* const o1, const GameObject* const o2) const;
	int determineGainedScore(const float objSize, const ModelClass classOfIntersector) const;
	void updateRemainingLifes() const;
	void createPlayer();
	void checkForMissingPlayer(const float dt);
	void checkSaucerBehaviour(Saucer* saucer);

public:
	InternalLogic(EntityFactory* const entityFactory) : playerIsMissing(false), shipCreationCtr(PLAYER_CREATION_DELAY),
		entityFactory(entityFactory), entitySpawner(entityFactory), shipController(ShipController(entityFactory)), stats(new GameStats()),
		physicsEngine(this) {};

	~InternalLogic() {
		delete stats;
		delete entityFactory;
	};

	// Main logic loop
	void update(const float dt);

	// Player steerings
	void rotatePlayerLeft(const float dt);
	void rotatePlayerRight(const float dt);
	void moveShip(const bool moving, const float dt);
	void shipShoot();
	void hyperspace();

	// Methods for UI
	int getScore() const { return stats->score; };
	int getLifes() const { return stats->lifes; };
	vector<GameObject*> getEntities() { return entityFactory->get(); };
	vector<RenderUnit> getRenderUnits() const;

	void resolveCollision(Entity* e1, Entity* e2, const Vec2& location) const override;
};

#endif INTERNAL_LOGIC
