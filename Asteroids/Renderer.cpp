#include "Renderer.h"

Renderer::Renderer(Game* const game) {
	this->game = game;

	ShaderProgram standardShaderProgramm;
	GLuint standardShaderID = standardShaderProgramm.createShaderProgram("shader.vert", "shader.frag");
	standardShader = new Shader(standardShaderID);

	ShaderProgram framebufferShaderProgramm;
	GLuint framebufferShaderID = framebufferShaderProgramm.createShaderProgram("framebufferShader.vert", "framebufferShader.frag");
	framebufferShader = new Shader(framebufferShaderID);

	createFrameBuffer(WIN_WIDTH, WIN_HEIGHT);
	initProjection();
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

		CustomBufferData data = modelMap.at(unit.model);
		BaseOpenGLRenderer::draw({ data.vao, data.ebo, data.vbo, data.indexCount, data.drawMode });

#ifdef DEBUG
		drawInDebugMode(data);
#endif
	}

	framebufferShader->use();
}

void Renderer::prepareShaders(const RenderUnit unit) const {
	standardShader->use();
	standardShader->setUniformMatrix4(TRANSFORM, unit.transformation);
}

void Renderer::drawInDebugMode(const CustomBufferData& data) const {
	glBindVertexArray(data.vao1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, data.indexCount1, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::loadModelDatas() {
	loadModelData(Model::ASTEROID1, GL_LINES);
	loadModelData(Model::ASTEROID2, GL_LINES);
	loadModelData(Model::ASTEROID3, GL_LINES);
	loadModelData(Model::ASTEROID4, GL_LINES);
	loadModelData(Model::SHIP, GL_LINES);
	loadModelData(Model::SAUCER, GL_LINES);
	loadModelData(Model::SHIP_MOVING, GL_LINES);
	loadModelData(Model::PROJECTILE, GL_LINES);
	loadModelData(Model::LINE_SEGMENT, GL_LINES);

	loadModelData(Model::CHARA, GL_TRIANGLES);
	loadModelData(Model::CHAR0, GL_TRIANGLES);
	loadModelData(Model::CHAR1, GL_TRIANGLES);
	loadModelData(Model::CHAR2, GL_TRIANGLES);
	loadModelData(Model::CHAR3, GL_TRIANGLES);
	loadModelData(Model::CHAR4, GL_TRIANGLES);
	loadModelData(Model::CHAR5, GL_TRIANGLES);
	loadModelData(Model::CHAR6, GL_TRIANGLES);
	loadModelData(Model::CHAR7, GL_TRIANGLES);
	loadModelData(Model::CHAR8, GL_TRIANGLES);
	loadModelData(Model::CHAR9, GL_TRIANGLES);
}

void Renderer::loadModelData(const Model model, const int drawMode) {
	Bindable bindable = game->getBindable(model);

	RenderData data = configure(bindable, drawMode);
	CustomBufferData cData = { data.vao, 0, data.ebo, data.vbo, data.indexCount, 0, data.drawMode };

#ifdef DEBUG
	if (drawMode != GL_TRIANGLES) {
		IndexData triangles = game->getTriangulatedModelData(model);
		Bindable triangleBindable = { bindable.vertexData, triangles };
		RenderData d1 = configure(triangleBindable, GL_TRIANGLES);

		cData.vao1 = d1.vao;
		cData.indexCount1 = d1.indexCount;
	}
#endif

	modelMap[model] = cData;
}

Renderer::~Renderer() {
	for (const pair<Model, CustomBufferData>& value : modelMap) {
		CustomBufferData data = value.second;

		glDeleteVertexArrays(1, &data.vao);
		glDeleteBuffers(1, &data.ebo);
		glDeleteBuffers(1, &data.vbo);
	}

	delete standardShader;
}