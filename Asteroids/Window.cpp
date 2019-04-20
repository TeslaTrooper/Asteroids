#include "Window.h"

Window::Window(BaseOpenGLRenderer* const renderer, Game* const game) : 
	BaseOpenGLWindow(game, renderer, WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "Asteroids | OpenGL"), game(game), renderer(renderer) {
	registerKeyListener();
}

void Window::checkInput(const float dt) {
	game->moveShip(UserInputController::isKeyPressed(KEY_UP), dt);

	if (UserInputController::isKeyPressed(KEY_RIGHT))
		game->rotateRight(dt);

	if (UserInputController::isKeyPressed(KEY_LEFT))
		game->rotateLeft(dt);

	if (UserInputController::isKeyPressed(KEY_SPACE)) {
		UserInputController::release(KEY_SPACE);
		game->shipShoot();
	}

	if (UserInputController::isKeyPressed(KEY_SHIFT)) {
		UserInputController::release(KEY_SHIFT);
		game->hyperspace();
		game->update(dt);
	}
}