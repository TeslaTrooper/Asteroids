#ifndef CONTROLLER
#define CONTROLLER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Util.h"

class Controller {

	static bool KEY_SPACE;
	static bool KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_DOWN;

	static bool getAndClean(bool* key);

	static double M_X, M_Y;

public:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	static bool isKeySpacePressed();
	static bool isKeyUpPressed();
	static bool isKeyDownPressed();
	static bool isKeyLeftPressed();
	static bool isKeyRightPressed();
	static double getMx();
	static double getMy();
};

#endif CONTROLLER