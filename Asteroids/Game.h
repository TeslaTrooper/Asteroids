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

class Game {

	ModelData modelData;
	FontData fontdata;
	FontBuilder fontBuilder;
	PhysicsEngine physicsEngine;
	EntityHandler entityHandler;

	map<RenderUnitType, vector<RenderUnit>*> renderUnits;
	vector<RenderUnit> gameObjects;
	vector<RenderUnit> uiElements;

	void doGameLogic(const float dt);
	void updateUIElements(const float dt);
	void prepareRenderUnits();

public:
	Game();
	~Game();

	void update(const float dt);

	vector<RenderUnit> getRenderUnits(const RenderUnitType type) const;

	/*
		Provides access to model data such as vertex and index information for a given model.

		@param model
			defines the model, for which the vertex and index information gets returned.
		@returns
			a Bindable reference containing the model information.
	*/
	Bindable getBindable(const Model model) const;
};

#endif GAME