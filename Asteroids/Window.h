#define GLEW_STATIC
#define OPENGL_VERSION 3

#ifndef WINDOW
#define WINDOW

#include "Controller.h"
#include "Renderer.h"
#include "Mat4.h"

#define FRAME_RATE 60

class Window {
	GLFWwindow* window;
	Renderer* renderer;
	Game* game;
	Dimension windowSize;

	Mat4 projection;

	void initOpenGL();
	void initWindow();
	void initViewport();
	void initProjectionMatrix();

	void checkKeys(const float dt);

public:
	Window();
	~Window();

	void loop();
};

#endif WINDOW