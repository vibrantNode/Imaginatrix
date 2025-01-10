#include "RenderData.h"
#include "Core/AssetManager.h"




void RenderData::PopluateDummyMesh() {
    // Define a simple triangle
    std::vector<Vertex> triangleVertices = {
        Vertex({0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
        Vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}),
        Vertex({1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f})
    };

    std::vector<uint32_t> triangleIndices = { 0, 1, 2 };

    // Define a simple quad
    std::vector<Vertex> quadVertices = {
        Vertex({-1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
        Vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}),
        Vertex({1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}),
        Vertex({1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f})
    };

    std::vector<uint32_t> quadIndices = { 0, 1, 2, 2, 3, 0 };

    // Use AssetManager to create the meshes
    AssetManager::CreateMesh("Triangle", triangleVertices, triangleIndices);
    AssetManager::CreateMesh("Quad", quadVertices, quadIndices);
}