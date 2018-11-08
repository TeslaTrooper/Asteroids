#ifndef UTIL
#define UTIL

#include "Mat4.h"

#define VERTEX_COMP_SIZE 2

struct Dimension {
	int width;
	int height;
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
};

enum Model {
	ASTEROID1, ASTEROID2, ASTEROID3, ASTEROID4, SHIP, SAUCER,
	CHARA, CHAR0, CHAR1,
	CHAR2, CHAR3, CHAR4,
	CHAR5, CHAR6, CHAR7,
	CHAR8, CHAR9
};

enum RenderUnitType {
	UI, GAME_OBJECT
};

struct RenderUnit {
	Mat4 transformation;
	Model model;
};

#endif UTIL