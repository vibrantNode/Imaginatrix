#include "Player.h"
#include "Game.h"
#include "BackEnd/BackEnd.h"
#include "Input/Input.h"
#include "Input/Camera/FPS_Input.h"
#include "Core/Camera.h"
#include "IMCommon/Common.h"


float m_cameraZoom = 1.0f;

Player::Player(int playerIndex) {
    m_playerIndex = playerIndex;
   
}

void Player::Update(Camera& camera, float deltaTime) {

    // I'll update the keyboard and mouse here since there is a delta time param

   // Input::ProcessInput(deltaTime);
   

}











