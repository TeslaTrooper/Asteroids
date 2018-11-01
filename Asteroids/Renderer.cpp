#include "Renderer.h"

Renderer::Renderer() {
	game = new Game();
	modelMap = map<Model, BufferData>();

	ShaderProgram shaderProgramm = ShaderProgram();
	shaderProgramID = shaderProgramm.createShaderProgram();

	shader = new Shader(shaderProgramID);

	loadModelDatas();
}

void Renderer::render(const float dt) {
	shader->use();

	vector<RenderUnit> units = game->getRenderUnits();
	for (int i = 0; i < units.size(); i++) {
		RenderUnit unit = units.at(i);

		shader->setUniformMatrix4("transform", unit.transformation);

		BufferData data = modelMap[unit.model];

		glBindVertexArray(data.vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

		glDrawElements(GL_LINES, data.indexCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
}

void Renderer::setProjection(const Mat4 projection) {
	shader->use();
	shader->setUniformMatrix4("projection", projection);
}

Renderer::BufferData Renderer::configureBuffers(const VertexData& vertexData, const IndexData& indexData) {
	GLuint vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.count * VERTEX_COMP_SIZE * sizeof(GLuint), indexData.indices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, vertexData.count * VERTEX_COMP_SIZE * sizeof(GLfloat), vertexData.vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VERTEX_COMP_SIZE * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return { vao, ebo, vbo, indexData.count * VERTEX_COMP_SIZE };
}

void Renderer::loadModelDatas() {
	loadModelData(Model::ASTEROID1);
	loadModelData(Model::ASTEROID2);
}

void Renderer::loadModelData(Model model) {
	Bindable bindable = game->getBindable(model);
	modelMap[model] = configureBuffers(bindable.vertexData, bindable.indexData);
}

Renderer::~Renderer() {
	for (const pair<Model, BufferData>& value : modelMap) {
		BufferData data = value.second;

		glDeleteVertexArrays(1, &data.vao);
		glDeleteBuffers(1, &data.ebo);
		glDeleteBuffers(1, &data.vbo);
	}

	delete game;
	delete shader;
}