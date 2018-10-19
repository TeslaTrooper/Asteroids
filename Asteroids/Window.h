#define GLEW_STATIC
#define OPENGL_VERSION 3

#ifndef WINDOW
#define WINDOW

#include "Controller.h"
#include "Renderer.h"
#include "Util.h"
#include "Mat4.h"

class Window {
	GLFWwindow* window;
	Renderer* renderer;
	Dimension windowSize;

	void initOpenGL();
	void initWindow();
	void initViewport();
	void initProjectionMatrix();

public:
	Window();
	~Window();

	void loop();
};

#endif WINDOW