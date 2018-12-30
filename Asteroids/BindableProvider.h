#ifndef BINDABLE_PROVIDER
#define BINDABLE_PROVIDER

#include "Util.h"
#include "ModelData.h"
#include "FontData.h"

class BindableProvider {

	FontData* fontData;

public:
	BindableProvider();
	~BindableProvider();

	Bindable getBindable(const Model model) const;
#ifdef DEBUG
	IndexData getTriangulatedModelData(const Model model) const;
#endif

};

#endif BINDABLE_PROVIDER