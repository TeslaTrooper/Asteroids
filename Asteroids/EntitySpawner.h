#pragma once

#include "EntityFactory.h"

#define UPDATE_INTERVAL 2

class EntitySpawner {

	EntityFactory* const entityFactory;

	float elapsedTime;
	float lastUpdate, lastSmallSaucerTimeStamp, lastBigSaucerTimeStamp;

	int totalEntityCount;

	int getEntityCountToCreate();
	float getRandomSize();
	Vec2 getRandomMovement();
	Vec2 getPosition(const Dimension cropBox);

	void checkForAsteroidCreation();
	void checkForSaucerCreation();

public:
	EntitySpawner(EntityFactory* const entityFactory);
	~EntitySpawner() {};

	void update(const float dt);

};