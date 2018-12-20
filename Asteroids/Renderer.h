#ifndef RENDERER
#define RENDERER

#include <map>

#include "ShaderProgram.h"
#include "Shader.h"
#include "Game.h"
#include "Util.h"
#include "ModelData.h"
#include "BufferConfigurator.h"
#include "BaseOpenGLRenderer.h"

#define PROJECTION "projection"
#define TRANSFORM "transform"

class Renderer : public BaseOpenGLRenderer {

	Game* game;

	Shader* standardShader;
	Shader* framebufferShader;

	map<Model, CustomBufferData> modelMap;

	void loadModelDatas();
	void loadModelData(const Model model, const int drawMode);
	void drawInDebugMode(const CustomBufferData& data) const;
	void prepareShaders(const RenderUnit) const;

	void render() const override;
	void setProjection(const Mat4 projection) const override;

public:
	Renderer(Game* const game);
	~Renderer();

};

#endif RENDERER