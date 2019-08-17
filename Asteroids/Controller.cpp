#include "Controller.h"

Controller::Controller(BaseRenderer* const renderer, Game* const game) :
	BaseController(game, renderer, WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "Asteroids | OpenGL"), game(game), renderer(renderer) {
	registerKeyListener();
}

void Controller::checkInput(const float dt) {
	game->moveShip(KeyCallbackHandler::isKeyPressed(KEY_UP), dt);

	if (KeyCallbackHandler::isKeyPressed(KEY_RIGHT))
		game->rotateRight(dt);

	if (KeyCallbackHandler::isKeyPressed(KEY_LEFT))
		game->rotateLeft(dt);

	if (KeyCallbackHandler::isKeyPressed(KEY_SPACE)) {
		KeyCallbackHandler::release(KEY_SPACE);
		game->shipShoot();
	}

	if (KeyCallbackHandler::isKeyPressed(KEY_SHIFT)) {
		KeyCallbackHandler::release(KEY_SHIFT);
		game->hyperspace();
		game->update(dt);
	}
}