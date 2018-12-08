#include "PhysicsEngine.h"

void PhysicsEngine::update(const vector<GameObject*> objects, const float dt) const {
	updatePosition(objects, dt);
	detectCollision(objects, dt);
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
		if (outerObj->isInvincible())
			continue;

		for each (GameObject* innerObj in objects) {
			if (outerObj->getModelClass() == innerObj->getModelClass())
				continue;

			if (innerObj->isInvincible())
				continue;

			if (!detectSimpleCollision(outerObj, innerObj))
				continue;

			Vec2* collisionLocation = detectComplexCollision(outerObj, innerObj);
			if (collisionLocation == nullptr)
				continue;

			// Now, we know, if outerObj is colliding with innerObj
			outerObj->setCollisionInfo({ innerObj->getModelClass(), innerObj->getScale(), *collisionLocation });
			innerObj->setCollisionInfo({ outerObj->getModelClass(), outerObj->getScale(), *collisionLocation });
		}
	}
}

bool PhysicsEngine::detectSimpleCollision(GameObject const * const obj1, GameObject const * const obj2) const {
	// Fetch 3 points from ship
	// Calc min and max for x and y
	// -> now we have w and h of crop box

	// To translate crop box to correct location, we have to 
	// - calc center of 3 points from ship
	// - calc center of crop box
	// - translate center of crop box to origin
	// - translate crop box to center of ship
	Vec2 a1, a2;

	if (obj1->getModelClass() == ModelClass::CLASS_SHIP) {
		Vec2 p1 = Vec2(ModelData::shipVertices[0], ModelData::shipVertices[1]);
		Vec2 p2 = Vec2(ModelData::shipVertices[2], ModelData::shipVertices[3]);
		Vec2 p3 = Vec2(ModelData::shipVertices[4], ModelData::shipVertices[5]);

		Mat4 transformation = obj1->getRenderUnit().transformation;

		p1 = transformation.transform(p1);
		p2 = transformation.transform(p2);
		p3 = transformation.transform(p3);

		double wMin = customMath::min(customMath::min(p1.x, p2.x), p3.x);
		double wMax = customMath::max(customMath::max(p1.x, p2.x), p3.x);
		double hMin = customMath::min(customMath::min(p1.y, p2.y), p3.y);
		double hMax = customMath::max(customMath::max(p1.y, p2.y), p3.y);

		a1 = Vec2((float) wMin, (float) hMin);
		a2 = Vec2((float) hMin, (float) hMax);
	} else {
		Dimension dimObj1 = ModelData::getCropBox(obj1->getModelClass(), 1);

		Vec2 scaling1 = Vec2(obj1->getScale() * dimObj1.width, obj1->getScale() * dimObj1.height);
		Mat4 transformation1 = Mat4::getTransformation(obj1->getPosition(), scaling1);

		a1 = transformation1.transform(Vec2(0, 0));
		a2 = transformation1.transform(Vec2(1, 1));
	}

	Dimension dimObj2 = ModelData::getCropBox(obj2->getModelClass(), 1);

	Vec2 scaling2 = Vec2(obj2->getScale() * dimObj2.width, obj2->getScale() * dimObj2.height);
	Mat4 transformation2 = Mat4::getTransformation(obj2->getPosition(), scaling2);

	Vec2 b1 = transformation2.transform(Vec2(0, 0));
	Vec2 b2 = transformation2.transform(Vec2(1, 1));

	if (a1.x < b2.x && a2.x > b1.x &&
		a1.y < b2.y && a2.y > b1.y) {
		return true;
	}

	return false;
}

Vec2* PhysicsEngine::detectComplexCollision(GameObject const * const obj1, GameObject const * const obj2) const {
	VertexData outerVertexData = modelData.getBindable(obj1->getModel()).vertexData;
	VertexData innerVertexData = modelData.getBindable(obj2->getModel()).vertexData;

	Mat4 outerTransformation = obj1->getRenderUnit().transformation;
	Mat4 innerTransformation = obj2->getRenderUnit().transformation;

	vector<Vec2> outerVertices = getTransformedVertices(outerVertexData, outerTransformation);
	vector<Vec2> innerVertices = getTransformedVertices(innerVertexData, innerTransformation);

	IndexData innerTriangleIndexData = modelData.getTriangulatedModelData(obj2->getModel());
	vector<Triangle> innerTriangles = convertVerticesToTriangles(innerVertices, innerTriangleIndexData);

	// Now, we have to check, if any vertex from outerVertices 
	// intersects with any triangle from innerTriangles#

	return detectTrianglePointIntersection(outerVertices, innerTriangles);
}

Vec2* PhysicsEngine::detectTrianglePointIntersection(const vector<Vec2> vertices, const vector<Triangle> triangles) const {
	for each (Vec2 vertex in vertices) {
		for each (Triangle triangle in triangles) {
			bool hasIntersection = detectTrianglePointIntersection(vertex, triangle);

			if (hasIntersection)
				return new Vec2(vertex.x, vertex.y);
		}
	}

	return nullptr;
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