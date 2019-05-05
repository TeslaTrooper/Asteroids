#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <Vec2.h>
#include <Entity.h>

#include "Util.h"
#include "ModelData.h"

#define UNDEFINED_LIFETIME -1

class GameObject : public Entity {

	Model model;
	ModelClass modelClass;

	float lifetime, maxLifetime;
	float scale;

	int angle;

	bool alive, playerProjectile, visible, invincible;

	friend class Ship;
	friend class Saucer;

	// Copy constructor 
	GameObject(const GameObject& obj) : GameObject(obj.model, obj.getPosition(), obj.scale) {}

	// copy assignment operator 
	GameObject& operator=(const GameObject& tmp_obj) {
		model = tmp_obj.model;
		setPosition(tmp_obj.getPosition());
		scale = tmp_obj.scale;

		return *this;
	}

public:

	static const int POSITIVE_ROTATION = 1;
	static const int NEGATIVE_ROTATION = -1;

	GameObject(const Model model, const Vec2 position, const float scale);
	~GameObject() {};

	virtual void update(const float dt);

	bool canCollide() const override;
	bool canCollideWith(const Entity* const e) const override;
	void updateTransformation() override;
	VertexData getVertexData() const override;
	IndexData getTriangulatedIndexData() const override;

	void setAcceleration(const float value) override;
	void setDirection(const Vec2 direction);
	void setAngle(const int angle);
	void rotate(const int direction, const float dt);
	void setIsPlayerProjectile(const bool value);
	void setInvincible(const bool value);
	void setMaxLifetime(const float value);
	void setVisible(const bool value);
	void markForCleanup();

	int getAngle() const { return angle; };
	Model getModel() const { return model; };
	ModelClass getModelClass() const { return modelClass; };
	float getLifetime() const { return lifetime; };
	bool isAlive() const { return alive; };
	float getScale() const { return scale; };
	bool isPlayerProjectile() const { return playerProjectile; };
	bool isVisible() const { return visible; };
	bool isInvincible() const { return invincible; };
	RenderUnit getRenderUnit() const;

};

#endif GAME_OBJECT