#pragma  once
#include "API/OpenGL/Types/GL_VertexBuffer.h"


struct VertexBuffer {
	void AllocateSpace(int vertexCount);


	OpenGLVertexBuffer glVertexBuffer;
};