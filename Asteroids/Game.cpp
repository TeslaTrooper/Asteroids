#include "Game.h"

Game::Game() {
	int size = 8;
	int offset = 50;
	Vec2 fontSize = Vec2(size, size);

	vector<RenderUnit> uiElements;

	uiElements.push_back({ Mat4::getTransformation(Vec2(0, 0), fontSize), Model::CHAR0 });
	uiElements.push_back({ Mat4::getTransformation(Vec2(0, FontData::h*size + offset), fontSize), Model::CHAR1 });
	uiElements.push_back({ Mat4::getTransformation(Vec2(0, (FontData::h*size * 2) + offset), fontSize), Model::CHAR2 });
	uiElements.push_back({ Mat4::getTransformation(Vec2(0, FontData::h*size * 3 + offset), fontSize), Model::CHAR3 });
	uiElements.push_back({ Mat4::getTransformation(Vec2(0, FontData::h*size * 4 + offset), fontSize), Model::CHAR4 });
	uiElements.push_back({ Mat4::getTransformation(Vec2(0, FontData::h*size * 5 + offset), fontSize), Model::CHAR5 });
	uiElements.push_back({ Mat4::getTransformation(Vec2(0, FontData::h*size * 6 + offset), fontSize), Model::CHAR6 });
	uiElements.push_back({ Mat4::getTransformation(Vec2(0, FontData::h*size * 7 + offset), fontSize), Model::CHAR7 });
	uiElements.push_back({ Mat4::getTransformation(Vec2(0, FontData::h*size * 8 + offset), fontSize), Model::CHAR8 });
	uiElements.push_back({ Mat4::getTransformation(Vec2(0, FontData::h*size * 9 + offset), fontSize), Model::CHAR9 });

	vector<RenderUnit> gameObjects;

	Mat4 transformation3 = Mat4::getTransformation(Vec2(0, 0), Vec2(1, 1));
	gameObjects.push_back({ transformation3, Model::ASTEROID2 });

	renderUnits[RenderUnitType::UI] = uiElements;
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