#pragma once

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/hash.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct Vertex {
	glm::vec3 position{ 0.0f }; // Default to origin
	glm::vec3 normal{ 0.0f };   // Default to zero vector
	glm::vec3 texCoord{ 0.0f }; // Default to zero vector
	glm::vec3 color{ 1.0f };    // Default to white color

	Vertex() = default;



    // Constructor to initialize all attributes
    Vertex(const glm::vec3& _position, const glm::vec3& _normal, const glm::vec3& _texCoord, const glm::vec3& _color)
        : position(_position), normal(_normal), texCoord(_texCoord), color(_color) {
    }

    // Constructor without normal
    Vertex(const glm::vec3& _position, const glm::vec3& _texCoord, const glm::vec3& _color)
        : position(_position), texCoord(_texCoord), color(_color) {
    }

    // Constructor with only position and color
    explicit Vertex(const glm::vec3& _position, const glm::vec3& _color)
        : position(_position), color(_color) {
    }
};