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

	vector<RenderUnit> units = game->getRenderUnits();
	for each (RenderUnit unit in units) {
		draw(unit);
	}
}

void Renderer::draw(const RenderUnit unit) const {
	shader->setUniformMatrix4(TRANSFORM, unit.transformation);

	BufferConfigurator::BufferData data = modelMap.at(unit.model);

	glBindVertexArray(data.vao);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glDrawElements(data.drawMode, data.indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(data.vao1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, data.indexCount1, GL_UNSIGNED_INT, 0);

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
	Bindable untransformedBindable = game->getBindable(model);
	Bindable bindable = transformVertexDataToOpenGLSpace(untransformedBindable);

	BufferConfigurator::BufferData data = bufferConfigurator.configure(untransformedBindable);
	data.drawMode = drawMode;

	// This is only for debugging
	if (drawMode != GL_TRIANGLES) {
		IndexData triangles = game->getTriangulatedModelData(model);
		Bindable triangleBindable = { untransformedBindable.vertexData, triangles, ModelData::ASTEROID_CROP_BOX };
		BufferConfigurator::BufferData data1 = bufferConfigurator.configure(triangleBindable);
		data.vao1 = data1.vao;
		data.indexCount1 = data1.indexCount;
	}

	modelMap[model] = data;
}

Bindable Renderer::transformVertexDataToOpenGLSpace(const Bindable& bindable) const {
	Mat4 rotationX = Mat4::rotateX(180);
	Mat4 translationY = Mat4::translate(Vec2(0.0f, (float) -bindable.cropBox.height));
	Mat4 transformation = rotationX.mul(translationY);

	float* transformedVertexData = new float[bindable.vertexData.count * VERTEX_COMP_SIZE];

	for (int i = 0; i < (bindable.vertexData.count * VERTEX_COMP_SIZE) - 1; i += 2) {
		Vec2 vec = Vec2(bindable.vertexData.vertices[i], bindable.vertexData.vertices[i + 1]);
		Vec2 transformedVec = transformation.transform(vec);

		transformedVertexData[i] = transformedVec.x;
		transformedVertexData[i + 1] = transformedVec.y;
	}

	VertexData data = { transformedVertexData, bindable.vertexData.count };

	return { data, bindable.indexData, bindable.cropBox };
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