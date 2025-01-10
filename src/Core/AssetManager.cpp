#include "AssetManager.h"
#include "API/OpenGL/OGLBackEnd.h"
//#include "API/OpenGL/Types/GL_Texture.h"
#include "BackEnd/BackEnd.h"
#include "Renderer/Types/Mesh.h"

#include <iostream>


namespace AssetManager {

    bool LoadingIsComplete = false;

    // Store everything in vectors and maps

    std::vector<Vertex> g_vertices;
    std::vector<uint32_t> g_indices;

    std::vector<Mesh> g_meshes;
    std::unordered_map<std::string, int> g_meshIndexMap;
    std::vector<OGLTexture> g_textures;

    // Data inserts for vectors above
    int _nextVertexInsert = 0;
    int _nextIndexInsert = 0;


    struct CompletedLoadingTasks {
        bool g_all = false;
        bool g_textures = false;

    }g_completedLoadingTasks;

}

void AssetManager::LoadNextItem() {
    // Textures
    for (OGLTexture& texture : g_textures) {
        if (!texture.Load(texture.GetFilePath())) {
            std::cerr << "Failed to load texture: " << texture.GetFilePath() << std::endl;
        }
        else {
            std::cout << "Loaded texture: " << texture.GetFilePath() << std::endl;
        }
    }


    g_completedLoadingTasks.g_textures = true;
    g_completedLoadingTasks.g_all = g_completedLoadingTasks.g_textures;
}

bool AssetManager::LoadingComplete() {
    return g_completedLoadingTasks.g_all;
}

bool AssetManager::LoadTextures() {
    // Clear any existing textures
    g_textures.clear();

    // Add textures to the vector
    g_textures.emplace_back(OGLTexture("C:/Users/Admin/OneDrive/Desktop/RealTimeRendering/Imaginatrix/res/textures/awesomeface.png"));

    // You can add more textures here if needed
    g_textures.emplace_back(OGLTexture("C:/Users/Admin/OneDrive/Desktop/RealTimeRendering/Imaginatrix/res/textures/spaceFloor.jpg"));

    // Load all textures
    LoadNextItem();

    return g_completedLoadingTasks.g_textures;
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