#include "Renderer.h"

Renderer::Renderer(Game* const game, const Dimension winSize) {
	this->game = game;
	this->winSize = winSize;

	ShaderProgram standardShaderProgramm;
	GLuint standardShaderID = standardShaderProgramm.createShaderProgram("shader.vert", "shader.frag");
	standardShader = new Shader(standardShaderID);

	ShaderProgram framebufferShaderProgramm;
	GLuint framebufferShaderID = framebufferShaderProgramm.createShaderProgram("framebufferShader.vert", "framebufferShader.frag");
	framebufferShader = new Shader(framebufferShaderID);

	framebuffer = bufferConfigurator.createFrameBuffer(winSize);
	screenQuad = bufferConfigurator.configureScreenQuad();

	loadModelDatas();
}

void Renderer::render(const float dt) const {
	beginDraw();

	vector<RenderUnit> units = game->getRenderUnits();
	for each (RenderUnit unit in units) {
		draw(unit);
	}

	endDraw();
}

void Renderer::beginDraw() const {
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.id);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	standardShader->use();
}

void Renderer::draw(const RenderUnit unit) const {
	standardShader->setUniformMatrix4(TRANSFORM, unit.transformation);

	BufferConfigurator::BufferData data = modelMap.at(unit.model);

	glBindVertexArray(data.vao);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glDrawElements(data.drawMode, data.indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(data.vao1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDrawElements(GL_TRIANGLES, data.indexCount1, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindVertexArray(0);
}

void Renderer::endDraw() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	framebufferShader->use();
	glBindVertexArray(screenQuad.vao);
	glBindTexture(GL_TEXTURE_2D, framebuffer.textureAttachment);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::setProjection(const Mat4 projection) const {
	standardShader->use();
	standardShader->setUniformMatrix4(PROJECTION, projection);
}

void Renderer::loadModelDatas() {
	loadModelData(Model::ASTEROID1, GL_LINES);
	loadModelData(Model::ASTEROID2, GL_LINES);
	loadModelData(Model::ASTEROID3, GL_LINES);
	loadModelData(Model::ASTEROID4, GL_LINES);
	loadModelData(Model::SHIP, GL_LINES);
	loadModelData(Model::SAUCER, GL_LINES);
	loadModelData(Model::SHIP_MOVING, GL_LINES);

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

	BufferConfigurator::BufferData data = bufferConfigurator.configure(bindable);
	data.drawMode = drawMode;

	// This is only for debugging
	if (drawMode != GL_TRIANGLES) {
		IndexData triangles = game->getTriangulatedModelData(model);
		Bindable triangleBindable = { bindable.vertexData, triangles };
		BufferConfigurator::BufferData data1 = bufferConfigurator.configure(triangleBindable);
		data.vao1 = data1.vao;
		data.indexCount1 = data1.indexCount;
	}

	modelMap[model] = data;
}

Renderer::~Renderer() {
	for (const pair<Model, BufferConfigurator::BufferData>& value : modelMap) {
		BufferConfigurator::BufferData data = value.second;

		glDeleteVertexArrays(1, &data.vao);
		glDeleteBuffers(1, &data.ebo);
		glDeleteBuffers(1, &data.vbo);
	}

	delete standardShader;
}