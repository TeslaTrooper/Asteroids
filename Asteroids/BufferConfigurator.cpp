#include "BufferConfigurator.h"

BufferConfigurator::BufferData BufferConfigurator::configure(const VertexData& vertexData, const IndexData& indexData) const {
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