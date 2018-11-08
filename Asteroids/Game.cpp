#include "Game.h"

Game::Game() {
	vector<RenderUnit> gameObjects;

	float scale = 1.5;

	gameObjects.push_back({ Mat4::getTransformation(Vec2(0, 100), Vec2(scale, scale)), Model::ASTEROID1 });
	gameObjects.push_back({ Mat4::getTransformation(Vec2(200, 100), Vec2(scale, scale)), Model::ASTEROID2 });
	gameObjects.push_back({ Mat4::getTransformation(Vec2(400, 100), Vec2(scale, scale)), Model::ASTEROID3 });
	gameObjects.push_back({ Mat4::getTransformation(Vec2(0, 250), Vec2(scale, scale)), Model::ASTEROID4 });
	gameObjects.push_back({ Mat4::getTransformation(Vec2(200, 250), Vec2(scale, scale)), Model::SHIP });
	gameObjects.push_back({ Mat4::getTransformation(Vec2(400, 250), Vec2(scale, scale)), Model::SAUCER });

	renderUnits[RenderUnitType::UI] = fontBuilder.buildString("0123456789", 11, Vec2(10, 100));
	renderUnits[RenderUnitType::GAME_OBJECT] = gameObjects;
}

Game::~Game() {
}

void Game::update(const float dt) {
	int fps = (float) (1000 / (dt * 1e3));
	if (fps < 0) fps = 0;

	std::string s = ::to_string(fps);

	renderUnits.at(RenderUnitType::UI) = fontBuilder.buildString(s.c_str() , 5, Vec2(5, 5));
}

vector<RenderUnit> Game::getRenderUnits(const RenderUnitType type) const {
	return renderUnits.at(type);
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