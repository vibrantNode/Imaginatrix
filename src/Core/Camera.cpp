//#include "Camera.h"
//
//Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float zoom)
//    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
//    MovementSpeed(2.5f),
//    MouseSensitivity(0.1f),
//    Zoom(zoom),
//    Position(position),
//    WorldUp(up),
//    Yaw(yaw),
//    Pitch(pitch) {
//    UpdateCameraVectors();
//}
//
//glm::mat4 Camera::GetViewMatrix() const {
//    return glm::lookAt(Position, Position + Front, Up);
//}
//
//float Camera::GetZoom() const {
//    return Zoom;
//}
//
//void Camera::ProcessKeyboardInput(int direction, float deltaTime) {
//    float velocity = MovementSpeed * deltaTime;
//    Position += direction * velocity;
//    // Add further movement logic as needed
//}
//
//void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
//    xoffset *= MouseSensitivity;
//    yoffset *= MouseSensitivity;
//
//    Yaw += xoffset;
//    Pitch += yoffset;
//
//    if (constrainPitch) {
//        if (Pitch > 89.0f) Pitch = 89.0f;
//        if (Pitch < -89.0f) Pitch = -89.0f;
//    }
//
//    UpdateCameraVectors();
//}
//
//void Camera::ProcessMouseScroll(float yoffset) {
//    Zoom -= yoffset;
//    if (Zoom < 1.0f) Zoom = 1.0f;
//    if (Zoom > 45.0f) Zoom = 45.0f;
//}
//
//void Camera::UpdateCameraVectors() {
//    glm::vec3 front;
//    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//    front.y = sin(glm::radians(Pitch));
//    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//    Front = glm::normalize(front);
//
//    // Recalculate Right and Up vectors
//    Right = glm::normalize(glm::cross(Front, WorldUp));
//    Up = glm::normalize(glm::cross(Right, Front));
//}
