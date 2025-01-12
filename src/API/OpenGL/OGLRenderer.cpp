#include "OGLRenderer.h"
#include "OGLBackEnd.h"
#include "Renderer/Types/Mesh.h"
#include "Core/AssetManager.h"
#include "Core/Camera.h"
#include "Types/GL_Shader.h"
#include "Types/GL_Texture.h"
#include <iostream>


/*
TASK LIST:

 The main render function should handle rendering other abstracted render functions for other objects 

*/

namespace OGLRenderer {

    Camera g_camera(glm::vec3(0.0f, 0.0f, 5.0f), -90.0f, 0.0f);


	struct Shaders {
		Shader _defaultShader;

	}g_shaders;


}

//void GeometryPass();

void OGLRenderer::Init() {
    AssetManager::LoadTextures();
    LoadShaders();
}

void OGLRenderer::Render() {

    g_shaders._defaultShader.Bind();

    glm::mat4 view = g_camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(g_camera.GetZoom()),
        800.0f / 600.0f, // Aspect ratio (width/height)
        0.1f, 100.0f     // Near and far planes
    );

    g_shaders._defaultShader.SetUniformMat4("view", view);
    g_shaders._defaultShader.SetUniformMat4("projection", projection);



    // Bind the texture
    if (!AssetManager::g_textures.empty()) {
        AssetManager::g_textures[1].Bind(1); // Bind the first texture to slot 1
    }


    glBindVertexArray(OGLBackEnd::GetVertexDataVAO());


    // Test
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
}