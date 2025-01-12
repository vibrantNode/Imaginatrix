#include "Scene.h"
#include "Player.h"
#include "Game.h"

void Scene::Init() {
	//AllocateStorageSpace();
	//LoadDefaultScene();
}


void Scene::Update(float deltaTime) {
	Player* player = Game::GetPlayerByIndex(0);
}