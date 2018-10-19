#ifndef CONTROLLER
#define CONTROLLER

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Controller {

	static bool KEY_SPACE;

public:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static bool isSpacePressed();
};

#endif CONTROLLER