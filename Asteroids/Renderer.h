#ifndef RENDERER
#define RENDERER

#include <map>

#include "ShaderProgram.h"
#include "Shader.h"
#include "Game.h"
#include "Util.h"
#include "ModelData.h"

class Renderer {

	struct BufferData {
		unsigned int vao;
		unsigned int ebo;
		unsigned int vbo;
		int indexCount;
	};

	Game* game;

	GLuint shaderProgramID;
	Shader* shader;
	map<Model, BufferData> modelMap;

	BufferData configureBuffers(const VertexData& vertexData, const IndexData& indexData);
	void loadModelDatas();
	void loadModelData(Model model);

public:
	Renderer();
	~Renderer();

	void render(const float dt);

	void setProjection(const Mat4 projection);
};

#endif RENDERER