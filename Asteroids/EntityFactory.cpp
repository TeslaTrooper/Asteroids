#include "EntityFactory.h"

EntityFactory::EntityFactory() {
	entities[ModelClass::CLASS_ASTEROID] = vector<GameObject*>();
	entities[ModelClass::CLASS_PROJECTILE] = vector<GameObject*>();
	entities[ModelClass::CLASS_SAUCER] = vector<GameObject*>();
	entities[ModelClass::CLASS_SHIP] = vector<GameObject*>();
	entities[ModelClass::CLASS_LINE_SEGMENT] = vector<GameObject*>();
}

void EntityFactory::update() {
	vector<GameObject*> objects = linearizeMap(ModelClass::CLASS_UNDEFINED);

	for each (GameObject* obj in objects) {
		if (!obj->isAlive()) {
			remove(obj);
		}
	}
}

GameObject* EntityFactory::createPlayer(const Vec2 position, const float size) {
	GameObject* object = new Ship(position, size);
	object->setVMax(5);

	entities[object->getModelClass()].push_back(object);

	return object;
}

GameObject* EntityFactory::createPlayerInCenter(const float size) {
	int x = (int) ((WIN_WIDTH / 2) - ((ModelData::SHIP_CROP_BOX.width * size) / 2));
	int y = (int) ((WIN_HEIGHT / 2) - ((ModelData::SHIP_CROP_BOX.height * size) / 2));

	return createPlayer(Vec2(x, y), size);
}

GameObject* EntityFactory::createPlayerProjectile(const Vec2 position, const float size, const Vec2 movement) {
	GameObject* obj = createStatic(Model::PROJECTILE, position, size, movement, true);
	obj->setMaxLifetime(PROJECTILE_MAX_LIFETIME);

	return obj;
}

GameObject* EntityFactory::createSaucerProjectile(const Vec2 position, const float size, const Vec2 movement) {
	GameObject* obj = createStatic(Model::PROJECTILE, position, size, movement, false);
	obj->setMaxLifetime(PROJECTILE_MAX_LIFETIME);

	return obj;
}

GameObject* EntityFactory::createSaucer(const Vec2 position, const float size, const Vec2 movement) {
	GameObject* object = new Saucer(position, size);
	configureAsStatic(object, movement, false);

	entities[object->getModelClass()].push_back(object);

	return object;
}

GameObject* EntityFactory::createAsteroid(const Model model, const Vec2 position, const float size, const Vec2 movement) {
	return createStatic(model, position, size, movement, false);
}

void EntityFactory::createSimpleParticleEffect(const Vec2 position) {
	for (int i = 0; i < PARTICLE_COUNT; i++) {
		createParticle(position, Model::PROJECTILE, SIZE_MEDIUM);
	}
}

void EntityFactory::createShipParticleEffect(const Vec2 position) {
	createSimpleParticleEffect(position);

	for (int i = 0; i < PARTICLE_COUNT * 2; i++) {
		GameObject* particle = createParticle(position, Model::LINE_SEGMENT, SIZE_MEDIUM);
		particle->setAngle(random(0, 359));
	}
}

vector<GameObject*> EntityFactory::get() const {
	return linearizeMap(ModelClass::CLASS_UNDEFINED);
}

vector<Entity*> EntityFactory::getAsEntities() const {
	vector<Entity*> entities;
	vector<GameObject*> objects = linearizeMap(ModelClass::CLASS_UNDEFINED);

	for each (GameObject* o in objects) {
		entities.push_back((Entity*) o);
	}

	return entities;
}

GameObject* EntityFactory::getPlayer() const {
	vector<GameObject*> playerVector = entities.at(ModelClass::CLASS_SHIP);

	if (playerVector.size() == 0) {
		return nullptr;
	}

	return playerVector.at(0);
}

vector<GameObject*> EntityFactory::get(const ModelClass modelClass) const {
	return entities.at(modelClass);
}

int EntityFactory::getPlayerProjectileCount() const {
	int result = 0;

	vector<GameObject*> projectiles = entities.at(ModelClass::CLASS_PROJECTILE);
	for each(GameObject* obj in projectiles) {
		if (obj->isPlayerProjectile())
			result++;
	}

	return result;
}

GameObject* EntityFactory::createParticle(const Vec2 position, const Model model, const float size) {
	// First, let's define a random rotation around entire circle
	Vec2 direction = Vec2::getRotatedInstance(random(0, 359));
	Vec2 movement = direction * random(PARTICLE_MIN_VELOCITY, PARTICLE_MAX_VELOCITY);

	GameObject* particle = createStatic(model, position, size, movement, false);
	particle->setInvincible(true);

	// Calc random lifetime between 0.5 and 1.5 seconds
	int randomLifetime = random(PARTICLE_MAX_LIFETIME * 5, PARTICLE_MAX_LIFETIME * 15);
	particle->setMaxLifetime(randomLifetime / 10.f);

	return particle;
}

GameObject* EntityFactory::createStatic(const Model model, const Vec2 position,
	const float size, const Vec2 movement, const bool isPlayerProjectile) {
	GameObject* object = new GameObject(model, position, size);
	configureAsStatic(object, movement, isPlayerProjectile);

	entities[object->getModelClass()].push_back(object);

	return object;
}

void EntityFactory::configureAsStatic(GameObject* object, const Vec2 movement, const bool isPlayerProjectile) {
	object->setAngle(0);
	object->setVMax(movement.length());
	object->setAcceleration(1);
	object->setDirection(movement.norm());
	object->setMovement(movement);
	object->setIsPlayerProjectile(isPlayerProjectile);
}

GameObject* EntityFactory::create(const Model model, const Vec2 position, const float size) {
	GameObject* object = new GameObject(model, position, size);
	entities[object->getModelClass()].push_back(object);

	return object;
}

void EntityFactory::clear() {
	linearizeMap(ModelClass::CLASS_UNDEFINED).clear();
}

vector<GameObject*> EntityFactory::linearizeMap(const ModelClass filter) const {
	vector<GameObject*> result;

	for (const pair<ModelClass, vector<GameObject*>>& pair : entities) {
		for each (GameObject* obj in pair.second) {
			if (filter == ModelClass::CLASS_UNDEFINED || obj->getModelClass() != filter) {
				result.push_back(obj);
			}
		}
	}

	return result;
}

void EntityFactory::remove(GameObject* object) {
	vector<GameObject*>* vec = &entities.at(object->getModelClass());

	auto it = std::find(vec->begin(), vec->end(), object);
	if (it != vec->end())
		vec->erase(it);
}

int EntityFactory::getEntityCount() const {
	return (int) entities.at(ModelClass::CLASS_ASTEROID).size();
}