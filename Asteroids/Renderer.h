#ifndef RENDERER
#define RENDERER

#include <map>

#include "ShaderProgram.h"
#include "Shader.h"
#include "Game.h"
#include "Util.h"
#include "ModelData.h"
#include "BufferConfigurator.h"

class Renderer {

	Game game;

	GLuint shaderProgramID;
	Shader* shader;
	BufferConfigurator bufferConfigurator;
	map<Model, BufferConfigurator::BufferData> modelMap;

	void loadModelDatas();
	void loadModelData(const Model model, const int drawMode);
	void draw(const RenderUnit unit) const;

public:
	Renderer();
	~Renderer();

	void render(const float dt) const;

	void setProjection(const Mat4 projection) const;
};

#endif RENDERER