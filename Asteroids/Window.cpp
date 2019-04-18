#include "Window.h"

Window::Window(BaseOpenGLRenderer* const renderer, Game* const game) : 
	BaseOpenGLWindow(game, renderer, WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "Asteroids | OpenGL"), game(game), renderer(renderer) {
	registerKeyCallback(Controller::key_callback);
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
		game->update(dt);
	}
}