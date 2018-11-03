#ifndef BUFFER_CONFIGURATOR
#define BUFFER_CONFIGURATOR

#include <GL/glew.h>

#include "Util.h"

class BufferConfigurator {

public:

	struct BufferData {
		unsigned int vao;
		unsigned int ebo;
		unsigned int vbo;
		int indexCount;
		int drawMode;
	};

	BufferData configure(const Bindable& bindable) const;

};

#endif BUFFER_CONFIGURATOR