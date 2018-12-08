#include "EntitySpawner.h"

EntitySpawner::EntitySpawner(EntityFactory* const entityFactory) : entityFactory(entityFactory) {
	this->elapsedTime = 0;
	this->lastUpdate = 0;
	this->lastBigSaucerTimeStamp = 0;
	this->lastSmallSaucerTimeStamp = 0;
	this->totalEntityCount = INITAL_ENTITY_COUNT;

	checkForAsteroidCreation();
};

void EntitySpawner::update(const float dt) {
	elapsedTime += dt;

	if ((elapsedTime - lastUpdate) < UPDATE_INTERVAL) {
		return;
	}

	lastUpdate = elapsedTime;

	checkForAsteroidCreation();
	checkForSaucerCreation();
}

void EntitySpawner::checkForAsteroidCreation() {
	int count = getEntityCountToCreate();
	for (int i = 0; i < count; i++) {
		Model randomAsteroidModel = (Model) random(0, 3);
		Vec2 position = getPosition(ModelData::getCropBox(ModelClass::CLASS_ASTEROID, SIZE_LARGE));
		float size = getRandomSize();
		Vec2 movement = getRandomMovement();

		entityFactory->createAsteroid(randomAsteroidModel, position, size, movement);
	}
}

void EntitySpawner::checkForSaucerCreation() {
	if ((elapsedTime - lastBigSaucerTimeStamp) >= BIG_SAUCER_INTERVAL) {
		lastBigSaucerTimeStamp = elapsedTime;

		entityFactory->createSaucer(getRandomPosition(), SIZE_LARGE, getRandomMovement());
	}

	if ((elapsedTime - lastSmallSaucerTimeStamp) >= SMALL_SAUCER_INTERVAL) {
		lastSmallSaucerTimeStamp = elapsedTime;

		entityFactory->createSaucer(getRandomPosition(), SIZE_MEDIUM, getRandomMovement());
	}
}

int EntitySpawner::getEntityCountToCreate() {
	int currentEntityCount = entityFactory->getEntityCount();

	return totalEntityCount - currentEntityCount;
}

float EntitySpawner::getRandomSize() {
	int r = random(0, 2);

	if (r == 0) return SIZE_SMALL;
	if (r == 1) return SIZE_MEDIUM;

	return SIZE_LARGE;
}

Vec2 EntitySpawner::getRandomMovement() {
	int randomAngle = random(0, 359);
	Vec2 direction = Vec2::getRotatedInstance(randomAngle);

	int randomVelocity = random(SAUCER_MIN_VELOCITY, SAUCER_MAX_VELOCITY);
	float velocity = randomVelocity / 10.f;

	return direction.mul(velocity);
}

Vec2 EntitySpawner::getPosition(const Dimension cropBox) {
	// Determine random position
	// Default position for y is top
	int x = random(-cropBox.width, WIN_WIDTH);
	int y = -cropBox.height;

	// Check, whether the entity gets positioned top or bottom
	if (random(0, 1) == 0)
		y = WIN_HEIGHT;

	return Vec2(x, y);
}