#include "Engine.h"
#include "BackEnd/BackEnd.h"
#include "API/OpenGL/OGLBackEnd.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderData.h"
#include "Core/AssetManager.h"


void Engine::run() {

	BackEnd::Init(API::OPENGL);

	while (BackEnd::WindowIsOpen()) {
		BackEnd::BeginFrame();
		BackEnd::UpdateSubSystems();

		// Load assets
		if (!AssetManager::LoadingComplete()) {
			AssetManager::LoadNextItem();

		}

		RenderData::PopluateDummyMesh();

		AssetManager::UploadVertexData();

		Renderer::Render();
		BackEnd::EndFrame();
	}
	BackEnd::CleanUp();
}