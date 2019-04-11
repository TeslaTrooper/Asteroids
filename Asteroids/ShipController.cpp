#include "ShipController.h"

ShipController::ShipController(EntityFactory* const entityFactory) : entityFactory(entityFactory) {
	this->inProgress = false;
	this->delayCtr = 0;
}

void ShipController::update(const float dt) {
	if (inProgress)
		delayCtr -= dt;

	if (delayCtr <= 0) {
		inProgress = false;
		delayCtr = DELAY;

		showShipAfterHyperspace();
	}
}

void ShipController::rotatePlayerLeft(const float dt) {
	GameObject* player = entityFactory->getPlayer();

	if (player == nullptr) {
		return;
	}

	player->rotate(GameObject::NEGATIVE_ROTATION, dt);
}

void ShipController::rotatePlayerRight(const float dt) {
	GameObject* player = entityFactory->getPlayer();

	if (player == nullptr) {
		return;
	}

	player->rotate(GameObject::POSITIVE_ROTATION, dt);
}

void ShipController::moveShip(const bool moving, const float dt) {
	GameObject* player = entityFactory->getPlayer();

	if (player == nullptr) {
		return;
	}

	player->setAcceleration(moving ? 1.f : 0.f);
}

void ShipController::hyperspace() {
	Ship* player = (Ship*) entityFactory->getPlayer();

	if (player == nullptr) {
		return;
	}

	player->enterHyperspace();

	inProgress = true;
}

void ShipController::showShipAfterHyperspace() {
	Ship* player = (Ship*) entityFactory->getPlayer();

	if (player == nullptr) {
		return;
	}

	player->leaveHyperspace();
}