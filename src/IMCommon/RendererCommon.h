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
struct CameraData {

    glm::mat4 projection = glm::mat4(1);
    glm::mat4 projectionInverse = glm::mat4(1);
    glm::mat4 view = glm::mat4(1);
    glm::mat4 viewInverse = glm::mat4(1);

    float viewportWidth = 0;
    float viewportHeight = 0;
    float viewportOffsetX = 0;
    float viewportOffsetY = 0;

    float clipSpaceXMin;
    float clipSpaceXMax;
    float clipSpaceYMin;
    float clipSpaceYMax;

    float contrast;
    float colorMultiplierR;
    float colorMultiplierG;
    float colorMultiplierB;
};
struct ViewportInfo {
    int width = 0;
    int height = 0;
    int xOffset = 0;
    int yOffset = 0;
};
