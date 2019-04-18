#include "Renderer.h"

void Renderer::setup() {
	standardShader = ShaderFactory::createShader("shader.vert", "shader.frag");
	framebufferShader = ShaderFactory::createShader("framebufferShader.vert", "framebufferShader.frag");

	initProjection();
	createFrameBuffer(WIN_WIDTH, WIN_HEIGHT);
	loadModelDatas();
}

void Renderer::initProjection() const {
	standardShader->use();
	standardShader->setUniformMatrix4(PROJECTION, Projection::getOrthographicProjection(WIN_WIDTH, WIN_HEIGHT));
}

void Renderer::render() const {
	vector<RenderUnit> units = game->getRenderUnits();
	for each (RenderUnit unit in units) {
		prepareShaders(unit);

		BaseOpenGLRenderer::draw(modelMap.at(unit.model));
	}

	framebufferShader->use();
}

void Renderer::prepareShaders(const RenderUnit unit) const {
	standardShader->use();
	standardShader->setUniformMatrix4(TRANSFORM, unit.transformation);
}

void Renderer::loadModelDatas() {
	loadModelData(Model::ASTEROID1, DRAW_MODE_LINE);
	loadModelData(Model::ASTEROID2, DRAW_MODE_LINE);
	loadModelData(Model::ASTEROID3, DRAW_MODE_LINE);
	loadModelData(Model::ASTEROID4, DRAW_MODE_LINE);
	loadModelData(Model::SHIP, DRAW_MODE_LINE);
	loadModelData(Model::SAUCER, DRAW_MODE_LINE);
	loadModelData(Model::SHIP_MOVING, DRAW_MODE_LINE);
	loadModelData(Model::PROJECTILE, DRAW_MODE_LINE);
	loadModelData(Model::LINE_SEGMENT, DRAW_MODE_LINE);

	loadModelData(Model::CHARA, DRAW_MODE_TRIANGLES);
	loadModelData(Model::CHAR0, DRAW_MODE_TRIANGLES);
	loadModelData(Model::CHAR1, DRAW_MODE_TRIANGLES);
	loadModelData(Model::CHAR2, DRAW_MODE_TRIANGLES);
	loadModelData(Model::CHAR3, DRAW_MODE_TRIANGLES);
	loadModelData(Model::CHAR4, DRAW_MODE_TRIANGLES);
	loadModelData(Model::CHAR5, DRAW_MODE_TRIANGLES);
	loadModelData(Model::CHAR6, DRAW_MODE_TRIANGLES);
	loadModelData(Model::CHAR7, DRAW_MODE_TRIANGLES);
	loadModelData(Model::CHAR8, DRAW_MODE_TRIANGLES);
	loadModelData(Model::CHAR9, DRAW_MODE_TRIANGLES);
}

void Renderer::loadModelData(const Model model, const int drawMode) {
	Bindable bindable = game->getBindable(model);
	RenderData data = configure(bindable, drawMode);

	modelMap[model] = data;
}

Renderer::~Renderer() {
	delete standardShader;
	delete framebufferShader;
	delete game;
}