#ifndef ENTITY_HANDLER
#define ENTITY_HANDLER

#include <vector>

#include "GameObject.h"
#include "Ship.h"
#include "Saucer.h"
#include "Util.h"

class EntityFactory {

	map<ModelClass, vector<GameObject*>> entities;

	vector<GameObject*> linearizeMap() const;
	void remove(GameObject* object);

	GameObject* createStatic(const Model model, const Vec2 position, const float size, const Vec2 movement, const bool isPlayerProjectile);
	GameObject* create(const Model model, const Vec2 position, const float size);
	GameObject* createParticle(const Vec2 position, const Model model, const float size);

	void configureAsStatic(GameObject* object, const Vec2 movement, const bool isPlayerProjectile);

public:
	EntityFactory();
	~EntityFactory() {};

	void update();
	void clear();

	GameObject* createPlayer(const Vec2 position, const float size);
	GameObject* createPlayerInCenter(const float size);
	GameObject* createPlayerProjectile(const Vec2 position, const float size, const Vec2 movement);
	GameObject* createSaucerProjectile(const Vec2 position, const float size, const Vec2 movement);
	GameObject* createSaucer(const Vec2 position, const float size, const Vec2 movement);
	GameObject* createAsteroid(const Model model, const Vec2 position, const float size, const Vec2 movement);
	void createSimpleParticleEffect(const Vec2 position);
	void createShipParticleEffect(const Vec2 position);

	vector<GameObject*> get() const;
	GameObject* getPlayer() const;
	vector<GameObject*> get(const ModelClass modelClass) const;
};

#endif ENTITY_HANDLER