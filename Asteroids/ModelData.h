#ifndef MODEL_DATA
#define MODEL_DATA

#include <map>
#include "Util.h"

using namespace std;

class ModelData {

	map<Model, VertexData> vertexDataMap;

	IndexData calcIndices(const int vertexCount) const;

public:
	ModelData();
	~ModelData();

	static const float a1Vertices[];
	static const float a2Vertices[];

	static const int a1VertexCount;
	static const int a2VertexCount;

	Bindable getBindable(const Model model) const;
};

#endif MODEL_DATA