#include "Engine.h"
#include "BackEnd/BackEnd.h"
#include "API/OpenGL/OGLBackEnd.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderData.h"
#include "Core/AssetManager.h"
#include "Core/Camera.h"
#include "Game/Game.h"




void Engine::run() {

	BackEnd::Init(API::OPENGL);

	while (BackEnd::WindowIsOpen()) {

		BackEnd::BeginFrame();
		BackEnd::UpdateSubSystems();

		// Load assets
		if (!AssetManager::LoadingComplete()) {
			AssetManager::LoadNextItem();
		}
		// Load Game 
		else if(!Game::IsLoaded()) {
			Game::Create();
			TestData::PopluateDummyMesh();
			AssetManager::UploadVertexData();
		}
		// Update and render
		else {
			Game::Update();
			Renderer::Render();
		}

		BackEnd::EndFrame();
	}
	BackEnd::CleanUp();
}

