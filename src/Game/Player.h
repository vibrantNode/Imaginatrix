#pragma once
#include "IMCommon/Common.h"
#include "Input/keycodes.h"
#include "Core/Camera.h"



struct PlayerControls {
    unsigned int WALK_FORWARD = IM_KEY_W;
    unsigned int WALK_BACKWARD = IM_KEY_S;
    unsigned int WALK_LEFT = IM_KEY_A;
    unsigned int WALK_RIGHT = IM_KEY_D;

};

enum InputType {
    KEYBOARD_AND_MOUSE,
    CONTROLLER
};

class Player {


public:

    Player() = default;
    Player(int playerIndex);


    glm::mat4 GetProjetionMatrix();


    // Updates
    void Update(Camera& camera, float deltaTime);



 

private:

 


    int32_t m_playerIndex = -1;

  
};