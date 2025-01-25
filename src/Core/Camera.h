#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>








#include <glm/gtc/quaternion.hpp>

#include <Input/Input.h>
// Define movement directions
enum class CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
private:
    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler Angles
    float yaw;
    float pitch;

    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom; // Field of view (FOV)

    // Updates the camera vectors based on the updated Euler angles
    void UpdateCameraVectors() {
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);

        // Recalculate the right and up vectors
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }

public:
    // Constructor
    Camera(glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 startUp = glm::vec3(0.0f, 1.0f, 0.0f),
        float startYaw = -90.0f,
        float startPitch = 0.0f,
        float startZoom = 45.0f)
        : position(startPosition), worldUp(startUp), yaw(startYaw), pitch(startPitch), zoom(startZoom),
        movementSpeed(2.5f), mouseSensitivity(0.1f) {
        UpdateCameraVectors();
    }

    // Returns the view matrix
    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

    // Processes input for movement
    void ProcessKeyboard(CameraMovement direction, float deltaTime) {
        float velocity = movementSpeed * deltaTime;
        if (direction == CameraMovement::FORWARD)
            position += front * velocity;
        if (direction == CameraMovement::BACKWARD)
            position -= front * velocity;
        if (direction == CameraMovement::LEFT)
            position -= right * velocity;
        if (direction == CameraMovement::RIGHT)
            position += right * velocity;
    }

    // Processes input from a mouse
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true) {
        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity;

        yaw += xOffset;
        pitch += yOffset;

        // Constrain the pitch
        if (constrainPitch) {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        // Update the front, right, and up vectors
        UpdateCameraVectors();
    }

    // Processes input for mouse scroll
    void ProcessMouseScroll(float yOffset) {
        zoom -= yOffset;
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > 90.0f)
            zoom = 90.0f;
    }

    // Getter for zoom (FOV)
    float GetZoom() const {
        return zoom;
    }
};








//
//enum CameraMovement {
//    FORWARD,
//    BACKWARD,
//    LEFT,
//    RIGHT
//};
//
//
//class Camera {
//public:
//
//    Camera(glm::vec3 position, float yaw, float pitch);
//
//    // Camera attributes
//    glm::vec3 Position;
//    glm::vec3 Front;
//    glm::vec3 Up;
//    glm::vec3 Right;
//    glm::vec3 WorldUp;
//
//    // Euler angles
//    float Yaw;
//    float Pitch;
//
//    // Camera options
//    float MovementSpeed;
//    float MouseSensitivity;
//    float Zoom;
//
//    // Constructor
//    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float zoom = 45.0f);
//
//    // Returns the view matrix calculated using LookAt
//    glm::mat4 GetViewMatrix() const;
//
//    // Returns the zoom level
//    float GetZoom() const;
//
//    // Processes keyboard input
//    void ProcessKeyboardInput(int direction, float deltaTime);
//
//    // Processes mouse movement
//    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
//
//    // Processes mouse scroll input
//    void ProcessMouseScroll(float yoffset);
//
//private:
//    // Updates the Front, Right, and Up vectors
//    void UpdateCameraVectors();
//};
//
//#endif // CAMERA_H
