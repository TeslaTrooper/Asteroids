#include "FontBuilder.h"

FontBuilder::FontBuilder() {
	charModelMap['0'] = Model::CHAR0;
	charModelMap['1'] = Model::CHAR1;
	charModelMap['2'] = Model::CHAR2;
	charModelMap['3'] = Model::CHAR3;
	charModelMap['4'] = Model::CHAR4;
	charModelMap['5'] = Model::CHAR5;
	charModelMap['6'] = Model::CHAR6;
	charModelMap['7'] = Model::CHAR7;
	charModelMap['8'] = Model::CHAR8;
	charModelMap['9'] = Model::CHAR9;
}

void FontBuilder::buildString(char const * const string, const int fontSize, const Vec2 position) {
	for (int i = 0; string[i] != '\0'; i++) {
		char c = string[i];

		float scaledGlyphWidth = FontData::w * fontSize;
		float glyphGap = i > 0 ? scaledGlyphWidth * FontData::GLYPH_GAP_RATIO : 0;

		float x = position.x + i * (scaledGlyphWidth + glyphGap);

		Vec2 tmpPos = Vec2(x, position.y);
		
		Mat4 transformation = Mat4::getTransformation(tmpPos, Vec2(fontSize, fontSize));
		Model model = charModelMap.at(c);

		characters.push_back({ transformation, model });
	}
}

vector<RenderUnit> FontBuilder::get() const {
	return characters;
}

void FontBuilder::clear() {
	characters.clear();
}