#ifndef UTIL
#define UTIL

struct Dimension {
	int width;
	int height;
};

struct ModelData {
	int vao;
	int indexCount;
};

struct IndexData {
	int* indices;
	int count;
};

struct VertexData {
	const float* vertices;
	int count;
};

#endif UTIL