#include "Player.h"
#include "Game.h"
#include "BackEnd/BackEnd.h"
#include "Input/Input.h"
#include "Input/Camera/FPS_Input.h"
#include "IMCommon/Common.h"


float m_cameraZoom = 1.0f;

Player::Player(int playerIndex) {
    m_playerIndex = playerIndex;
}

void Player::Update(float deltaTime) {
    //UpdateMovement(deltaTime);
    //UpdateMouseLook(deltaTime);
   

}

glm::mat4 Player::GetProjetionMatrix() {
    float width = (float)BackEnd::GetWindowedWidth();
    float height = (float)BackEnd::GetWindowedHeight();

    return false;
    //return glm::perspective(m_cameraZoom, width / height, NEAR_PLANE, FAR_PLANE);
}


void Player::UpdateMouseLook(float deltaTime) {
    if (BackEnd::WindowHasFocus()) {
     /*   float mouseSensitivity = 0.002f;
        float xOffset = (float)FPS_Input::GetMouseXOffset(m_mouseIndex);
        float yOffset = (float)FPS_Input::GetMouseYOffset(m_mouseIndex);
        _rotation.x += -yOffset * mouseSensitivity;
        _rotation.y += -xOffset * mouseSensitivity;
        _rotation.x = std::min(_rotation.x, 1.5f);
        _rotation.x = std::max(_rotation.x, -1.5f);*/
    }
}


bool Player::PressingWalkForward() {
    return false;
}

bool Player::PressingWalkBackward() {
    return false;
}

bool Player::PressingWalkLeft() {
    return false;
}

bool Player::PressingWalkRight() {
    return false;
}


bool Player::PressedWalkForward() {
    return false;
}

bool Player::PressedWalkBackward() {
    return false;
}

bool Player::PressedWalkLeft() {
    return false;
}

bool Player::PressedWalkRight() {
    return false;
}
int32_t Player::GetKeyboardIndex() {
    return m_keyboardIndex;
}

int32_t Player::GetMouseIndex() {
    return m_mouseIndex;
}

void Player::SetKeyboardIndex(int32_t index) {
    m_keyboardIndex = index;
}
void Player::SetMouseIndex(int32_t index) {
    m_mouseIndex = index;
}








