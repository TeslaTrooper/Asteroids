#define GLEW_STATIC
#define OPENGL_VERSION 3

#ifndef WINDOW
#define WINDOW

#include "Controller.h"
#include "Renderer.h"

class Window {
	GLFWwindow* window;
	Renderer* renderer;

	void initOpenGL();
	void initWindow();

public:
	Window();
	~Window();

	void loop();
};

#endif WINDOW