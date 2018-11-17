#ifndef BINDABLE_PROVIDER
#define BINDABLE_PROVIDER

#include "Util.h"
#include "ModelData.h"
#include "FontData.h"

class BindableProvider {

	ModelData* modelData;
	FontData* fontData;

public:
	BindableProvider();
	~BindableProvider();

	Bindable getBindable(const Model model) const;
	IndexData getTriangulatedModelData(const Model model) const;

};

#endif BINDABLE_PROVIDER