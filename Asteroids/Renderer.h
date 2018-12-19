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

class RenderData {

};

class Renderer : public BaseOpenGLRenderer {

	Game* game;

	Shader* standardShader;
	Shader* framebufferShader;

	BufferConfigurator::FrameBuffer framebuffer;
	BufferConfigurator::BufferData screenQuad;
	BufferConfigurator bufferConfigurator;
	map<Model, CustomBufferData> modelMap;

	void loadModelDatas();
	void loadModelData(const Model model, const int drawMode);
	void drawInDebugMode(const CustomBufferData& data) const;

public:
	Renderer(Game* const game);
	~Renderer();

	void render(const float dt) const;
	void endDraw() const override;
	void prepareShaders(const RenderUnit) const;
	void setProjection(const Mat4 projection) const;
};

#endif RENDERER