#pragma once

#include "GameImpl.h"

class APIFactory {

	static Game* game;

	APIFactory() {}

public:

	static Game* getInstance() {
		static Game* instance = new GameImpl();

		return instance;
	}

};