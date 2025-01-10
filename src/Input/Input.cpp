#include "Input.h"
#include "BackEnd/BackEnd.h"


namespace Input {

    bool _keyPressed[372];
    bool _keyDown[372];
    double _mouseX = 0;
    double _mouseY = 0;
    double _mouseOffsetX = 0;
    double _mouseOffsetY = 0;
	GLFWwindow* _window;

    //void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    void Init() {
        double x, y;
        _window = BackEnd::GetWindowPointer();
        //glfwSetScrollCallback(_window, scroll_callback);
        glfwGetCursorPos(_window, &x, &y);
        //DisableCursor();
        _mouseOffsetX = x;
        _mouseOffsetY = y;
        _mouseX = x;
        _mouseY = y;
     
    }



    void Update() {

        if (KeyPressed(IM_KEY_ESCAPE)) {
            BackEnd::ForceCloseWindow();
        }
        // Mouse
        double x, y;
        glfwGetCursorPos(_window, &x, &y);
    }


    int GetMouseX() {
        return (int)_mouseX;
    }

    int GetMouseY() {
        return (int)_mouseY;
    }

    bool KeyPressed(unsigned int keycode) {
        return _keyPressed[keycode];
    }

    float GetMouseOffsetX() {
        return (float)_mouseOffsetX;
    }

    float GetMouseOffsetY() {
        return (float)_mouseOffsetY;
    }
    void DisableCursor() {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void HideCursor() {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void ShowCursor() {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}