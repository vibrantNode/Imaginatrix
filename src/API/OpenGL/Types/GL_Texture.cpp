#include "GL_Texture.h"
#include <iostream>
#include <stb_image.h>
#include <stdexcept>


GLuint OGLTexture::GetID() {
    return m_ID;
}

void OGLTexture::Bind(unsigned int slot) {
    // Ensure a valid ID exists before binding
    if (m_ID == 0) {
        std::cerr << "Error: Attempting to bind an uninitialized texture!" << std::endl;
        return;
    }

    // Activate the texture unit and bind the texture
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}


bool OGLTexture::Load(const std::string filepath) {
    // Store the file path for future reference
    m_fullPath = filepath;
    m_filename = filepath.substr(filepath.find_last_of("/\\") + 1);

    // Generate a texture ID
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    // Set texture wrapping and filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load the texture image
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // Flip the texture on the y-axis
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        // Determine the image format
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

        // Upload the texture to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
        return true; // Successfully loaded
    }
    else {
        std::cerr << "Failed to load texture: " << filepath << std::endl;
        stbi_image_free(data);
        return false; // Failed to load
    }
}