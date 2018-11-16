#ifndef UTIL
#define UTIL

#include <vector>
#include "Mat4.h"

#define VERTEX_COMP_SIZE 2

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

enum Model {
	ASTEROID1, ASTEROID2, ASTEROID3, ASTEROID4, SHIP, SAUCER,
	CHARA, CHAR0, CHAR1,
	CHAR2, CHAR3, CHAR4,
	CHAR5, CHAR6, CHAR7,
	CHAR8, CHAR9
};

struct RenderUnit {
	Mat4 transformation;
	Model model;
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

static float getArea(const vector<Vec2> triangle) {
	if (triangle.size() != 3) {
		printf("Unable to calculate area. Vertex size is %i", triangle.size());
		return -1;
	}

	Vec2 pivot = triangle.at(0);

	Vec2 edge1 = triangle.at(1).sub(pivot);
	Vec2 edge2 = triangle.at(2).sub(pivot);

	Vec2 cross = edge1.cross(edge2);

	return cross.length() / 2.f;
}

#endif UTIL