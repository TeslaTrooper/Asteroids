#include "Game.h"

Game::Game() {
	vector<RenderUnit> gameObjects;

	Mat4 transformation3 = Mat4::getTransformation(Vec2(0, 0), Vec2(1, 1));
	gameObjects.push_back({ transformation3, Model::ASTEROID2 });

	renderUnits[RenderUnitType::UI] = fontBuilder.buildString("0123456789", 11, Vec2(10, 100));
	renderUnits[RenderUnitType::GAME_OBJECT] = gameObjects;
}

Game::~Game() {
}

void Game::update(const float dt) {

}

vector<RenderUnit> Game::getRenderUnits(const RenderUnitType type) const {
	return renderUnits.at(type);
}

Bindable Game::getBindable(const Model model) const {
	switch (model) {
		case Model::ASTEROID1:
		case Model::ASTEROID2: return modelData.getBindable(model);
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