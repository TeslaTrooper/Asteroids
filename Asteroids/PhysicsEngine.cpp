#include "PhysicsEngine.h"

void PhysicsEngine::update(const vector<GameObject*> objects, const float dt) const {
	updatePosition(objects, dt);
	detectCollision(objects, dt);
	//resolveCollision(objects, dt);
	updateVelocity(objects, dt);
}

void PhysicsEngine::updatePosition(const vector<GameObject*> objects, const float dt) const {
	for each (GameObject* obj in objects) {
		// Fetch all data for physx calculations
		Vec2 position = obj->getPosition();
		Vec2 direction = obj->getDirection();
		Vec2 movement = obj->getMovement();

		// update position: pn = pn-1+vn-1
		obj->setPosition(position + movement);
	}
}

void PhysicsEngine::updateVelocity(const vector<GameObject*> objects, const float dt) const {
	for each (GameObject* obj in objects) {
		// Fetch all data for physx calculations
		Vec2 movement = obj->getMovement();
		float acceleration = obj->getAcceleration();

		// Friction is an acceleration pointing in the opposite direction of current movement
		Vec2 friction = movement.inv().mul(0.5f);
		// And we have the normal acceleration, which is triggered by player input
		Vec2 directionalAcceleration = acceleration * obj->getDirection();
		// Sum up all accelerations
		Vec2 resultAcceleration = friction + directionalAcceleration;

		// We want to know delta movement (step) since last frame
		// => dV = a * t
		Vec2 deltaMovement = resultAcceleration * dt;
		// We want to know the overall movement
		// => V = a * t + V0 = dV + V0
		Vec2 tmpMovement = movement + deltaMovement;

		float currentSpeed = tmpMovement.length();
		// To prevent the ship from endless acceleration, we have to cap movement to vmax
		// Cap value is based on current speed and the maximum speed the object can have
		// Therefore, the resulting cap value is min(vmax, currentSpeed)
		float capValue = customMath::min(currentSpeed, obj->getVMax());

		// Cap velocity based on capValue
		Vec2 resultMovement = tmpMovement.norm() * capValue;

		// Finally, pass updated velocity vector to object
		obj->setMovement(resultMovement);
	}
}

void PhysicsEngine::detectCollision(const vector<GameObject*> objects, const float dt) const {
	// What we need:
	// VertexData from each object
	// IndexData defining triangles based on VertexData
	// Transformation matrix for transforming each single vertex to its actual position on screen

	for each (GameObject* outerObj in objects) {
		for each (GameObject* innerObj in objects) {
			if (outerObj->getModelClass() == innerObj->getModelClass()) {
				continue;
			}

			if (!detectSimpleCollision(outerObj, innerObj)) {
				continue;
			}

			if (!detectComplexCollision(outerObj, innerObj)) {
				continue;
			}

			// Now, we know, if outerObj is colliding with innerObj
			outerObj->setIsIntersecting(true);
			innerObj->setIsIntersecting(true);
		}
	}
}

bool PhysicsEngine::detectSimpleCollision(GameObject const * const obj1, GameObject const * const obj2) const {
	Vec2 v1 = Vec2(0, 0);
	Vec2 v3 = Vec2(1, 1);

	Dimension dimObj1 = ModelData::getCropBox(obj1->getModelClass());
	Dimension dimObj2 = ModelData::getCropBox(obj2->getModelClass());

	Vec2 scaling1 = Vec2(obj1->getScale() + dimObj1.width, obj1->getScale() + dimObj1.height);
	Mat4 transformation1 = Mat4::getTransformation(obj1->getPosition(), scaling1);

	Vec2 scaling2 = Vec2(obj2->getScale() + dimObj2.width, obj2->getScale() + dimObj2.height);
	Mat4 transformation2 = Mat4::getTransformation(obj2->getPosition(), scaling2);

	Vec2 a1 = transformation1.transform(v1);
	Vec2 a2 = transformation1.transform(v3);

	Vec2 b1 = transformation2.transform(v1);
	Vec2 b2 = transformation2.transform(v3);

	if (a1.x < b2.x && a2.x > b1.x &&
		a1.y < b2.y && a2.y > b1.y) {
		return true;
	}

	return false;
}

bool PhysicsEngine::detectComplexCollision(GameObject const * const obj1, GameObject const * const obj2) const {
	VertexData outerVertexData = modelData.getBindable(obj1->getModel()).vertexData;
	VertexData innerVertexData = modelData.getBindable(obj2->getModel()).vertexData;

	Mat4 outerTransformation = obj1->getRenderUnit().transformation;
	Mat4 innerTransformation = obj2->getRenderUnit().transformation;

	vector<Vec2> outerVertices = getTransformedVertices(outerVertexData, outerTransformation);
	vector<Vec2> innerVertices = getTransformedVertices(innerVertexData, innerTransformation);

	IndexData innerTriangleIndexData = modelData.getTriangulatedModelData(obj2->getModel());
	vector<Triangle> innerTriangles = convertVerticesToTriangles(innerVertices, innerTriangleIndexData);

	// Now, we have to check, if any vertex from outerVertices 
	// intersects with any triangle from innerTriangles

	return detectTrianglePointIntersection(outerVertices, innerTriangles);
}

void PhysicsEngine::resolveCollision(const vector<GameObject*> objects, const float dt) const {
	for each (GameObject* obj in objects) {
		if (obj->hasIntersection()) {
			obj->setAcceleration(0);
			obj->setMovement(Vec2());
		}
	}
}

bool PhysicsEngine::detectTrianglePointIntersection(const vector<Vec2> vertices, const vector<Triangle> triangles) const {
	for each (Vec2 vertex in vertices) {
		for each (Triangle triangle in triangles) {
			bool hasIntersection = detectTrianglePointIntersection(vertex, triangle);

			if (hasIntersection)
				return true;
		}
	}

	return false;
}

// Source: http://www.jeffreythompson.org/collision-detection/tri-point.php
// Source: https://www.youtube.com/watch?v=HYAgJN3x4GA
bool PhysicsEngine::detectTrianglePointIntersection(const Vec2 vertex, const Triangle& triangle) const {
	Vec2 a = triangle.p1;
	Vec2 b = triangle.p2;
	Vec2 c = triangle.p3;

	double zaehler1 = a.x * (c.y - a.y) + (vertex.y - a.y) * (c.x - a.x) - vertex.x * (c.y - a.y);
	double nenner1 = (b.y - a.y) * (c.x - a.x) - (b.x - a.x) * (c.y - a.y);
	double w1 = zaehler1 / nenner1;

	double zaehler2 = vertex.y - a.y - w1 * (b.y - a.y);
	double nenner2 = c.y - a.y;
	double w2 = zaehler2 / nenner2;

	return w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1;
}