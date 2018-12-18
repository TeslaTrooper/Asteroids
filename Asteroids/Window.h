#ifndef WINDOW
#define WINDOW

#include <stdio.h>

#include "Controller.h"
#include "Renderer.h"
#include "Mat4.h"
#include "BaseOpenGLWindow.h"

#define FRAME_RATE 60

#define WIN_POS_X 50
#define WIN_POS_Y 100

class Window : public BaseOpenGLWindow {
	Renderer* renderer;
	Game* game;

	void checkInput(const float dt);

public:
	Window();
	~Window();

	void loop(float dt);
};

#endif WINDOW