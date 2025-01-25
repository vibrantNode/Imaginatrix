#include "RenderData.h"
#include "Core/AssetManager.h"




void TestData::PopluateDummyMesh() {
    // Define a simple triangle
    std::vector<Vertex> triangleVertices = {
        Vertex({0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
        Vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}),
        Vertex({1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f})
    };

    std::vector<uint32_t> triangleIndices = { 0, 1, 2 };

    // Define a simple quad
    std::vector<Vertex> quadVertices = {
        Vertex({-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}), // Top-left
        Vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}), // Bottom-left
        Vertex({ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}), // Bottom-right
        Vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f})  // Top-right
    };



    std::vector<uint32_t> quadIndices = { 0, 1, 2, 2, 3, 0 };
    // Cube vertices and indices for a skybox
    std::vector<Vertex> cubeVertices = {
        // Front face
        Vertex({-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f,  1.0f}, {0.0f, 0.0f, 1.0f}), // Bottom-left
        Vertex({ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f,  1.0f}, {1.0f, 0.0f, 0.0f}), // Bottom-right
        Vertex({ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f,  1.0f}, {1.0f, 1.0f, 0.0f}), // Top-right
        Vertex({-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f,  1.0f}, {0.0f, 1.0f, 0.0f}), // Top-left

        // Back face
        Vertex({-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f}), // Bottom-left
        Vertex({ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}), // Bottom-right
        Vertex({ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 0.0f}), // Top-right
        Vertex({-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}), // Top-left

        // Left face
        Vertex({-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}), // Bottom-left
        Vertex({-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}), // Bottom-right
        Vertex({-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}), // Top-right
        Vertex({-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}), // Top-left

        // Right face
        Vertex({ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}), // Bottom-left
        Vertex({ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}), // Bottom-right
        Vertex({ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}), // Top-right
        Vertex({ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}), // Top-left

        // Top face
        Vertex({-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}), // Bottom-left
        Vertex({-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}), // Bottom-right
        Vertex({ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}), // Top-right
        Vertex({ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}), // Top-left

        // Bottom face
        Vertex({-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}), // Bottom-left
        Vertex({-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}), // Bottom-right
        Vertex({ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}), // Top-right
        Vertex({ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}), // Top-left
    };


    std::vector<uint32_t> cubeIndices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 13, 14, 14, 15, 12,
        // Top face
        16, 17, 18, 18, 19, 16,
        // Bottom face
        20, 21, 22, 22, 23, 20
    };
    // Use AssetManager to create the meshes
    AssetManager::CreateMesh("Triangle", triangleVertices, triangleIndices);
    AssetManager::CreateMesh("Quad", quadVertices, quadIndices);
    AssetManager::CreateMesh("Skybox", cubeVertices, cubeIndices);
}