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

	struct FrameBuffer {
		unsigned int id;
		unsigned int textureAttachment;
	};

	BufferData configure(const Bindable& bindable) const;
	BufferData configureScreenQuad() const;
	FrameBuffer createFrameBuffer(const Dimension winSize) const;

};

#endif BUFFER_CONFIGURATOR