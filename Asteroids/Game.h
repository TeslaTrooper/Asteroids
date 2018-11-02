#ifndef GAME
#define GAME

#include <vector>

#include "Util.h"
#include "ModelData.h"
#include "FontData.h"

class Game {

	ModelData modelData;
	FontData fontdata;

	map<RenderUnitType, vector<RenderUnit>> renderUnits;

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