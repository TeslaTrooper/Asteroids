#ifndef RENDERER
#define RENDERER

#include "ShaderProgram.h"
#include "Shader.h"
#include "Game.h"

class Renderer {

	Game* game;

	GLuint shaderProgramID;
	Shader* shader;

public:
	Renderer();
	~Renderer();

	void render(const float dt);

	void setProjection(const Mat4 projection);
};

#endif RENDERER