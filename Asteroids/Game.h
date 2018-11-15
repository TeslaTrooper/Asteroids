#ifndef GAME
#define GAME

#include <vector>
#include <string>

#include "Util.h"
#include "ModelData.h"
#include "FontData.h"
#include "FontBuilder.h"
#include "PhysicsEngine.h"
#include "EntityHandler.h"
#include "BindableProvider.h"

class Game {

	ModelData modelData;
	FontData fontdata;
	FontBuilder fontBuilder;
	PhysicsEngine physicsEngine;
	EntityHandler entityHandler;
	BindableProvider bindableProvider;

	vector<RenderUnit> renderUnits;

	Dimension windowBounds;
	GameObject* player;

	void doGameLogic(const float dt);
	void updateUIElements(const float dt);
	void prepareRenderUnits();
	void checkForOutOfBoundsObjects(const vector<GameObject*> objects) const;

public:
	Game(const Dimension windowBounds);
	~Game();

	void update(const float dt);
	vector<RenderUnit> getRenderUnits() const;

	/*
		Provides access to model data such as vertex and index information for a given model.

		@param model
			defines the model, for which the vertex and index information gets returned.
		@returns
			a Bindable reference containing the model information.
	*/
	Bindable getBindable(const Model model) const;

	void moveShip(const bool moving, const float dt);
	void rotateLeft(const float dt);
	void rotateRight(const float dt);


};

#endif GAME