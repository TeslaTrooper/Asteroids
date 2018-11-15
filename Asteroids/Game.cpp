#include "Game.h"

Game::Game(const Dimension windowBounds) {
	this->windowBounds = windowBounds;

	this->player = entityHandler.create(Model::SHIP, Vec2(100, 100), 1.f);
	this->player->setVMax(5);

	GameObject* asteroid1 = entityHandler.create(Model::ASTEROID1, Vec2(300, 300), 1.f);
	asteroid1->setAngle(0);
	asteroid1->setVMax(2);
	asteroid1->setAcceleration(2);
	asteroid1->setDirection(Vec2(1, 1));
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
	
	checkForOutOfBoundsObjects(objects);
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
	return bindableProvider.getBindable(model);
}

void Game::moveShip(const bool moving, const float dt) {
	player->setAcceleration(moving ? 1.f : 0.f);
}

void Game::rotateLeft(const float dt) {
	player->rotate(GameObject::POSITIVE_ROTATION, dt);
}

void Game::rotateRight(const float dt) {
	player->rotate(GameObject::NEGATIVE_ROTATION, dt);
}

void Game::checkForOutOfBoundsObjects(const vector<GameObject*> objects) const {
	for each (GameObject* obj in objects) {
		if (obj->getPosition().x >= windowBounds.width) {
			obj->setPosition(Vec2(0.f, obj->getPosition().y));
		}
		if (obj->getPosition().x < 0) {
			obj->setPosition(Vec2((float)windowBounds.width, obj->getPosition().y));
		}
		if (obj->getPosition().y >= windowBounds.height) {
			obj->setPosition(Vec2(obj->getPosition().x, 0.f));
		}
		if (obj->getPosition().y < 0) {
			obj->setPosition(Vec2(obj->getPosition().x, windowBounds.height));
		}
	}
}