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

struct Transform {
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);
    glm::mat4 to_mat4() {
        glm::mat4 m = glm::translate(glm::mat4(1), position);
        m *= glm::mat4_cast(glm::quat(rotation));
        m = glm::scale(m, scale);
        return m;
    };
    glm::vec3 to_forward_vector() {
        glm::quat q = glm::quat(rotation);
        return glm::normalize(q * glm::vec3(0.0f, 0.0f, 1.0f));
    }
    glm::vec3 to_right_vector() {
        glm::quat q = glm::quat(rotation);
        return glm::normalize(q * glm::vec3(1.0f, 0.0f, 0.0f));
    }
};
 
struct ViewportInfo {
    int width = 0;
    int height = 0;
    int xOffset = 0;
    int yOffset = 0;
};
