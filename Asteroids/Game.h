#ifndef GAME
#define GAME

#include <vector>
#include <string>

#include "Util.h"
#include "ModelData.h"
#include "FontData.h"
#include "FontBuilder.h"
#include "PhysicsEngine.h"
#include "BindableProvider.h"
#include "InternalLogic.h"

class Game {

	ModelData modelData;
	FontData fontdata;
	FontBuilder fontBuilder;
	PhysicsEngine physicsEngine;
	BindableProvider bindableProvider;
	InternalLogic internalLogic;

	vector<RenderUnit> renderUnits;

	void updateUIElements(const float dt);
	void prepareRenderUnits();

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
	IndexData getTriangulatedModelData(const Model model) const;

	void moveShip(const bool moving, const float dt);
	void rotateLeft(const float dt);
	void rotateRight(const float dt);
	void shipShoot();


};

#endif GAME