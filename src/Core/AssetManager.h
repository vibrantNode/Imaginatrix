#pragma once
#include <string>
#include "IMCommon/RendererCommon.h"
#include "Renderer/Types/Mesh.h"

namespace AssetManager {

	
	void UploadVertexData();
	int CreateMesh(std::string name, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	std::vector<Vertex>& GetVertices();
	std::vector<uint32_t>& GetIndices();


	// Getters
	int GetMeshIndexByName(const std::string& name);
	Mesh* GetMeshByIndex(int index);


	static const std::vector<Mesh>& GetMeshes() {
		//return g_meshes;
	}
}