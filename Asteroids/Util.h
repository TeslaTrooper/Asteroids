#ifndef UTIL
#define UTIL

//#define DEBUG

#include <vector>

#include "structs.h"
#include "Mat4.h"

#define VERTEX_COMP_SIZE 2
#define WIN_WIDTH 900
#define WIN_HEIGHT 600

#define SIZE_LARGE 1.5f
#define SIZE_MEDIUM 1.f
#define SIZE_SMALL 0.5f

#define MAX_PROJECTILE 4
#define PROJECTILE_MAX_LIFETIME 1.5f
#define GAP_PROJECTILE_SHIP 10
#define PROJECTILE_SPEED 6
#define ROTATION_ZONE 45
#define ASTEROID_MIN_VELOCITY 20
#define ASTEROID_MAX_VELOCITY 50
#define ASTEROID_PIECE_COUNT 2

#define PARTICLE_COUNT 2
#define PARTICLE_MAX_LIFETIME 1
#define PARTICLE_MIN_VELOCITY 1
#define PARTICLE_MAX_VELOCITY 2

#define INITAL_ENTITY_COUNT 2
#define SMALL_SAUCER_INTERVAL 40
#define BIG_SAUCER_INTERVAL 20
#define SAUCER_MIN_VELOCITY 10
#define SAUCER_MAX_VELOCITY 30

enum ModelClass {
	CLASS_ASTEROID, CLASS_SHIP, CLASS_SAUCER, CLASS_PROJECTILE, CLASS_LINE_SEGMENT, CLASS_UNDEFINED
};

enum Model {
	ASTEROID1, ASTEROID2, ASTEROID3, ASTEROID4, SHIP, SAUCER, SHIP_MOVING, PROJECTILE, LINE_SEGMENT,
	CHARA, CHAR0, CHAR1,
	CHAR2, CHAR3, CHAR4,
	CHAR5, CHAR6, CHAR7,
	CHAR8, CHAR9
};

struct Dimension {
	float width;
	float height;
};

struct RenderUnit {
	Mat4 transformation;
	Model model;
};

struct Triangle {
	Vec2 p1, p2, p3;

	float getArea() const {
		Vec2 edge1 = p2.sub(p1);
		Vec2 edge2 = p3.sub(p1);

		Vec2 cross = edge1.cross(edge2);

		return cross.length() / 2.f;
	}
};

struct CustomBufferData {
	unsigned int vao, vao1;
	unsigned int ebo;
	unsigned int vbo;
	int indexCount, indexCount1;
	int drawMode;
};

struct CollisionInfo {
	ModelClass classOfObj;
	float objSize;
	Vec2 collisionLocation;
};

static Vec2 operator+(const Vec2& vec1, const Vec2& vec2) {
	return Vec2(vec1.x + vec2.x, vec1.y + vec2.y);
};

static Vec2 operator*(const float scalar, const Vec2& vec) {
	return Vec2(vec.x * scalar, vec.y * scalar);
};

static Vec2 operator*(const int scalar, const Vec2& vec) {
	return Vec2(vec.x * scalar, vec.y * scalar);
};

static Vec2 operator*(const Vec2& vec, const float scalar) {
	return Vec2(vec.x * scalar, vec.y * scalar);
};

static Dimension operator*(const Dimension dim, const float scale) {
	return { dim.width * scale, dim.height * scale };
}

static vector<Vec2> getTransformedVertices(const Binding::VertexData& vertexData, const Mat4& transformtion) {
	vector<Vec2> transformedVertices;

	for (int i = 0; i < vertexData.count * 2; i += VERTEX_COMP_SIZE) {
		Vec2 tmpVec = Vec2(vertexData.vertices[i], vertexData.vertices[i + 1]);
		transformedVertices.push_back(transformtion.transform(tmpVec));
	}

	return transformedVertices;
}

static vector<Triangle> convertVerticesToTriangles(const vector<Vec2> vertices, const Binding::IndexData& indexData) {
	if (indexData.count % 3 != 0) {
		printf("Wrong arguments! Unable create triangles.");
		return vector<Triangle>();
	}

	vector<Triangle> triangles;
	for (int i = 0; i < indexData.count; i += 3) {
		Vec2 p1 = vertices.at(indexData.indices[i]);
		Vec2 p2 = vertices.at(indexData.indices[i + 1]);
		Vec2 p3 = vertices.at(indexData.indices[i + 2]);

		triangles.push_back({ p1, p2, p3 });
	}

	return triangles;
}

static ModelClass getClassFromModel(const Model model) {
	switch (model) {
		case ASTEROID1:
		case ASTEROID2:
		case ASTEROID3:
		case ASTEROID4: return CLASS_ASTEROID; break;
		case SHIP:
		case SHIP_MOVING: return CLASS_SHIP; break;
		case SAUCER: return CLASS_SAUCER; break;
		case PROJECTILE: return CLASS_PROJECTILE; break;
		case LINE_SEGMENT: return CLASS_LINE_SEGMENT; break;
		default: return CLASS_ASTEROID; break;
	}
}

// Returns a random number between min and max. Note: min and max included.
static int random(const int min, const int max) {
	return rand() % (max - min + 1) + min;
}

static Vec2 getRandomPosition() {
	int x = random(0, WIN_WIDTH);
	int y = random(0, WIN_HEIGHT);

	return Vec2(x, y);
}

namespace customMath {
	// Source: https://stackoverflow.com/questions/1375882/mathematically-find-max-value-without-conditional-comparison
	static float min(const float a, const float b) {
		return ((a + b) - abs(a - b)) / 2;
	}

	static float max(const float a, const float b) {
		return ((a + b) + abs(a - b)) / 2;
	}
}

#endif UTIL