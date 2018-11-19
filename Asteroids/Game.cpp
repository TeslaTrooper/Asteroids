#include "Game.h"

Game::Game(const Dimension windowBounds) : internalLogic(InternalLogic(windowBounds)) {
	internalLogic.createInitialEntities();
}

Game::~Game() {}

void Game::update(const float dt) {
	physicsEngine.update(internalLogic.getEntities(), dt);
	internalLogic.update(dt);
	updateUIElements(dt);
	prepareRenderUnits();
}

void Game::updateUIElements(const float dt) {
	fontBuilder.clear();

	int fps = (int) (1000 / (dt * 1e3));
	if (fps < 0) fps = 0;

	//printf("FPS: %i \n", fps);

	std::string s = ::to_string(fps);
	fontBuilder.buildString(s.c_str(), 5, Vec2(5, 5));
}

void Game::prepareRenderUnits() {
	renderUnits.clear();

	vector<RenderUnit> ui = fontBuilder.get();
	vector<RenderUnit> entities = internalLogic.getRenderUnits();

	for each (RenderUnit uiElem in ui) {
		renderUnits.push_back(uiElem);
	}

	for each (RenderUnit entity in entities) {
		renderUnits.push_back(entity);
	}
}

vector<RenderUnit> Game::getRenderUnits() const {
	return renderUnits;
}

Bindable Game::getBindable(const Model model) const {
	return bindableProvider.getBindable(model);
}

IndexData Game::getTriangulatedModelData(const Model model) const {
	return bindableProvider.getTriangulatedModelData(model);
}

void Game::moveShip(const bool moving, const float dt) {
	internalLogic.moveShip(moving, dt);
}

void Game::rotateLeft(const float dt) {
	internalLogic.rotatePlayerLeft(dt);
}

void Game::rotateRight(const float dt) {
	internalLogic.rotatePlayerRight(dt);
}