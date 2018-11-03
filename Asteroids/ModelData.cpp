#include "ModelData.h"

const Vec2 ModelData::CROP_BOX = Vec2(100.f, 100.f);

const float ModelData::a1Vertices[] = {
	0, 26,
	20.5, 0,
	32, 10.5,
	70, 0,
	100, 32.5,
	70, 52.5,
	100, 75.5,
	72.5, 100,
	43.5, 80,
	22.5, 100,
	0, 74,
	20.5, 50
};
const int ModelData::a1VertexCount = 12;

const float ModelData::a2Vertices[] = {
	6, 94,
	58, 94,
	47, 110,
	69, 110,
	98, 97,
	98, 90,
	52, 81,
	96, 64,
	75, 47,
	53, 57,
	23, 43,
	6, 74,
};
const int ModelData::a2VertexCount = 12;


ModelData::ModelData() {
	vertexDataMap[Model::ASTEROID1] = { a1Vertices, a1VertexCount };
	vertexDataMap[Model::ASTEROID2] = { a2Vertices, a2VertexCount };
}

ModelData::~ModelData() {
	delete[] &a1Vertices;
	delete[] &a2Vertices;
}

Bindable ModelData::getBindable(const Model model) const {
	VertexData vertexData = vertexDataMap.at(model);
	IndexData indexData = calcIndices(vertexData.count);

	return { vertexData, indexData };
}

IndexData ModelData::calcIndices(const int vertexCount) const {
	int* indices = new int[vertexCount * VERTEX_COMP_SIZE];

	for (int i = 0, j = 0; i < vertexCount; i++, j += 2) {
		indices[j] = i;
		indices[j + 1] = (i + 1) % vertexCount;
	}

	return { indices, vertexCount * 2 };
}