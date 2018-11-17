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

	static const Dimension ASTEROID_CROP_BOX;
	static const Dimension SHIP_CROP_BOX;
	static const Dimension SAUCER_CROP_BOX;
	static const Vec2 SHIP_CENTER;

	// The following float arrays define the vertices of each single model
	static const float a1Vertices[];
	static const float a2Vertices[];
	static const float a3Vertices[];
	static const float a4Vertices[];
	static const float shipVertices[];
	static const float saucerVertices[];

	// For collision detection, we triangulate each model and store
	// the indices of each single triangle
	static const int a1Triangles[];

	// In order to process the vertex data defined above, we have to know how
	// many vertices exists per model
	static const int a1VertexCount;
	static const int a2VertexCount;
	static const int a3VertexCount;
	static const int a4VertexCount;
	static const int shipVertexCount;
	static const int saucerVertexCount;

	Bindable getBindable(const Model model) const;
	IndexData getTriangulatedModelData(const Model model) const;
};

#endif MODEL_DATA