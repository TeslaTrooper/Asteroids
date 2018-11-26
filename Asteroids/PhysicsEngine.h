#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <vector>

#include "Util.h"
#include "GameObject.h"

class PhysicsEngine {

	ModelData modelData;

	void updatePosition(const vector<GameObject*> objects, const float dt) const;
	void updateVelocity(const vector<GameObject*> objects, const float dt) const;
	void detectCollision(const vector<GameObject*> objects, const float dt) const;

	bool detectSimpleCollision(GameObject const * const obj1, GameObject const * const obj2) const;
	bool detectComplexCollision(GameObject const * const obj1, GameObject const * const obj2) const;
	bool detectTrianglePointIntersection(const vector<Vec2> vertices, const vector<Triangle> triangles) const;
	bool detectTrianglePointIntersection(const Vec2 vertex, const Triangle& triangle) const;

public:

	PhysicsEngine() {};
	~PhysicsEngine() {};

	void update(const vector<GameObject*> objects, const float dt) const;

};

#endif PHYSICS_ENGINE