#ifndef RENDERER
#define RENDERER

#include <map>
#include <ShaderFactory.h>
#include <Shader.h>
#include <BufferConfigurator.h>
#include <BaseOpenGLRenderer.h>

#include "Game.h"
#include "Util.h"
#include "ModelData.h"

#define PROJECTION "projection"
#define TRANSFORM "transform"
#define DRAW_MODE_LINE DrawMode::LINES
#define DRAW_MODE_TRIANGLES DrawMode::TRIANGLES

class Renderer : public BaseOpenGLRenderer {

	Game* const game;

	Shader* standardShader;
	Shader* framebufferShader;

	map<Model, RenderData> modelMap;

	void loadModelDatas();
	void loadModelData(const Model model, const int drawMode);
	void prepareShaders(const RenderUnit unit) const;
	void setup(int defaultFramebufferWidth, int defaultFramebufferHeight) override;

	void render() const override;
	void initProjection() const;

public:

	Renderer(Game* const game) : game(game) {};
	~Renderer();

};

#endif RENDERER