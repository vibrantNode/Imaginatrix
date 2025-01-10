#include "AssetManager.h"
#include "API/OpenGL/OGLBackEnd.h"
#include "BackEnd/BackEnd.h"
#include "Renderer/Types/Mesh.h"

#include <iostream>


namespace AssetManager {
    std::vector<Vertex> g_vertices;
    std::vector<uint32_t> g_indices;

    std::vector<Mesh> g_meshes;
    std::unordered_map<std::string, int> g_meshIndexMap;

    // Data inserts for vectors above
    int _nextVertexInsert = 0;
    int _nextIndexInsert = 0;
}

int AssetManager::CreateMesh(std::string name, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    Mesh& mesh = g_meshes.emplace_back();
    mesh.baseVertex = _nextVertexInsert;
    mesh.baseIndex = _nextIndexInsert;
    mesh.vertexCount = (uint32_t)vertices.size();
    mesh.indexCount = (uint32_t)indices.size();
    mesh.name = name;
    

    g_vertices.reserve(g_vertices.size() + vertices.size());
    g_vertices.insert(std::end(g_vertices), std::begin(vertices), std::end(vertices));
    g_indices.reserve(g_indices.size() + indices.size());
    g_indices.insert(std::end(g_indices), std::begin(indices), std::end(indices));
    _nextVertexInsert += mesh.vertexCount;
    _nextIndexInsert += mesh.indexCount;
    return g_meshes.size() - 1;
}

void AssetManager::UploadVertexData() {
	if (BackEnd::GetAPI() == API::OPENGL) {
		OGLBackEnd::UploadVertexData(g_vertices, g_indices);
	}
}

std::vector<Vertex>& AssetManager::GetVertices() {
    return g_vertices;
}


std::vector<uint32_t>& AssetManager::GetIndices() {
    return g_indices;
}

Mesh* AssetManager::GetMeshByIndex(int index) {
    if (index >= 0 && index < g_meshes.size()) {
        return &g_meshes[index];
    }
    else {
        std::cout << "AssetManager::GetMeshByIndex() failed because index '" << index << "' is out of range. Size is " << g_meshes.size() << "!\n";
        return nullptr;
    }
}


int AssetManager::GetMeshIndexByName(const std::string& name) {
    auto it = g_meshIndexMap.find(name);
    if (it != g_meshIndexMap.end()) {
        return it->second;
    }
    std::cout << "AssetManager::GetMeshIndexByName() failed because name '" << name << "' was not found in _meshes!\n";
    return -1;
}