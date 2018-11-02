#include "Game.h"

Game::Game() {}

Game::~Game() {
}

void Game::update(const float dt) {

}

vector<RenderUnit> Game::getRenderUnits() const {
	Mat4 transformation1 = Mat4::getTransformation(Vec2(10, 10), Vec2(50, 50));
	Mat4 transformation2 = Mat4::getTransformation(Vec2(100, 10), Vec2(50, 50));

	vector<RenderUnit> list = vector<RenderUnit>();
	list.push_back({ transformation1, Model::CHAR1 });
	list.push_back({ transformation2, Model::CHAR5 });

	return list;
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