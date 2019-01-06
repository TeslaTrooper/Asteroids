#include "Window.h"

Window::Window() : BaseOpenGLWindow(WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "Asteroids | OpenGL") {
	registerKeyCallback(Controller::key_callback);

	game = APIFactory::getInstance();
	renderer = new Renderer(game);
}

Window::~Window() {
	BaseOpenGLWindow::~BaseOpenGLWindow();
	delete renderer;
}

void Window::checkInput(const float dt) {
	if (Controller::isKeyDownPressed()) {
		printf("Down\n");
	}
	if (Controller::isKeyUpPressed()) {
		//printf("Up\n");
	}

	game->moveShip(Controller::isKeyUpPressed(), dt);

	if (Controller::isKeyRightPressed()) {
		game->rotateRight(dt);
	}
	if (Controller::isKeyLeftPressed()) {
		game->rotateLeft(dt);
	}
	if (Controller::isKeySpacePressed()) {
		game->shipShoot();
	}
	if (Controller::isKeyShiftPressed()) {
		game->hyperspace();
	}
}

void Window::loop(float dt) {
	game->update(dt);
	renderer->update(dt);
	checkInput(dt);
}