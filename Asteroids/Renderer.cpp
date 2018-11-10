#include "Renderer.h"

Renderer::Renderer(Game* game) {
	this->game = game;

	ShaderProgram shaderProgramm;
	shaderProgramID = shaderProgramm.createShaderProgram();

	shader = new Shader(shaderProgramID);

	loadModelDatas();
}

void Renderer::render(const float dt) const {
	shader->use();

	vector<RenderUnit> uiUnits = game->getRenderUnits(RenderUnitType::TYPE_UI);
	for (int i = 0; i < uiUnits.size(); i++) {
		draw(uiUnits.at(i), -FontData::h);
	}

	vector<RenderUnit> gameUnits = game->getRenderUnits(RenderUnitType::TYPE_GAME_OBJECT);
	for (int i = 0; i < gameUnits.size(); i++) {
		draw(gameUnits.at(i), -ModelData::CROP_BOX.y);
	}
}

void Renderer::draw(const RenderUnit unit, const float invTranslation) const {
	Mat4 unitTransformation = unit.transformation;
	Mat4 rotationX = Mat4::rotateX(180);
	Mat4 translationY = Mat4::translate(Vec2(0.0f, invTranslation));
	Mat4 transformation = translationY.mul(rotationX.mul(unit.transformation));

	shader->setUniformMatrix4(TRANSFORM, transformation);

	BufferConfigurator::BufferData data = modelMap.at(unit.model);

	glBindVertexArray(data.vao);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glDrawElements(data.drawMode, data.indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Renderer::setProjection(const Mat4 projection) const {
	shader->use();
	shader->setUniformMatrix4(PROJECTION, projection);
}

void Renderer::loadModelDatas() {
	loadModelData(Model::ASTEROID1, GL_LINES);
	loadModelData(Model::ASTEROID2, GL_LINES);
	loadModelData(Model::ASTEROID3, GL_LINES);
	loadModelData(Model::ASTEROID4, GL_LINES);
	loadModelData(Model::SHIP, GL_LINES);
	loadModelData(Model::SAUCER, GL_LINES);

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

	modelMap[model] = data;
}

Renderer::~Renderer() {
	for (const pair<Model, BufferConfigurator::BufferData>& value : modelMap) {
		BufferConfigurator::BufferData data = value.second;

		glDeleteVertexArrays(1, &data.vao);
		glDeleteBuffers(1, &data.ebo);
		glDeleteBuffers(1, &data.vbo);
	}

	delete shader;
}