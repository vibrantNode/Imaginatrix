#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath> // For sin and cos functions

// Constructor
Camera::Camera(glm::vec3 position, float yaw, float pitch)
    : m_Position(position), m_Yaw(yaw), m_Pitch(pitch),
    m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_Zoom(75.0f), m_MovementSpeed(20.5f) {
    UpdateCameraVectors();
}

// Mouse movement processing
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    const float sensitivity = 0.1f;  // Adjust this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_Yaw += xoffset;
    m_Pitch += yoffset;

    if (constrainPitch) {
        if (m_Pitch > 89.0f) m_Pitch = 89.0f;
        if (m_Pitch < -89.0f) m_Pitch = -89.0f;
    }

    UpdateCameraVectors();
}


// Keyboard input processing (with adjustable speed)
void Camera::ProcessKeyboardInput(int direction, float deltaTime) {
    float velocity = m_MovementSpeed * deltaTime;  // Use movement speed
    if (direction == FORWARD)
        m_Position += m_Front * velocity;
    if (direction == BACKWARD)
        m_Position -= m_Front * velocity;
    if (direction == LEFT)
        m_Position -= m_Right * velocity;
    if (direction == RIGHT)
        m_Position += m_Right * velocity;
}

void Camera::Jump(float jumpHeight) {
    m_Position.y += jumpHeight;  // Move up by jumpHeight units
}

void Camera::TeleportDownward(float distance) {
    m_Position.y -= distance;  // Move down by the specified distance
}

void Camera::TeleportInDirection(int direction) {
    const float teleportDistance = 0.40f; // Set teleport distance to 50 units

    if (direction == FORWARD) {
        m_Position += m_Front * teleportDistance;
    }
    else if (direction == BACKWARD) {
        m_Position -= m_Front * teleportDistance;
    }
    else if (direction == LEFT) {
        m_Position -= m_Right * teleportDistance;
    }
    else if (direction == RIGHT) {
        m_Position += m_Right * teleportDistance;
    }
}
// Update the camera vectors based on yaw and pitch
void Camera::UpdateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);

    // Update right and up vectors
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

// Get the camera's zoom (field of view)
float Camera::GetZoom() const {
    return m_Zoom;
}

// Set the movement speed of the camera
void Camera::SetMovementSpeed(float speed) {
    m_MovementSpeed = speed;
}
// Get the view matrix
glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}
// Get the camera position
glm::vec3 Camera::GetPosition() const {
    return m_Position;
}