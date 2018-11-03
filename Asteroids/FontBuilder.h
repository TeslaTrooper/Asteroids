#ifndef FONT_BUILDER
#define FONT_BUILDER

#include <vector>

#include "FontData.h"
#include "Util.h"

class FontBuilder {

	map<char, Model> charModelMap;

public:
	FontBuilder();
	~FontBuilder();

	vector<RenderUnit> buildString(char const * const string, const int fontSize, const Vec2 position) const;

};

#endif FONT_BUILDER