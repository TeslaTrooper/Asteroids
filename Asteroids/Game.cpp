#include "Game.h"

Game::Game() {
	modelData = new ModelData();
}

Game::~Game() {
}

void Game::update(const float dt) {

}

vector<RenderUnit> Game::getRenderUnits() {
	Mat4 transformation = Mat4::getTransformation(Vec2(10, 10), Vec2(1, 1));

	RenderUnit r = { transformation, Model::ASTEROID2 };

	vector<RenderUnit> list = vector<RenderUnit>();
	list.push_back(r);

	return list;
}

Bindable Game::getBindable(Model model) {
	return modelData->getBindable(model);
}
