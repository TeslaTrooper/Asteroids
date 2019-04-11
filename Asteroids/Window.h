#ifndef WINDOW
#define WINDOW

#include <stdio.h>
#include <BaseOpenGLWindow.h>
#include <BaseOpenGLRenderer.h>

#include "Controller.h"
#include "Renderer.h"
#include "APIFactory.h"

#define FRAME_RATE 60

#define WIN_POS_X 50
#define WIN_POS_Y 100

class Window : public BaseOpenGLWindow {
	BaseOpenGLRenderer* renderer;
	Game* game;

	void checkInput(const float dt);

public:
	Window();
	~Window();

	void loop(float dt) override;
};

#endif WINDOW