#pragma once
#include "keycodes.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Input {

    void Init();
    void Update();
    void SetGLFWWindow(GLFWwindow* window);

    void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    bool IsKeyPressed(int key);
    
    bool KeyPressed(unsigned int keycode);

 
}