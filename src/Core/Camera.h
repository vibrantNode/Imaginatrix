#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT	
};

class Camera {
public:
    Camera() = default;
	Camera(glm::vec3 position, float yaw, float pitch);

	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	void ProcessKeyboardInput(int direction, float deltaTime);

	glm::mat4 GetViewMatrix() const;

	void UpdateIdleMovement(float deltaTime);

	float GetZoom() const;

    // Set movement speed
    void SetMovementSpeed(float speed);

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    glm::vec3 GetPosition() const;

    void Jump(float jumpHeight);

    void TeleportDownward(float distance); // Moves the camera down

    void TeleportInDirection(int direction);

    static Camera& GetInstance() {
        static Camera instance;  // This ensures that the Camera instance is created only once
        return instance;
    }
private:

    float m_LastX; // Last mouse x position
    float m_LastY; // Last mouse y position
    float m_MouseSensitivity; // Sensitivity factor for mouse input
    // Deadzone
    float m_MouseDeadZone;
    // Inertia
    glm::vec3 m_Velocity;
    // Camera attributes
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;

    // Euler angles
    float m_Yaw;
    float m_Pitch;

    // Camera options
    float m_Zoom;
    float m_MovementSpeed;  // Added movement speed

    // Update camera vectors
    void UpdateCameraVectors();

    // Prevent copying and assignment
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
};