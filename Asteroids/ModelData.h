#ifndef MODEL_DATA
#define MODEL_DATA

#include <map>

#include "Util.h"
#include "structs.h"

using namespace Binding;
using namespace PhysX;

class ModelData {

public:

	struct Data {
		VertexData vertexData;
		IndexData triangulatedIndexData;
	};

	static void clear();

	static const Dimension ASTEROID_CROP_BOX;
	static const Dimension SHIP_CROP_BOX;
	static const Dimension SAUCER_CROP_BOX;
	static const Dimension LINE_SEGMENT_CROP_BOX;
	static const Vec2 SHIP_CENTER;

	// The following float arrays define the vertices of each single model
	static const float a1Vertices[];
	static const float a2Vertices[];
	static const float a3Vertices[];
	static const float a4Vertices[];
	static const float shipVertices[];
	static const float saucerVertices[];
	static const float shipMovingVertices[];
	static const float particleVertices[];
	static const float lineSegmentVertices[];

	// For collision detection, we triangulate each model and store
	// the indices of each single triangle
	static const int a1Triangles[];
	static const int a2Triangles[];
	static const int a3Triangles[];
	static const int a4Triangles[];
	static const int shipTriangles[];
	static const int saucerTriangles[];
	static const int particleTriangles[];

	// In order to process the vertex data defined above, we have to know how
	// many vertices exists per model
	static const int a1VertexCount;
	static const int a2VertexCount;
	static const int a3VertexCount;
	static const int a4VertexCount;
	static const int shipVertexCount;
	static const int saucerVertexCount;
	static const int shipMovingVertexCount;
	static const int particleVertexCount;
	static const int lineSegmentVertexCount;

	static const int attributeSizes[];

	static Bindable getBindable(const Model model);
	static IndexData getTriangulatedIndexData(const Model model);
	static Dimension getCropBox(const ModelClass modelClass, const float scale);

private:

	static const map<Model, Data> dataMap;
	static const map<Model, Bindable> bindings;
	static IndexData calcIndices(const int vertexCount);

};

#endif MODEL_DATA