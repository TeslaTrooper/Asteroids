#ifndef GAME
#define GAME

#include <vector>
#include <string>
#include <InternalLogic.h>

#include "Util.h"
#include "ModelData.h"
#include "FontData.h"
#include "FontBuilder.h"
#include "BindableProvider.h"

/*
	Represents the main interface to the core logic of the game.
*/
struct Game : public InternalLogic {


	/*
		Provides access to all objects, which can be displayed by the ui.

		@returns
			a list containing RenderUnit instances, which can be used for rendering.
	*/
	virtual vector<RenderUnit> getRenderUnits() const = 0;


	/*
		Provides access to model data such as vertex and index information for a given model.

		@param model
			defines the model, for which the vertex and index information gets returned.
		@returns
			a Bindable reference containing the model information.
	*/
	virtual Bindable getBindable(const Model model) const = 0;


	/*
		This method can be used for streering the player's ship.

		@param moving
			defines, whether the ship should accelerate, or not.
		@param dt
			defines the time since last frame.
	*/
	virtual void moveShip(const bool moving, const float dt) = 0;


	/*
		This method can be used to rotate the ship to the left.

		@param dt
			defines the time since last frame.
	*/
	virtual void rotateLeft(const float dt) = 0;


	/*
		This method can be used to rotate the ship to the right.

		@param dt
			defines the time since last frame.
	*/
	virtual void rotateRight(const float dt) = 0;


	/*
		This method can be used to shoot away a projetile by player's ship.
	*/
	virtual void shipShoot() = 0;


	/*
		Calling this method performs hyperspace on the player's ship.
	*/
	virtual void hyperspace() = 0;

};

#endif GAME