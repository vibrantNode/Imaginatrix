#include "OGLRenderer.h"
#include "OGLBackEnd.h"
#include "BackEnd/BackEnd.h"
#include "Renderer/Types/Mesh.h"
#include "Core/AssetManager.h"
#include "Core/Camera.h"
#include "Types/GL_Shader.h"
#include "Types/GL_Texture.h"
#include "IMCommon/RendererCommon.h"
#include <iostream>


/*
TASK LIST:

Implement a tranform class / struct

*/

namespace OGLRenderer {

   

	struct Shaders {
		Shader _defaultShader;
        Shader _skyboxShader;

	}g_shaders;


}

//void GeometryPass();

void OGLRenderer::Init() {
    AssetManager::LoadTextures();
    LoadShaders();
}

void OGLRenderer::Render() {

    g_shaders._defaultShader.Bind();

    // Set up matrices
    int width, height;
    glfwGetFramebufferSize(BackEnd::GetWindowPointer(), &width, &height);
    glm::mat4 projection = glm::perspective(glm::radians(BackEnd::GetCamera().GetZoom()), (float)width / height, 0.1f, 100.0f);
    glm::mat4 view = BackEnd::GetCamera().GetViewMatrix();

    g_shaders._defaultShader.SetUniformMat4("view", view);
    g_shaders._defaultShader.SetUniformMat4("projection", projection);


    // Use Transform struct for model transformation
    Transform objTransform;
    objTransform.position = glm::vec3(0.0f, 0.0f, 0.0f); // Set position
    objTransform.rotation = glm::vec3(glm::radians(90.0f), 0.0f, 0.0f); // Set rotation (90 degrees around X-axis)
    objTransform.scale = glm::vec3(19.0f, 12.0f, 11.0f); // Set scale


    // Generate model matrix
    glm::mat4 model = objTransform.to_mat4();
    
    g_shaders._defaultShader.SetUniformMat4("model", model);

    // Bind the texture
    if (!AssetManager::g_textures.empty()) {
        AssetManager::g_textures[1].Bind(1); // Bind the first texture to slot 1
    }

    glBindVertexArray(OGLBackEnd::GetVertexDataVAO());

    // Test pass of generic mesh
    Mesh* mesh = AssetManager::GetMeshByIndex(1); // Get the mesh by index
    if (mesh) { // Check if the mesh was found (nullptr check)
        glDrawElementsBaseVertex(
            GL_TRIANGLES,
            mesh->indexCount,          // Access the mesh's index count
            GL_UNSIGNED_INT,
            (void*)(mesh->baseIndex * sizeof(uint32_t)),  // Use the mesh's base index
            mesh->baseVertex           // Use the mesh's base vertex
        );
    }
    else {
        std::cerr << "Mesh not found at index!" << std::endl;
    }

    glBindVertexArray(0);
	
}
void OGLRenderer::LoadShaders() {
	std::cout << "Loading Shaders \n";


	g_shaders._defaultShader.Load("default.vert", "default.frag");
    g_shaders._skyboxShader.Load("skybox.vert", "skybox.frag");
}