#ifndef RENDERER
#define RENDERER

#include "Game.h"

class Renderer {

	Game* game;

public:
	Renderer();
	~Renderer();

	void render(const float dt);
};

#endif RENDERER