#include "Renderer.h"

Renderer::Renderer() {
	ShaderProgram shaderProgramm = ShaderProgram();
	shaderProgramID = shaderProgramm.createShaderProgram();

	shader = new Shader(shaderProgramID);

	initVertexData();
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	delete game;
	delete shader;
}

void Renderer::render(const float dt) {
	shader->use();
	shader->setUniformMatrix4("transform", Mat4::getTransformation(Vec2(10, 10), Vec2(50, 50)));

	glBindVertexArray(vao);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Renderer::setProjection(const Mat4 projection) {
	shader->use();
	shader->setUniformMatrix4("projection", projection);
}

void Renderer::initVertexData() {
	GLfloat vertices[] = {
		// pos
		0.8f, 1.0f, // top right
		1.0f, 0.0f, // bottom right
		0.2f, 0.5f, // bottom left
		0.0f, 1.0f, // top left
	};

	GLuint indices[] = {
		0, 1,
		1, 2,
		2, 3,
		3, 0
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}