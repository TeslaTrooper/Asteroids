#ifndef FONT_BUILDER
#define FONT_BUILDER

#include <vector>

#include "FontData.h"
#include "Util.h"

class FontBuilder {

	map<char, Model> charModelMap;

	vector<RenderUnit> characters;

public:
	FontBuilder();
	~FontBuilder() {};

	void buildString(char const * const string, const int fontSize, const Vec2 position);
	void clear();
	vector<RenderUnit> get() const;
};

#endif FONT_BUILDER