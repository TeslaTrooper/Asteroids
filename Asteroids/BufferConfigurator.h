#ifndef BUFFER_CONFIGURATOR
#define BUFFER_CONFIGURATOR

#include <GL/glew.h>

#include "Util.h"

class BufferConfigurator {

public:

	struct BufferData {
		unsigned int vao, vao1;
		unsigned int ebo;
		unsigned int vbo;
		int indexCount, indexCount1;
		int drawMode;
	};

	BufferData configure(const Bindable& bindable) const;

};

#endif BUFFER_CONFIGURATOR