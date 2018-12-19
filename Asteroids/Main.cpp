#include "Window.h"

int main(void) {
	BaseOpenGLWindow* window = new Window();
	window->run();

	return 0;
}