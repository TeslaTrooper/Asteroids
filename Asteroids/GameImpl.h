#ifndef GAME_IMPL
#define GAME_IMPL

#include "Game.h"

class GameImpl : public Game {

	FontData fontdata;
	FontBuilder fontBuilder;
	BindableProvider bindableProvider;
	InternalLogic internalLogic;

	vector<RenderUnit> renderUnits;

	void updateUIElements(const float dt);
	void prepareRenderUnits();

public:
	GameImpl(const GameImpl& impl) = delete;
	void operator=(const GameImpl&) = delete;

	GameImpl() : internalLogic(InternalLogic(new EntityFactory())) {}
	~GameImpl() {};

	void update(const float dt) override;
	vector<RenderUnit> getRenderUnits() const override;
	Bindable getBindable(const Model model) const override;
	void moveShip(const bool moving, const float dt) override;
	void rotateLeft(const float dt) override;
	void rotateRight(const float dt) override;
	void shipShoot() override;
	void hyperspace() override;
};



#endif GAME_IMPL