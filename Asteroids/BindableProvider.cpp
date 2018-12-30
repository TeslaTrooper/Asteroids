#include "BindableProvider.h"

BindableProvider::BindableProvider() {
	this->fontData = new FontData();
}

BindableProvider::~BindableProvider() {
	ModelData::clear();
	delete fontData;
}

Bindable BindableProvider::getBindable(const Model model) const {
	switch (model) {
		case Model::ASTEROID1:
		case Model::ASTEROID2:
		case Model::ASTEROID3:
		case Model::ASTEROID4:
		case Model::SAUCER:
		case Model::PROJECTILE:
		case Model::SHIP: return ModelData::getBindable(model);
		case Model::CHARA:
		case Model::CHAR0:
		case Model::CHAR1:
		case Model::CHAR2:
		case Model::CHAR3:
		case Model::CHAR4:
		case Model::CHAR5:
		case Model::CHAR6:
		case Model::CHAR7:
		case Model::CHAR8:
		case Model::CHAR9: return fontData->getBindable(model);
		default: return ModelData::getBindable(model);
	}
}

#ifdef DEBUG
IndexData BindableProvider::getTriangulatedModelData(const Model model) const {
	return ModelData::getTriangulatedModel(model);
}
#endif