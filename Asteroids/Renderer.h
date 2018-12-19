#ifndef RENDERER
#define RENDERER

#include <map>

#include "ShaderProgram.h"
#include "Shader.h"
#include "Game.h"
#include "Util.h"
#include "ModelData.h"
#include "BufferConfigurator.h"

#define PROJECTION "projection"
#define TRANSFORM "transform"

class Renderer {

	Game* game;

	Shader* standardShader;
	Shader* framebufferShader;

	BufferConfigurator::FrameBuffer framebuffer;
	BufferConfigurator::BufferData screenQuad;
	BufferConfigurator bufferConfigurator;
	map<Model, BufferConfigurator::BufferData> modelMap;

	void loadModelDatas();
	void loadModelData(const Model model, const int drawMode);

	void beginDraw() const;
	void draw(const RenderUnit unit) const;
	void endDraw() const;

public:
	Renderer(Game* const game);
	~Renderer();

	void render(const float dt) const;

	void setProjection(const Mat4 projection) const;
};

#endif RENDERER