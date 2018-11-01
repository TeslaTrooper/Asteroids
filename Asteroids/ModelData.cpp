#include "ModelData.h"

const float ModelData::a1Vertices[] = {
	21, 47,
	36, 68,
	22, 87,
	44, 106,
	65, 103,
	92, 115,
	118, 106,
	84, 90,
	115, 71,
	80, 39,
	55, 45,
	46, 36,
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
	vertexDataMap = map<Model, VertexData>();

	vertexDataMap[Model::ASTEROID1] = { a1Vertices, a1VertexCount };
	vertexDataMap[Model::ASTEROID2] = { a2Vertices, a2VertexCount };
}

ModelData::~ModelData() {
	delete[] a1Vertices;
	delete[] a2Vertices;
}

Bindable ModelData::getBindable(Model model) {
	VertexData vertexData = vertexDataMap[model];
	IndexData indexData = calcIndices(vertexData.count);

	return { vertexData, indexData };
}

IndexData ModelData::calcIndices(const int vertexCount) {
	int* indices = new int[vertexCount * VERTEX_COMP_SIZE];

	for (int i = 0, j = 0; i < vertexCount; i++, j += 2) {
		indices[j] = i;
		indices[j + 1] = (i + 1) % vertexCount;
	}

	return { indices, vertexCount };
}