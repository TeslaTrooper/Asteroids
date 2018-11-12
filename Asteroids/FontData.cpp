#include "FontData.h"

const float FontData::w = 3.6f;
const float FontData::h = 5.3f;
const float FontData::a = 0.7f;
const float FontData::b = (h / 2.0f) + (a / 2.0f);
const float FontData::c = (h / 2.0f) - (a / 2.0f);
const float FontData::GLYPH_GAP_RATIO = 0.2f;

const float FontData::charAVertices[] = {
	0, 0,
	0, 3.7f,
	1.69f, 5.31f,
	1.93f, 5.31f,
	3.63f, 3.7f,
	3.63f, 0,
	3.28f, 0,
	3.28f, 1.6f,
	0.35f, 1.6f,
	0.35f, 0,
	0.35f, 1.95f,
	3.28f, 1.95f,
	3.28f, 3.5f,
	1.81f, 4.96f,
	0.35f, 3.58f
};
const int FontData::charAVertexCount = 15;

const int FontData::charAIndices[] = {
	0,1,9,9,1,14,14,1,13,13,1,2,2,3,13,13,3,12,12,3,4,4,5,12,12,5,6,7,8,11,11,8,10
};
const int FontData::charAIndexCount = 33;

const float FontData::char0Vertices[] = {
	0, 0,
	0, h,
	w, h,
	w, 0,
	w-a, a,
	a, a,
	a, h-a,
	w-a, h-a
};
const int FontData::char0VertexCount = 8;

const int FontData::char0Indices[] = {
	0,1,5,5,1,6,6,1,2,2,7,6,2,4,7,2,3,4,4,3,0,4,0,5
};
const int FontData::char0IndexCount = 24;

const float FontData::char1Vertices[] = {
	(w/2.0f)-(a/2.0f), 0,
	(w / 2.0f) - (a / 2.0f), h,
	(w / 2.0f) + (a / 2.0f), h,
	(w / 2.0f) + (a / 2.0f), 0
};
const int FontData::char1VertexCount = 4;

const int FontData::char1Indices[] = {
	0,1,2,0,2,3
};
const int FontData::char1IndexCount = 6;

const float FontData::char2Vertices[] = {
	0, 0,
	0, b,
	w-a, b,
	w-a, h-a,
	0, h-a,
	0, h,
	w, h,
	w, c,
	a, c,
	a, a,
	w, a,
	w, 0
};
const int FontData::char2VertexCount = 12;

const int FontData::char2Indices[] = {
	0,1,9,0,9,10,0,10,11,1,8,9,1,7,8,1,2,7,2,6,7,2,3,6,3,4,5,3,5,6
};
const int FontData::char2IndexCount = 30;

const float FontData::char3Vertices[] = {
	0, 0,
	0, a,
	w-a, a,
	w-a, c,
	0, c,
	0, b,
	w-a, b,
	w-a, h-a,
	0, h-a,
	0, h,
	w, h,
	w, 0
};
const int FontData::char3VertexCount = 12;

const int FontData::char3Indices[] = {
	0,1,2,0,2,11,11,2,6,3,4,6,4,5,6,11,6,10,6,7,10,7,8,9,7,9,10
};
const int FontData::char3IndexCount = 27;

const float FontData::char4Vertices[] = {
	0, c,
	0, h,
	a, h,
	a, b,
	w-a, b,
	w-a, h,
	w, h,
	w, 0,
	w-a, 0,
	w-a, c
};
const int FontData::char4VertexCount = 10;

const int FontData::char4Indices[] = {
	0,1,3,1,2,3,0,3,9,9,3,4,8,5,6,8,6,7
};
const int FontData::char4IndexCount = 18;

const float FontData::char5Vertices[] = {
	w, 0,
	w, b,
	a, b,
	a, h - a,
	w, h - a,
	w, h,
	0, h,
	0, c,
	w-a, c,
	w-a, a,
	0, a,
	0, 0
};
const int FontData::char5VertexCount = 12;

const int FontData::char5Indices[] = {
	0,1,9,0,9,10,0,10,11,1,8,9,1,7,8,1,2,7,2,6,7,2,3,6,3,4,5,3,5,6
};
const int FontData::char5IndexCount = 30;

const float FontData::char6Vertices[] = {
	0, 0,
	0, h,
	a, h,
	a, b,
	w, b,
	w, 0,
	a, a,
	a, c,
	w - a, c,
	w - a, a
};
const int FontData::char6VertexCount = 10;

const int FontData::char6Indices[] = {
	0,1,2,0,2,6,0,6,5,6,9,5,5,9,8,5,8,4,8,7,3,8,3,4
};
const int FontData::char6IndexCount = 24;

const float FontData::char7Vertices[] = {
	0, h - a,
	0, h,
	w, h,
	w, 0,
	w - a, 0,
	w - a, h - a
};
const int FontData::char7VertexCount = 6;

const int FontData::char7Indices[] = {
	0,1,5,5,1,2,5,2,4,4,2,3
};
const int FontData::char7IndexCount = 12;

const float FontData::char8Vertices[] = {
	0, 0,
	0, h,
	w, h,
	w, 0,
	a, a,
	a, c,
	w-a, c,
	w-a, a,
	a, b,
	a, h-a,
	w-a, h-a,
	w-a, b
};
const int FontData::char8VertexCount = 12;

const int FontData::char8Indices[] = {
	0,1,4,4,1,5,5,1,8,8,1,9,9,1,10,10,1,2,10,2,11,11,2,6,6,2,7,7,2,3,4,7,3,3,0,4,5,8,6,6,8,11
};
const int FontData::char8IndexCount = 42;

const float FontData::char9Vertices[] = {
	w, h,
	w, 0,
	w-a, 0,
	w-a, h-b,
	0, h-b,
	0, h,
	w-a, h-a,
	w-a, h-c,
	a, h-c,
	a, h-a
};
const int FontData::char9VertexCount = 10;

const int FontData::char9Indices[] = {
	0,1,2,0,2,6,0,6,5,6,9,5,5,9,8,5,8,4,8,7,3,8,3,4
};
const int FontData::char9IndexCount = 24;

FontData::FontData() {
	vertexDataMap[Model::CHARA] = { { charAVertices, charAVertexCount },{ charAIndices, charAIndexCount } };
	vertexDataMap[Model::CHAR0] = { { char0Vertices, char0VertexCount },{ char0Indices, char0IndexCount } };
	vertexDataMap[Model::CHAR1] = { { char1Vertices, char1VertexCount },{ char1Indices, char1IndexCount } };
	vertexDataMap[Model::CHAR2] = { { char2Vertices, char2VertexCount },{ char2Indices, char2IndexCount } };
	vertexDataMap[Model::CHAR3] = { { char3Vertices, char3VertexCount },{ char3Indices, char3IndexCount } };
	vertexDataMap[Model::CHAR4] = { { char4Vertices, char4VertexCount },{ char4Indices, char4IndexCount } };
	vertexDataMap[Model::CHAR5] = { { char5Vertices, char5VertexCount },{ char5Indices, char5IndexCount } };
	vertexDataMap[Model::CHAR6] = { { char6Vertices, char6VertexCount },{ char6Indices, char6IndexCount } };
	vertexDataMap[Model::CHAR7] = { { char7Vertices, char7VertexCount },{ char7Indices, char7IndexCount } };
	vertexDataMap[Model::CHAR8] = { { char8Vertices, char8VertexCount },{ char8Indices, char8IndexCount } };
	vertexDataMap[Model::CHAR9] = { { char9Vertices, char9VertexCount },{ char9Indices, char9IndexCount } };
}

FontData::~FontData() {
	delete[] & charAVertices;
	delete[] & charAIndices;

	delete[] & char0Vertices;
	delete[] & char0Indices;

	delete[] & char1Vertices;
	delete[] & char1Indices;

	delete[] & char2Vertices;
	delete[] & char2Indices;

	delete[] & char3Vertices;
	delete[] & char3Indices;

	delete[] & char4Vertices;
	delete[] & char4Indices;

	delete[] & char5Vertices;
	delete[] & char5Indices;

	delete[] & char6Vertices;
	delete[] & char6Indices;

	delete[] & char7Vertices;
	delete[] & char7Indices;

	delete[] & char8Vertices;
	delete[] & char8Indices;

	delete[] & char9Vertices;
	delete[] & char9Indices;
}

Bindable FontData::getBindable(const Model character) const {
	Bindable bindable = vertexDataMap.at(character);
	bindable.cropBox = { w, h };

	return bindable;
}
