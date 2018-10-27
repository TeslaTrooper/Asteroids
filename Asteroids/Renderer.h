#ifndef RENDERER
#define RENDERER

#include "ShaderProgram.h"
#include "Shader.h"
#include "Game.h"

class Renderer {

	Game* game;

	GLuint shaderProgramID, vbo, vao, ebo;
	Shader* shader;

	void initVertexData();

public:
	Renderer();
	~Renderer();

	void render(const float dt);

	void setProjection(const Mat4 projection);
};

#endif RENDERER