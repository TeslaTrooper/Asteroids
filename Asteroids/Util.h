#ifndef UTIL
#define UTIL

#include "Mat4.h"

#define VERTEX_COMP_SIZE 2

struct Dimension {
	int width;
	int height;
};

struct IndexData {
	int* indices;
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
	ASTEROID1, ASTEROID2
};


struct RenderUnit {
	Mat4 transformation;
	Model model;
};

#endif UTIL