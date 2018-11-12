#include "ModelData.h"

const Dimension ModelData::ASTEROID_CROP_BOX = { 150, 100 };
const Dimension ModelData::SHIP_CROP_BOX = { 40, 17 };
const Dimension ModelData::SAUCER_CROP_BOX = { 45, 20 };

const float ModelData::a1Vertices[] = {
	0, 25,
	15, 50,
	0, 75,
	35, 100,
	60, 80,
	95, 100,
	125, 72,
	90, 58,
	125, 38,
	95, 0,
	50, 15,
	33, 0
};
const int ModelData::a1VertexCount = 12;

const float ModelData::a2Vertices[] = {
	27, 0,
	0, 38,
	0, 75,
	50, 75,
	27, 100,
	75, 100,
	125, 70,
	125, 57,
	70, 45,
	125, 25,
	100, 0,
	70, 15
};
const int ModelData::a2VertexCount = 12;

const float ModelData::a3Vertices[] = {
	20, 0,
	0, 35,
	22, 45,
	0, 55,
	40, 100,
	95, 100,
	125, 65,
	125, 45,
	80, 0,
	40, 0,
	45, 30,
};
const int ModelData::a3VertexCount = 11;

const float ModelData::a4Vertices[] = {
	25, 0,
	0, 25,
	0, 75,
	30, 100,
	65, 75,
	95, 100,
	125, 78,
	105, 50,
	125, 30,
	75, 0,
};
const int ModelData::a4VertexCount = 10;

const float ModelData::shipVertices[] = {
	40, 0,
	0, 8.5f,
	40, 17,
	30, 14.9f,
	30, 2.09f
};
const int ModelData::shipVertexCount = 5;

const float ModelData::saucerVertices[] = {
	32.5f, 13.5f,
	27.5f, 20,
	17.5f, 20,
	12.5f, 13.5f,
	32.5f, 13.5f,
	45, 7,
	34.5f, 0,
	10.5f, 0,
	0, 7,
	45, 7,
	32.5f, 13.5f,
	12.5f, 13.5f,
	0, 7,
	12.5f, 13.5f
};
const int ModelData::saucerVertexCount = 14;


ModelData::ModelData() {
	vertexDataMap[Model::ASTEROID1] = { a1Vertices, a1VertexCount };
	vertexDataMap[Model::ASTEROID2] = { a2Vertices, a2VertexCount };
	vertexDataMap[Model::ASTEROID3] = { a3Vertices, a3VertexCount };
	vertexDataMap[Model::ASTEROID4] = { a4Vertices, a4VertexCount };
	vertexDataMap[Model::SHIP] = { shipVertices, shipVertexCount };
	vertexDataMap[Model::SAUCER] = { saucerVertices, saucerVertexCount };
}

ModelData::~ModelData() {
	delete[] &a1Vertices;
	delete[] &a2Vertices;
	delete[] &a3Vertices;
	delete[] &a4Vertices;
	delete[] &shipVertices;
	delete[] &saucerVertices;
}

Bindable ModelData::getBindable(const Model model) const {
	VertexData vertexData = vertexDataMap.at(model);
	IndexData indexData = calcIndices(vertexData.count);

	if (model == Model::SHIP) {
		return{ vertexData, indexData, SHIP_CROP_BOX };
	}

	if (model == Model::SAUCER) {
		return{ vertexData, indexData, SAUCER_CROP_BOX };
	}

	return { vertexData, indexData, ASTEROID_CROP_BOX };
}

IndexData ModelData::calcIndices(const int vertexCount) const {
	int* indices = new int[vertexCount * VERTEX_COMP_SIZE];

	for (int i = 0, j = 0; i < vertexCount; i++, j += 2) {
		indices[j] = i;
		indices[j + 1] = (i + 1) % vertexCount;
	}

	return { indices, vertexCount * 2 };
}