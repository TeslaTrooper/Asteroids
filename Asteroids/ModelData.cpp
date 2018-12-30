#include "ModelData.h"

const Dimension ModelData::ASTEROID_CROP_BOX = { 150, 100 };
const Dimension ModelData::SHIP_CROP_BOX = { 40, 17 };
const Dimension ModelData::SAUCER_CROP_BOX = { 45, 20 };
const Vec2 ModelData::SHIP_CENTER = { 20.f, 8.5f };
const Dimension ModelData::LINE_SEGMENT_CROP_BOX = { 30.f, 1.f };

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
const int ModelData::a1Triangles[] = {
	0, 1, 11,
	1, 4, 11,
	1, 2, 3,
	1, 3, 4,
	4, 10, 11,
	4, 9, 10,
	4, 7, 9,
	4, 5, 7,
	5, 6, 7,
	7, 8, 9
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
const int ModelData::a2Triangles[] = {
	0, 1, 11,
	1, 2, 8,
	2, 3, 8,
	1, 8, 11,
	8, 10, 11,
	8, 9, 10,
	3, 7, 8,
	3, 6, 7,
	3, 5, 6,
	3, 4, 5
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
const int ModelData::a3Triangles[] = {
	0, 1, 10,
	1, 2, 10,
	2, 4, 10,
	2, 3, 4,
	4, 5, 10,
	5, 6, 10,
	6, 7, 10,
	7, 8, 10,
	8, 9, 10
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
const int ModelData::a4Triangles[] = {
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	4, 5, 6,
	4, 6, 7,
	4, 7, 8,
	4, 8, 9,
	0, 4, 9
};
const int ModelData::a4VertexCount = 10;

const float ModelData::shipVertices[] = {
	40, 0,
	0, 8.5f,
	40, 17,
	30, 14.9f,
	30, 2.09f
};
const int ModelData::shipTriangles[] = {
	1, 3, 4,
	0, 4, 3,
	2, 3, 4
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
const int ModelData::saucerTriangles[] = {
	1, 2, 3,
	0, 3, 1,
	0, 5, 3,
	5, 6, 3,
	3, 6, 7,
	3, 7, 8
};
const int ModelData::saucerVertexCount = 14;

const float ModelData::shipMovingVertices[] = {
	40, 0,
	0, 8.5f,
	40, 17,
	30, 14.9f,
	30, 2.09f,
	30, 5,
	37, 8.5f,
	30, 12.5f,
	30, 2.09f,
};
const int ModelData::shipMovingVertexCount = 9;

const float ModelData::particleVertices[] = {
	0, 0,
	1, 0,
	1, 1,
	0, 1
};
const int ModelData::particleTriangles[] = {
	0, 2, 1,
	0, 3, 2
};
const int ModelData::particleVertexCount = 4;

const float ModelData::lineSegmentVertices[] = {
	0, 0,
	30, 0,
};
const int ModelData::lineSegmentVertexCount = 2;

const int ModelData::attributeSizes[] = {
	2
};

const map<Model, ModelData::Data> ModelData::dataMap = {
	{ Model::ASTEROID1, { { ModelData::a1Vertices, VERTEX_COMP_SIZE, ModelData::a1VertexCount }, { ModelData::a1Triangles, 30 } } },
	{ Model::ASTEROID2, { { ModelData::a2Vertices, VERTEX_COMP_SIZE, ModelData::a2VertexCount }, { ModelData::a2Triangles, 30 } } },
	{ Model::ASTEROID3, { { ModelData::a3Vertices, VERTEX_COMP_SIZE, ModelData::a3VertexCount }, { ModelData::a3Triangles, 27 } } },
	{ Model::ASTEROID4, { { ModelData::a4Vertices, VERTEX_COMP_SIZE,  ModelData::a4VertexCount }, { ModelData::a4Triangles, 24 } } },
	{ Model::SHIP, { { ModelData::shipVertices, VERTEX_COMP_SIZE, ModelData::shipVertexCount }, { ModelData::shipTriangles, 9 } } },
	{ Model::SAUCER, { { ModelData::saucerVertices, VERTEX_COMP_SIZE, ModelData::saucerVertexCount }, { ModelData::saucerTriangles, 18 } } },
	{ Model::SHIP_MOVING, { { ModelData::shipMovingVertices, VERTEX_COMP_SIZE, ModelData::shipMovingVertexCount }, { ModelData::shipTriangles, 9 } } },
	{ Model::PROJECTILE, { { ModelData::particleVertices, VERTEX_COMP_SIZE, ModelData::particleVertexCount }, { ModelData::particleTriangles, 6 } } },
	{ Model::LINE_SEGMENT, { { ModelData::lineSegmentVertices, VERTEX_COMP_SIZE, ModelData::lineSegmentVertexCount } } }
};

const map<Model, Bindable> ModelData::bindings = {
	{ Model::ASTEROID1, { dataMap.at(Model::ASTEROID1).vertexData, calcIndices(dataMap.at(Model::ASTEROID1).vertexData.count), { attributeSizes, 1 } } },
	{ Model::ASTEROID2, { dataMap.at(Model::ASTEROID2).vertexData, calcIndices(dataMap.at(Model::ASTEROID2).vertexData.count), { attributeSizes, 1 } } },
	{ Model::ASTEROID3, { dataMap.at(Model::ASTEROID3).vertexData, calcIndices(dataMap.at(Model::ASTEROID3).vertexData.count), { attributeSizes, 1 } } },
	{ Model::ASTEROID4, { dataMap.at(Model::ASTEROID4).vertexData, calcIndices(dataMap.at(Model::ASTEROID4).vertexData.count), { attributeSizes, 1 } } },
	{ Model::SHIP, { dataMap.at(Model::SHIP).vertexData, calcIndices(dataMap.at(Model::SHIP).vertexData.count), { attributeSizes, 1 } } },
	{ Model::SAUCER, { dataMap.at(Model::SAUCER).vertexData, calcIndices(dataMap.at(Model::SAUCER).vertexData.count), { attributeSizes, 1 } } },
	{ Model::SHIP_MOVING, { dataMap.at(Model::SHIP_MOVING).vertexData, calcIndices(dataMap.at(Model::SHIP_MOVING).vertexData.count), { attributeSizes, 1 } } },
	{ Model::PROJECTILE, { dataMap.at(Model::PROJECTILE).vertexData, calcIndices(dataMap.at(Model::PROJECTILE).vertexData.count), { attributeSizes, 1 } } },
	{ Model::LINE_SEGMENT, { dataMap.at(Model::LINE_SEGMENT).vertexData, calcIndices(dataMap.at(Model::LINE_SEGMENT).vertexData.count), { attributeSizes, 1 } } }
};

void ModelData::clear() {
	delete[] & a1Vertices;
	delete[] & a2Vertices;
	delete[] & a3Vertices;
	delete[] & a4Vertices;
	delete[] & shipVertices;
	delete[] & saucerVertices;
}

Bindable ModelData::getBindable(const Model model) {
	return bindings.at(model);
}

IndexData ModelData::getTriangulatedIndexData(const Model model) {
	return dataMap.at(model).triangulatedIndexData;
}

IndexData ModelData::calcIndices(const int vertexCount) {
	int* indices = new int[vertexCount * VERTEX_COMP_SIZE];

	for (int i = 0, j = 0; i < vertexCount; i++, j += 2) {
		indices[j] = i;
		indices[j + 1] = (i + 1) % vertexCount;
	}

	return { indices, vertexCount * 2 };
}

Dimension ModelData::getCropBox(const ModelClass modelClass, const float scale) {
	switch (modelClass) {
		case ModelClass::CLASS_ASTEROID: return ASTEROID_CROP_BOX * scale;
		case ModelClass::CLASS_SHIP: return SHIP_CROP_BOX * scale;
		case ModelClass::CLASS_SAUCER: return SAUCER_CROP_BOX * scale;
		case ModelClass::CLASS_LINE_SEGMENT: return LINE_SEGMENT_CROP_BOX * scale;
		default: return Dimension();
	}
}