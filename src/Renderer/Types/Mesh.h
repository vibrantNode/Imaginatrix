#pragma once
#include <glm/glm.hpp>
#include <string>


struct Mesh {

    std::string name = "undefined";

    int32_t baseVertex = 0;
    uint32_t baseIndex = 0;
    uint32_t vertexCount = 0;
    uint32_t indexCount = 0;

    bool uploadedToGPU = false;
};