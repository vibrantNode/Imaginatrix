#pragma once 
#include "IMCommon/Common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
 
#include "Renderer/Types/Mesh.h"
#include "Types/vk_allocation.h"
#include "Types/vk_frameData.h"


namespace VKBackEnd {
	void CreateVulkanInstance();

	void HandleFrameBufferResized();

    void Init();
	void SetGLFWSurface();
	void SelectPhysicalDevice();
	void CreateSwapchain();
	void CreateCommandBuffers();
    void RecreateDynamicSwapchain();
    void SetGLFWSurface();
    void SelectPhysicalDevice();
    void CreateSwapchain();
    void CreateCommandBuffers();
    void CreateSyncStructures();
    void CreateSampler();
    bool FrameBufferWasResized();
    void MarkFrameBufferAsResized();
    VkDevice GetDevice();
    VkSurfaceKHR GetSurface();
    VkSwapchainKHR GetSwapchain();
    int32_t GetFrameIndex();
    VkQueue GetGraphicsQueue();
 
    VmaAllocator GetAllocator();
    VkDescriptorPool GetDescriptorPool();
    VkSampler GetSampler();
    std::vector<VkImage>& GetSwapchainImages();
    void AdvanceFrameIndex();

    inline AllocatedBuffer _mainVertexBuffer;
    inline AllocatedBuffer _mainIndexBuffer;
 
 
}