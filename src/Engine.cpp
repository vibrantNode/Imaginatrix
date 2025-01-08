#include "Engine.h"
#include "BackEnd/BackEnd.h"





void Engine::run() {

	BackEnd::Init(API::OPENGL);

	while (BackEnd::WindowIsOpen()) {
		BackEnd::BeginFrame();
	}
	
}