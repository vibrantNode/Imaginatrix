#pragma once
#include "IMCommon/Common.h"

namespace OGLBackEnd {
	void Init();
	void UploadVertexData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	void HandleFrameBufferResized();
	// Getters
	GLuint GetVertexDataVAO();
	GLuint GetVertexDataVBO();
	GLuint GetVertexDataEBO();
}