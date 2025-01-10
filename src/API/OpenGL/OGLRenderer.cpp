#include "OGLRenderer.h"
#include "OGLBackEnd.h"
#include "Renderer/Types/Mesh.h"
#include "Core/AssetManager.h"
#include "Types/GL_Shader.h"
#include "Types/GL_Texture.h"
#include <iostream>


/*
TASK LIST

 

*/

namespace OGLRenderer {


	struct Shaders {
		Shader _defaultShader;

	}g_shaders;


}

void OGLRenderer::Init() {
    AssetManager::LoadTextures();
    LoadShaders();
}

void OGLRenderer::Render() {

    g_shaders._defaultShader.Bind();

    // Bind the first texture in the AssetManager's texture list (example)
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