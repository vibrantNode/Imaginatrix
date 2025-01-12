#include "Renderer.h"
#include "BackEnd/BackEnd.h"
#include <iostream>
#include "API/OpenGL/OGLRenderer.h"
#include "BackEnd/BackEnd.h"
#include "Core/Camera.h"



namespace Renderer {




}
void Renderer::Render() {
	if (BackEnd::GetAPI() == API::OPENGL) {
		OGLRenderer::Render();
	}
}

void Renderer::LoadShaders() {
	if (BackEnd::GetAPI() == API::OPENGL) {
		OGLRenderer::LoadShaders();
	}
}