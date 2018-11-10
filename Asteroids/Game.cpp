#include "Game.h"

Game::Game(const Dimension windowBounds) {
	this->windowBounds = windowBounds;

	renderUnits[RenderUnitType::TYPE_UI] = &uiElements;
	renderUnits[RenderUnitType::TYPE_GAME_OBJECT] = &gameObjects;

	this->player = entityHandler.create(Model::SHIP, Vec2(0, 0), 1.5f);
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
	uiElements.clear();
	gameObjects.clear();

	vector<RenderUnit> ui = fontBuilder.get();
	vector<GameObject*> entities = entityHandler.get();

	for each (RenderUnit uiElem in ui) {
		uiElements.push_back(uiElem);
	}

	for each (GameObject* entity in entities) {
		gameObjects.push_back(entity->getRenderUnit());
	}

	renderUnits.at(RenderUnitType::TYPE_UI) = &uiElements;
	renderUnits.at(RenderUnitType::TYPE_GAME_OBJECT) = &gameObjects;
}

vector<RenderUnit> Game::getRenderUnits(const RenderUnitType type) const {
	return *renderUnits.at(type);
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
	if (moving) {
		player->setAcceleration(2);
	} else {
		player->setAcceleration(0);
	}
}