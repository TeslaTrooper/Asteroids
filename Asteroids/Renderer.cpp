#include "Renderer.h"

Renderer::Renderer() {
	ShaderProgram shaderProgramm = ShaderProgram();
	shaderProgramID = shaderProgramm.createShaderProgram();

	shader = new Shader(shaderProgramID);
}

Renderer::~Renderer() {
}

void Renderer::render(const float dt) {
}

void Renderer::setProjection(const Mat4 projection) {
	shader->use();
	shader->setUniformMatrix4("projection", projection);
}