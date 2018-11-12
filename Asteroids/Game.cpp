#include "Game.h"

Game::Game(const Dimension windowBounds) {
	this->windowBounds = windowBounds;

	this->player = entityHandler.create(Model::SAUCER, Vec2(100, 100), 5.f);
	this->player->setVMax(5);
}

Game::~Game() {
}

void Game::update(const float dt) {
	physicsEngine.update(entityHandler.get(), dt);
	doGameLogic(dt);
	updateUIElements(dt);
	prepareRenderUnits();
}

void Game::doGameLogic(const float dt) {
	vector<GameObject*> objects = entityHandler.get();
	for each (GameObject* obj in objects) {
		if (obj->getPosition().x >= windowBounds.width) {
			obj->setPosition(Vec2(0.f, obj->getPosition().y));
		}
		if (obj->getPosition().x < 0) {
			obj->setPosition(Vec2((float)windowBounds.width, obj->getPosition().y));
		}
	}
}

void Game::updateUIElements(const float dt) {
	fontBuilder.clear();

	int fps = (float)(1000 / (dt * 1e3));
	if (fps < 0) fps = 0;

	//printf("FPS: %i \n", fps);

	std::string s = ::to_string(fps);
	fontBuilder.buildString(s.c_str(), 5, Vec2(5, 5));
}

void Game::prepareRenderUnits() {
	renderUnits.clear();

	vector<RenderUnit> ui = fontBuilder.get();
	vector<GameObject*> entities = entityHandler.get();

	for each (RenderUnit uiElem in ui) {
		renderUnits.push_back(uiElem);
	}

	for each (GameObject* entity in entities) {
		renderUnits.push_back(entity->getRenderUnit());
	}
}

vector<RenderUnit> Game::getRenderUnits() const {
	return renderUnits;
}

Bindable Game::getBindable(const Model model) const {
	switch (model) {
		case Model::ASTEROID1:
		case Model::ASTEROID2:
		case Model::ASTEROID3:
		case Model::ASTEROID4:
		case Model::SAUCER:
		case Model::SHIP: return modelData.getBindable(model);
		case Model::CHARA:
		case Model::CHAR0:
		case Model::CHAR1:
		case Model::CHAR2:
		case Model::CHAR3:
		case Model::CHAR4:
		case Model::CHAR5:
		case Model::CHAR6:
		case Model::CHAR7:
		case Model::CHAR8:
		case Model::CHAR9: return fontdata.getBindable(model);
		default: return modelData.getBindable(model);
	}
}

void Game::moveShip(const bool moving, const float dt) {
	player->setAcceleration(moving ? 2.f : 0.f);
}

void Game::rotateLeft(const float dt) {
	player->rotate(GameObject::POSITIVE_ROTATION, dt);
	printf("Rotation: %i \n", player->getAngle());
}

void Game::rotateRight(const float dt) {
	player->rotate(GameObject::NEGATIVE_ROTATION, dt);
	printf("Rotation: %i \n", player->getAngle());
}