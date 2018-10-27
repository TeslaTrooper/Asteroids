#include "Renderer.h"

Renderer::Renderer() {
	ShaderProgram shaderProgramm = ShaderProgram();
	shaderProgramID = shaderProgramm.createShaderProgram();

	shader = new Shader(shaderProgramID);

	loadModelData();
}

void Renderer::render(const float dt) {
	shader->use();
	shader->setUniformMatrix4("transform", Mat4::getTransformation(Vec2(10, 10), Vec2(1, 1)));

	glBindVertexArray(asteriod2.vao);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glDrawElements(GL_LINES, asteriod2.indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Renderer::setProjection(const Mat4 projection) {
	shader->use();
	shader->setUniformMatrix4("projection", projection);
}

int Renderer::configureBuffers(const VertexData& vertexData, const IndexData& indexData) {
	GLuint vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.count * sizeof(int), indexData.indices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, vertexData.count * sizeof(float), vertexData.vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return vao;
}

IndexData Renderer::calcIndices(const float* vertexData, int arraySize) {
	int vertexCount = arraySize / sizeof(float);

	int* indices = new int[vertexCount];

	for (int i = 0, j = 0; i < vertexCount; i++, j += 2) {
		indices[j] = i;
		indices[j + 1] = (i + 1) % (vertexCount / 2);
	}

	return { indices, vertexCount };
}

void Renderer::loadModelData() {
	IndexData indexData1 = calcIndices(a1Vertices, sizeof(a1Vertices));
	VertexData vertexData1 = { a1Vertices, sizeof(a1Vertices) };
	int vao1 = configureBuffers(vertexData1, indexData1);

	asteriod1 = { vao1, indexData1.count };

	IndexData indexData2 = calcIndices(a2Vertices, sizeof(a2Vertices));
	VertexData vertexData2 = { a2Vertices, sizeof(a2Vertices) };
	int vao2 = configureBuffers(vertexData2, indexData2);

	asteriod2 = { vao2, indexData2.count };
}

Renderer::~Renderer() {
	/*glDeleteVertexArrays(1, &asteriod1.vao);
	/*glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);*/

	delete game;
	delete shader;
}