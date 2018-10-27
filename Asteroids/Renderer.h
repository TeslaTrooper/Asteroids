#ifndef RENDERER
#define RENDERER

#include "ShaderProgram.h"
#include "Shader.h"
#include "Game.h"
#include "Util.h"
#include "ModelData.h"

class Renderer {

	Game* game;

	GLuint shaderProgramID;
	Shader* shader;
	ModelData asteriod1, asteriod2;

	int configureBuffers(const VertexData& vertexData, const IndexData& indexData);
	void loadModelData();
	IndexData calcIndices(const float* vertexData, int arraySize);

public:
	Renderer();
	~Renderer();

	void render(const float dt);

	void setProjection(const Mat4 projection);
};

#endif RENDERER