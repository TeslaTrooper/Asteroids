#ifndef FONT_DATA
#define FONT_DATA

#include <map>
#include <structs.h>

#include "Util.h"

using namespace Binding;

class FontData {

	map<Model, Bindable> vertexDataMap;

	static const float charAVertices[];
	static const float char0Vertices[];
	static const float char1Vertices[];
	static const float char2Vertices[];
	static const float char3Vertices[];
	static const float char4Vertices[];
	static const float char5Vertices[];
	static const float char6Vertices[];
	static const float char7Vertices[];
	static const float char8Vertices[];
	static const float char9Vertices[];

	static const int charAIndices[];
	static const int char0Indices[];
	static const int char1Indices[];
	static const int char2Indices[];
	static const int char3Indices[];
	static const int char4Indices[];
	static const int char5Indices[];
	static const int char6Indices[];
	static const int char7Indices[];
	static const int char8Indices[];
	static const int char9Indices[];

	static const int charAVertexCount;
	static const int char0VertexCount;
	static const int char1VertexCount;
	static const int char2VertexCount;
	static const int char3VertexCount;
	static const int char4VertexCount;
	static const int char5VertexCount;
	static const int char6VertexCount;
	static const int char7VertexCount;
	static const int char8VertexCount;
	static const int char9VertexCount;

	static const int charAIndexCount;
	static const int char0IndexCount;
	static const int char1IndexCount;
	static const int char2IndexCount;
	static const int char3IndexCount;
	static const int char4IndexCount;
	static const int char5IndexCount;
	static const int char6IndexCount;
	static const int char7IndexCount;
	static const int char8IndexCount;
	static const int char9IndexCount;

	static const int attributeSizes[];

public:

	/*
	Defines glyph metrics for this font.
	w: total possible glyph width
	h: total possible glyph height
	a: thickness of glyph
	b and c: helper variables to keep calculations easy and clear
	*/
	static const float w, h, a, b, c;
	static const float GLYPH_GAP_RATIO;

	FontData();
	~FontData();

	Bindable getBindable(const Model character) const;
};

#endif FONT_DATA