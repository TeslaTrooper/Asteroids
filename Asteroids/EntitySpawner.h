#pragma once

#include "EntityFactory.h"

class EntitySpawner {

	EntityFactory* const entityFactory;

	float elapsedTime;
	float lastSmallSaucerTimeStamp, lastBigSaucerTimeStamp;

	int totalEntityCount;

	int getEntityCountToCreate();
	float getRandomSize();
	Vec2 getRandomMovement();

	void checkForAsteroidCreation();
	void checkForSaucerCreation();

public:
	EntitySpawner(EntityFactory* const entityFactory);
	~EntitySpawner() {};

	void update(const float dt);

};