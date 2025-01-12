#include "GL_Shader.h"
#include "IMCommon/RendererCommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // for glm::value_ptr
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string readTextFromFile(std::string path) {
    std::ifstream file(path);
    std::string str;
    std::string line;
    while (std::getline(file, line)) {
        str += line + "\n";
    }
    return str;
}
int checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";
        }
    }
    return success;
}

void Shader::Load(std::string vertexPath, std::string fragmentPath) {

    std::string vertexSource = readTextFromFile("C:/Users/Admin/OneDrive/Desktop/RealTimeRendering/Imaginatrix/shaders/" + vertexPath);
    std::string fragmentSource = readTextFromFile("C:/Users/Admin/OneDrive/Desktop/RealTimeRendering/Imaginatrix/shaders/" + fragmentPath);

    const char* vShaderCode = vertexSource.c_str();
    const char* fShaderCode = fragmentSource.c_str();

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    int tempID = glCreateProgram();
    glAttachShader(tempID, vertex);
    glAttachShader(tempID, fragment);
    glLinkProgram(tempID);

    if (checkCompileErrors(tempID, "PROGRAM")) {
        if (m_ID != -1) {
            glDeleteProgram(m_ID);
        }
        m_ID = tempID;
        //m_uniformsLocations.clear();
    }
    else {
        std::cout << "shader failed to compile " << vertexPath << " " << fragmentPath << "\n";
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)const {
    int location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' doesn't exist or is not used in the shader." << std::endl;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::Bind() const {
    glUseProgram(m_ID);

}
