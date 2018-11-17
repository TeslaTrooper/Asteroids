#ifndef UTIL
#define UTIL

#include <vector>
#include "Mat4.h"

#define VERTEX_COMP_SIZE 2

enum Model {
	ASTEROID1, ASTEROID2, ASTEROID3, ASTEROID4, SHIP, SAUCER,
	CHARA, CHAR0, CHAR1,
	CHAR2, CHAR3, CHAR4,
	CHAR5, CHAR6, CHAR7,
	CHAR8, CHAR9
};

struct Dimension {
	float width;
	float height;
};

struct IndexData {
	const int* indices;
	int count;
};

struct VertexData {
	const float* vertices;
	int count;
};

struct Bindable {
	VertexData vertexData;
	IndexData indexData;
	Dimension cropBox;
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

static Vec2 operator+(const Vec2& vec1, const Vec2& vec2) {
	return Vec2(vec1.x + vec2.x, vec1.y + vec2.y);
};

static Vec2 operator*(const float scalar, const Vec2& vec) {
	return Vec2(vec.x * scalar, vec.y * scalar);
};

static Vec2 operator*(const Vec2& vec, const float scalar) {
	return Vec2(vec.x * scalar, vec.y * scalar);
};

static vector<Vec2> getTransformedVertices(const VertexData& vertexData, const Mat4& transformtion) {
	vector<Vec2> transformedVertices;

	for (int i = 0; i < vertexData.count * 2; i += VERTEX_COMP_SIZE) {
		Vec2 tmpVec = Vec2(vertexData.vertices[i], vertexData.vertices[i + 1]);
		transformedVertices.push_back(transformtion.transform(tmpVec));
	}

	return transformedVertices;
}

static vector<Triangle> convertVerticesToTriangles(const vector<Vec2> vertices, const IndexData& indexData) {
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