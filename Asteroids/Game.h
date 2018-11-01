#ifndef GAME
#define GAME

#include <vector>

#include "Util.h"
#include "ModelData.h"

class Game {

	ModelData* modelData;

public:
	Game();
	~Game();

	void update(const float dt);

	vector<RenderUnit> getRenderUnits();

	/*
		Provides access to model data such as vertex and index information for a given model.

		@param model
			defines the model, for which the vertex and index information gets returned.
		@returns
			a Bindable reference containing the model information.
	*/
	Bindable getBindable(Model model);
};

#endif GAME