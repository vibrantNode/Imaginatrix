#include "Input.h"
#include <iostream>
#include <glm/glm.hpp>
#include "BackEnd/BackEnd.h"
#include "Core/Camera.h"


namespace Input {

    bool _keyPressed[372];
    bool _keyDown[372];
    bool _keyDownLastFrame[372];
    double _mouseX = 0;
    double _mouseY = 0;
    double _mouseOffsetX = 0;
    double _mouseOffsetY = 0;

    // Initialize static variables
    GLFWwindow* _window = nullptr; // Linked to the GLFW window
    Camera _camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

    glm::vec2 lastMousePosition(0.0f, 0.0f);
    glm::vec2 mouseDelta(0.0f, 0.0f);

    // Initialization function
    void Init() {

        _window = BackEnd::GetWindowPointer();
        if (!_window) {
            std::cerr << "Input::Init() - GLFW window not set. Call SetGLFWWindow() first." << std::endl;
        }
    }


    // Update function (can be extended to handle frame-specific tasks)
    void Update() {
        if (!_window) {
            std::cerr << "Input::Update() - GLFW window not set. Call SetGLFWWindow() first." << std::endl;
            return;
        }

    }

    // Set the GLFW window and configure callbacks
    void SetGLFWWindow(GLFWwindow* window) {
        _window = window;
    }



    // Check if a specific key is pressed
    bool IsKeyPressed(int key) {
        if (!_window) {
            std::cerr << "Input::IsKeyPressed() - GLFW window not set. Call SetGLFWWindow() first." << std::endl;
            return false;
        }
        return glfwGetKey(_window, key) == GLFW_PRESS;
    }

    bool KeyPressed(unsigned int keycode) {
        return _keyPressed[keycode];
    }



    void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
        // Get mouse offset
        double xoffset = xpos - _mouseX;
        double yoffset = _mouseY - ypos;  // Inverted Y-axis to match OpenGL's coordinate system

        _mouseX = xpos;
        _mouseY = ypos;

        _camera.ProcessMouseMovement(static_cast<float>(xoffset), static_cast<float>(yoffset));
    }
}
