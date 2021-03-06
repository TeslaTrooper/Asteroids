#include "GameImpl.h"

void GameImpl::update(const float dt) {
	gameLogic.update(dt);
	updateUIElements(dt);
	prepareRenderUnits();
}

void GameImpl::updateUIElements(const float dt) {
	fontBuilder.clear();

	int fps = (int) (1000 / (dt * 1e3));
	if (fps < 0) fps = 0;

	//printf("FPS: %i \n", fps);

	std::string fpsLabel = ::to_string(fps);
	fontBuilder.buildString(fpsLabel.c_str(), 5, Vec2(5, 5));

	std::string scoreLabel = to_string(gameLogic.getScore());
	fontBuilder.buildString(scoreLabel.c_str(), 5, Vec2((float) 5, WIN_HEIGHT - ((FontData::h * 5) + 5)));
}

void GameImpl::prepareRenderUnits() {
	renderUnits.clear();

	vector<RenderUnit> ui = fontBuilder.get();
	vector<RenderUnit> entities = gameLogic.getRenderUnits();

	for each (RenderUnit uiElem in ui) {
		renderUnits.push_back(uiElem);
	}

	for each (RenderUnit entity in entities) {
		renderUnits.push_back(entity);
	}

	for (int i = 0; i < gameLogic.getLifes(); i++) {
		int x = (int) (5 + (i * ModelData::SHIP_CROP_BOX.width));
		int y = WIN_HEIGHT - 60;

		Dimension modelDim = ModelData::getCropBox(ModelClass::CLASS_SHIP, 1);
		Vec2 rotationOrigin = Vec2(modelDim.width / 2, modelDim.height / 2);
		Mat4 transformation = Mat4::getTransformation(Vec2(x, y), Vec2(SIZE_SMALL, SIZE_SMALL), 270, rotationOrigin);


		renderUnits.push_back({ transformation, Model::SHIP });
	}
}

vector<RenderUnit> GameImpl::getRenderUnits() const {
	return renderUnits;
}

Bindable GameImpl::getBindable(const Model model) const {
	return bindableProvider.getBindable(model);
}

void GameImpl::moveShip(const bool moving, const float dt) {
	gameLogic.moveShip(moving, dt);
}

void GameImpl::rotateLeft(const float dt) {
	gameLogic.rotatePlayerLeft(dt);
}

void GameImpl::rotateRight(const float dt) {
	gameLogic.rotatePlayerRight(dt);
}

void GameImpl::shipShoot() {
	gameLogic.shipShoot();
}

void GameImpl::hyperspace() {
	gameLogic.hyperspace();
}