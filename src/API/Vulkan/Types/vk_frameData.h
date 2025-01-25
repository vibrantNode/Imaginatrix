#pragma once
#include <vulkan/vulkan.h>
#include "vk_buffer.h"
 

struct FrameData {

    VkSemaphore _presentSemaphore, _renderSemaphore;
    VkFence _renderFence;
    VkCommandPool _commandPool;
    VkCommandBuffer _commandBuffer;

    struct DrawCommandBuffers {
        Buffer geometry;
    };

    struct Buffers {
        Buffer defaultBuffer;
        DrawCommandBuffers drawCommandBuffers[1]; // one struct for each player

        Buffer geometryInstanceData;
    } buffers;
     
};