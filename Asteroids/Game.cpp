#include "Game.h"

Game::Game() {
	renderUnits[RenderUnitType::TYPE_UI] = &uiElements;
	renderUnits[RenderUnitType::TYPE_GAME_OBJECT] = &gameObjects;

	float scale = 2;

	GameObject* obja = entityHandler.create(Model::SHIP, Vec2(50, 50), scale);
	obja->setDirection(Vec2(1.f, 0.3f));
	obja->setVMax(3);
	obja->setAcceleration(0.5f);

	GameObject* obj = entityHandler.create(Model::ASTEROID1, Vec2(0, 100), scale);
	obj->setVMax(1);
	obj->setAcceleration(1);
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

}

void Game::updateUIElements(const float dt) {
	fontBuilder.clear();

	int fps = (float)(1000 / (dt * 1e3));
	if (fps < 0) fps = 0;

	printf("FPS: %i \n", fps);

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