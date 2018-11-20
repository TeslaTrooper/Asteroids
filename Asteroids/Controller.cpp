#include "Controller.h"

bool Controller::KEY_SPACE = false;
bool Controller::KEY_RIGHT = false;
bool Controller::KEY_LEFT = false;
bool Controller::KEY_UP = false;
bool Controller::KEY_DOWN = false;
double Controller::M_X = 0;
double Controller::M_Y = 0;

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, 1); break;
		case GLFW_KEY_SPACE: KEY_SPACE = true; break;
		case GLFW_KEY_UP: KEY_UP = true; break;
		case GLFW_KEY_DOWN: KEY_DOWN = true; break;
		case GLFW_KEY_LEFT: KEY_LEFT = true; break;
		case GLFW_KEY_RIGHT: KEY_RIGHT = true;
		}
	} else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_SPACE: KEY_SPACE = false; break;
		case GLFW_KEY_UP: KEY_UP = false; break;
		case GLFW_KEY_DOWN: KEY_DOWN = false; break;
		case GLFW_KEY_LEFT: KEY_LEFT = false; break;
		case GLFW_KEY_RIGHT: KEY_RIGHT = false;
		}
	}
}

void Controller::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	M_X = xpos;
	M_Y = ypos;
}

bool Controller::getAndClean(bool* key) {
	bool tmp = *key;
	*key = false;

	return tmp;
}

bool Controller::isKeySpacePressed() {
	return getAndClean(&KEY_SPACE);
}

bool Controller::isKeyUpPressed() {
	return KEY_UP;
}

bool Controller::isKeyDownPressed() {
	return KEY_DOWN;
}

bool Controller::isKeyLeftPressed() {
	return KEY_LEFT;
}

bool Controller::isKeyRightPressed() {
	return KEY_RIGHT;
}

double Controller::getMx() {
	return M_X;
}

double Controller::getMy() {
	return M_Y;
}