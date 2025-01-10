#pragma once
#include <string>
#include "IMCommon/RendererCommon.h"
#include "Renderer/Types/Mesh.h"
#include "API/OpenGL/Types/GL_Texture.h"

namespace AssetManager {

	// Asset Loading
	void LoadNextItem();

	extern bool LoadingIsComplete;

	bool LoadingComplete();


	// Getters
	int GetMeshIndexByName(const std::string& name);
	Mesh* GetMeshByIndex(int index);

	std::vector<Vertex>& GetVertices();
	std::vector<uint32_t>& GetIndices();

	// Textures
	bool LoadTextures();

	//OGLTexture* GetTexture(const std::string& textureName);


	// Misc

	void UploadVertexData();
	int CreateMesh(std::string name, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	extern std::vector<OGLTexture> g_textures;

}

