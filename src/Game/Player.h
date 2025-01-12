#pragma once
#include "IMCommon/Common.h"
#include "Input/keycodes.h"




struct PlayerControls {
    unsigned int WALK_FORWARD = IM_KEY_W;
    unsigned int WALK_BACKWARD = IM_KEY_S;
    unsigned int WALK_LEFT = IM_KEY_A;
    unsigned int WALK_RIGHT = IM_KEY_D;

};

class Player {


public:

    Player() = default;
    Player(int playerIndex);

    // Input

    bool PressingWalkForward();
    bool PressingWalkBackward();
    bool PressingWalkLeft();
    bool PressingWalkRight();

    bool PressedWalkForward();
    bool PressedWalkBackward();
    bool PressedWalkLeft();
    bool PressedWalkRight();

    bool PressedEscape();
    glm::mat4 GetProjetionMatrix();


    // Updates
    void Update(float deltaTime);
    void UpdateMovement(float deltaTime);
    void UpdateMouseLook(float deltaTime);



    // Checks


    // State queries
    bool IsMoving();



    // Misc
    int32_t GetKeyboardIndex();

    int32_t GetMouseIndex();

    void SetKeyboardIndex(int32_t index);
    void SetMouseIndex(int32_t index);


private:

 

    int m_mouseIndex = -1;
    int m_keyboardIndex = -1;

    int32_t m_playerIndex = -1;

    glm::mat4 _viewMatrix = glm::mat4(1);
    glm::mat4 _inverseViewMatrix = glm::mat4(1);
    glm::vec3 _viewPos = glm::vec3(0);
    glm::vec3 _forward = glm::vec3(0);
    glm::vec3 _up = glm::vec3(0);
    glm::vec3 _right = glm::vec3(0);
    glm::vec3 _position = glm::vec3(0);
    glm::vec3 _rotation = glm::vec3(-0.1f, -3.14 * 0.5f, 0);
};