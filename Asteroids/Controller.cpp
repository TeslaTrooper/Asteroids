#include "Controller.h"

bool Controller::KEY_SPACE = false;

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_SPACE: KEY_SPACE = true;
		}
	}
}

bool Controller::isSpacePressed() {
	bool tmp = KEY_SPACE;
	KEY_SPACE = false;

	return tmp;
}

