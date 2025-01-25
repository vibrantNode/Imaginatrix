#include "VkBackEnd.h"
#include "BackEnd/BackEnd.h"
 
#define GLM_FORCE_SILENT_WARNINGS
#define GLM_ENABLE_EXPERIMENTAL
#define VMA_IMPLEMENTATION
#define GLFW_INCLUDE_VULKAN
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.h>
#include "VkBootstrap.h"
#include "VkRenderer.h"
#include "vk_mem_alloc.h"




namespace VKBackEnd {

    struct UploadContext {
        VkFence _uploadFence;
        VkCommandPool _commandPool;
        VkCommandBuffer _commandBuffer;
    };

    VkDevice _device;
    VkInstance _instance;
    VmaAllocator _allocator;
    VkSurfaceKHR _surface;
    VkSwapchainKHR _swapchain;
    VkFormat _swachainImageFormat;
    VkSampler _sampler;
    VkDescriptorPool _descriptorPool;
    VkExtent2D _renderTargetPresentExtent = { 768 , 432 };
    VkExtent2D _windowedModeExtent = { 2280, 1620 };
    VkExtent2D _currentWindowExtent = { };
    VkDebugUtilsMessengerEXT _debugMessenger;
    VkPhysicalDeviceMemoryProperties _memoryProperties;
    VkPhysicalDevice _physicalDevice;
    VkPhysicalDeviceProperties _gpuProperties;
    VkPhysicalDeviceRayTracingPipelinePropertiesKHR  _rayTracingPipelineProperties = {};
    VkPhysicalDeviceAccelerationStructureFeaturesKHR accelerationStructureFeatures = {};
    std::vector<VkImage> _swapchainImages;
    std::vector<VkImageView> _swapchainImageViews;

    UploadContext _uploadContext;
//    FrameData _frames[FRAME_OVERLAP];
    int _frameNumber = { 0 };

    uint32_t g_allocatedSkinnedVertexBufferSize = 0;

    PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;
    PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
    PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR;
    PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
    PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR;
    PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR;
    PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
    PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;
    PFN_vkDebugMarkerSetObjectTagEXT pfnDebugMarkerSetObjectTag;
    PFN_vkDebugMarkerSetObjectNameEXT pfnDebugMarkerSetObjectName;
    PFN_vkCmdDebugMarkerBeginEXT pfnCmdDebugMarkerBegin;
    PFN_vkCmdDebugMarkerEndEXT pfnCmdDebugMarkerEnd;
    PFN_vkCmdDebugMarkerInsertEXT pfnCmdDebugMarkerInsert;
    PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT;

    inline VkQueue _graphicsQueue;
    inline uint32_t _graphicsQueueFamily;
    vkb::Instance _bootstrapInstance;
    bool _frameBufferResized = false;
    bool _enableValidationLayers = true;
    bool _printAvaliableExtensions = false;

    bool _forceCloseWindow;

    void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

   

    inline uint32_t _mainIndexCount;


    VkDevice GetDevice() {
        return _device;
    }
    VkSurfaceKHR GetSurface() {
        return _surface;
    }
    VkSwapchainKHR GetSwapchain() {
        return _swapchain;
    }
  
    VkQueue GetGraphicsQueue() {
        return _graphicsQueue;
    }
  /*  int32_t GetFrameIndex() {
        return _frameNumber % FRAME_OVERLAP;
    }
    FrameData& GetCurrentFrame() {
        return _frames[GetFrameIndex()];
    }
    FrameData& GetFrameByIndex(int index) {
        return _frames[index];
    }*/
    VmaAllocator GetAllocator() {
        return _allocator;
    }
    VkDescriptorPool GetDescriptorPool() {
        return _descriptorPool;
    }
    VkSampler VKBackEnd::GetSampler() {
        return _sampler;
    }
    std::vector<VkImage>& GetSwapchainImages() {
        return _swapchainImages;
    }
    void VKBackEnd::AdvanceFrameIndex() {
        _frameNumber++;
    }
}

bool VKBackEnd::FrameBufferWasResized() {
    return _frameBufferResized;
}

void VKBackEnd::MarkFrameBufferAsResized() {
    _frameBufferResized = true;
}

void VKBackEnd::HandleFrameBufferResized() {
    //RecreateDynamicSwapchain();
    _frameBufferResized = false;
}

void VKBackEnd::Init()
{
    SetGLFWSurface();
    SelectPhysicalDevice();
    CreateSwapchain();

    VKRenderer::CreateMinimumShaders();
    VKRenderer::CreateRenderTargets();


    CreateCommandBuffers();
    CreateSyncStructures();
    CreateSampler();

    VKRenderer::CreateDescriptorSets();
    VKRenderer::CreatePipelinesMinimum();

    VKRenderer::CreateStorageBuffers();
 
}
void VKBackEnd::SetGLFWSurface() {
    glfwCreateWindowSurface(_instance, BackEnd::GetWindowPointer(), nullptr, &_surface);
}



void VKBackEnd::CreateVulkanInstance() {
    vkb::InstanceBuilder builder;
    builder.set_app_name("Imaginatrix");
    builder.request_validation_layers(_enableValidationLayers);
    builder.use_default_debug_messenger();
    builder.require_api_version(1, 3, 0);
    _bootstrapInstance = builder.build().value();
    _instance = _bootstrapInstance.instance;
    _debugMessenger = _bootstrapInstance.debug_messenger;
}

void VKBackEnd::SelectPhysicalDevice() {

    vkb::PhysicalDeviceSelector selector{ _bootstrapInstance };
    selector.add_required_extension(VK_KHR_MAINTENANCE_4_EXTENSION_NAME);					// Hides shader warnings for unused variables
    selector.add_required_extension(VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME);				// Dynamic rendering
    selector.add_required_extension(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME);			// Ray tracing related extensions required by this sample
    selector.add_required_extension(VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME);			// Ray tracing related extensions required by this sample
    selector.add_required_extension(VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME);			// Required by VK_KHR_acceleration_structure
    selector.add_required_extension(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);		// Required by VK_KHR_acceleration_structure
    selector.add_required_extension(VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME);				// Required by VK_KHR_acceleration_structure
    selector.add_required_extension(VK_KHR_SPIRV_1_4_EXTENSION_NAME);						// Required for VK_KHR_ray_tracing_pipeline
    selector.add_required_extension(VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME);			// Required by VK_KHR_spirv_1_4
    selector.add_required_extension(VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_EXTENSION_NAME);	// aftermath
    selector.add_required_extension(VK_NV_DEVICE_DIAGNOSTICS_CONFIG_EXTENSION_NAME);		// aftermath

    selector.add_required_extension(VK_KHR_RAY_QUERY_EXTENSION_NAME);

    VkPhysicalDeviceRayTracingPipelineFeaturesKHR rayTracingPipelineFeatures{};
    rayTracingPipelineFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
    rayTracingPipelineFeatures.rayTracingPipeline = VK_TRUE;
    rayTracingPipelineFeatures.rayTraversalPrimitiveCulling = VK_TRUE;
    rayTracingPipelineFeatures.pNext = nullptr;

    VkPhysicalDeviceAccelerationStructureFeaturesKHR accelerationStructureFeatures{};
    accelerationStructureFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
    accelerationStructureFeatures.accelerationStructure = VK_TRUE;
    accelerationStructureFeatures.pNext = &rayTracingPipelineFeatures;

    VkPhysicalDeviceRayQueryFeaturesKHR rayQueryFeatures{};
    rayQueryFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
    rayQueryFeatures.rayQuery = VK_TRUE;
    rayQueryFeatures.pNext = &accelerationStructureFeatures;

    VkPhysicalDeviceFeatures features = {};
    features.samplerAnisotropy = true;
    features.shaderInt64 = true;
    features.multiDrawIndirect = true;
    selector.set_required_features(features);

    VkPhysicalDeviceVulkan12Features features12 = {};
    features12.shaderSampledImageArrayNonUniformIndexing = true;
    features12.runtimeDescriptorArray = true;
    features12.descriptorBindingVariableDescriptorCount = true;
    features12.descriptorBindingPartiallyBound = true;
    features12.descriptorIndexing = true;
    features12.bufferDeviceAddress = true;
    features12.scalarBlockLayout = true;
    selector.set_required_features_12(features12);

    VkPhysicalDeviceVulkan13Features features13 = {};
    features13.maintenance4 = true;
    features13.dynamicRendering = true;
    features13.pNext = &rayQueryFeatures;	// you probably want to confirm this chaining of pNexts works when shit goes wrong.
    selector.set_required_features_13(features13);

    selector.set_minimum_version(1, 3);
    selector.set_surface(_surface);
    vkb::PhysicalDevice physicalDevice = selector.select().value();
    vkb::DeviceBuilder deviceBuilder{ physicalDevice };

    // store these for some ray tracing stuff.
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &_memoryProperties);

    // Query available device extensions
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

    // Check if extension is supported
    //bool maintenance4ExtensionSupported = false;
    for (const auto& extension : availableExtensions) {
        if (std::string(extension.extensionName) == VK_KHR_RAY_QUERY_EXTENSION_NAME) {
            //maintenance4ExtensionSupported = true;
            std::cout << "VK_KHR_RAY_QUERY_EXTENSION_NAME is supported\n";
            break;
        }
    }
    // Specify the extensions to enable
    //std::vector<const char*> enabledExtensions = {
    //    VK_KHR_MAINTENANCE_4_EXTENSION_NAME
    //};
    //if (!maintenance4ExtensionSupported) {
    //    throw std::runtime_error("Required extension not supported");
   // }

    vkb::Device vkbDevice = deviceBuilder.build().value();
    _device = vkbDevice.device;
    _physicalDevice = physicalDevice.physical_device;
    _graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
    _graphicsQueueFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

    // Initialize the memory allocator
    VmaAllocatorCreateInfo allocatorInfo = {};
    allocatorInfo.physicalDevice = _physicalDevice;
    allocatorInfo.device = _device;
    allocatorInfo.instance = _instance;
    allocatorInfo.flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;
    vmaCreateAllocator(&allocatorInfo, &_allocator);

    vkGetPhysicalDeviceProperties(_physicalDevice, &_gpuProperties);

    auto instanceVersion = VK_API_VERSION_1_0;
    auto FN_vkEnumerateInstanceVersion = PFN_vkEnumerateInstanceVersion(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));
    if (vkEnumerateInstanceVersion) {
        vkEnumerateInstanceVersion(&instanceVersion);
    }

    uint32_t major = VK_VERSION_MAJOR(instanceVersion);
    uint32_t minor = VK_VERSION_MINOR(instanceVersion);
    uint32_t patch = VK_VERSION_PATCH(instanceVersion);
    std::cout << "Vulkan: " << major << "." << minor << "." << patch << "\n\n";

    if (_printAvaliableExtensions) {
        uint32_t deviceExtensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &deviceExtensionCount, nullptr);
        std::vector<VkExtensionProperties> deviceExtensions(deviceExtensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &deviceExtensionCount, deviceExtensions.data());
        std::cout << "Available device extensions:\n";
        for (const auto& extension : deviceExtensions) {
            std::cout << ' ' << extension.extensionName << "\n";
        }
        std::cout << "\n";
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::cout << "Available instance extensions:\n";
        for (const auto& extension : extensions) {
            std::cout << ' ' << extension.extensionName << "\n";
        }
        std::cout << "\n";
    }

    // Get the ray tracing and acceleration structure related function pointers required by this sample
    vkGetBufferDeviceAddressKHR = reinterpret_cast<PFN_vkGetBufferDeviceAddressKHR>(vkGetDeviceProcAddr(_device, "vkGetBufferDeviceAddressKHR"));
    vkCmdBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresKHR>(vkGetDeviceProcAddr(_device, "vkCmdBuildAccelerationStructuresKHR"));
    vkBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkBuildAccelerationStructuresKHR>(vkGetDeviceProcAddr(_device, "vkBuildAccelerationStructuresKHR"));
    vkCreateAccelerationStructureKHR = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(vkGetDeviceProcAddr(_device, "vkCreateAccelerationStructureKHR"));
    //vkDestroyAccelerationStructureKHR = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(vkGetDeviceProcAddr(_device, "vkDestroyAccelerationStructureKHR"));
    vkGetAccelerationStructureBuildSizesKHR = reinterpret_cast<PFN_vkGetAccelerationStructureBuildSizesKHR>(vkGetDeviceProcAddr(_device, "vkGetAccelerationStructureBuildSizesKHR"));
    vkGetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(vkGetDeviceProcAddr(_device, "vkGetAccelerationStructureDeviceAddressKHR"));
    //vkCmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(vkGetDeviceProcAddr(_device, "vkCmdTraceRaysKHR"));
    // ----------------------------------------------------------------------*****
    //VKRenderer::LoadRaytracingFunctionPointer();
    vkGetRayTracingShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(vkGetDeviceProcAddr(_device, "vkGetRayTracingShaderGroupHandlesKHR"));
    vkCreateRayTracingPipelinesKHR = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(vkGetDeviceProcAddr(_device, "vkCreateRayTracingPipelinesKHR"));

    // Debug marker shit
    vkSetDebugUtilsObjectNameEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(vkGetDeviceProcAddr(_device, "vkSetDebugUtilsObjectNameEXT"));

    // Get ray tracing pipeline properties, which will be used later on in the sample
    _rayTracingPipelineProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
    VkPhysicalDeviceProperties2 deviceProperties2{};
    deviceProperties2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    deviceProperties2.pNext = &_rayTracingPipelineProperties;
    vkGetPhysicalDeviceProperties2(_physicalDevice, &deviceProperties2);

    // Get acceleration structure properties, which will be used later on in the sample
    accelerationStructureFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
    VkPhysicalDeviceFeatures2 deviceFeatures2{};
    deviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    deviceFeatures2.pNext = &accelerationStructureFeatures;
    vkGetPhysicalDeviceFeatures2(_physicalDevice, &deviceFeatures2);
}


void VKBackEnd::RecreateDynamicSwapchain() {
    while (_currentWindowExtent.width == 0 || _currentWindowExtent.height == 0) {
        _currentWindowExtent.width = BackEnd::GetCurrentWindowWidth();
        _currentWindowExtent.height = BackEnd::GetCurrentWindowHeight();
        glfwWaitEvents();
    }
    vkDeviceWaitIdle(_device);
    for (int i = 0; i < _swapchainImages.size(); i++) {
        vkDestroyImageView(_device, _swapchainImageViews[i], nullptr);
    }
    vkDestroySwapchainKHR(_device, _swapchain, nullptr);
    CreateSwapchain();
}

void VKBackEnd::CreateSwapchain() {

    _currentWindowExtent.width = BackEnd::GetCurrentWindowWidth();
    _currentWindowExtent.height = BackEnd::GetCurrentWindowHeight();

    VkSurfaceFormatKHR format;
    format.colorSpace = VkColorSpaceKHR::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    format.format = VkFormat::VK_FORMAT_R8G8B8A8_UNORM;

    vkb::SwapchainBuilder swapchainBuilder(_physicalDevice, _device, _surface);
    swapchainBuilder.set_desired_format(format);
    swapchainBuilder.set_desired_present_mode(VK_PRESENT_MODE_IMMEDIATE_KHR);
    swapchainBuilder.set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR);
    swapchainBuilder.set_desired_present_mode(VK_PRESENT_MODE_MAILBOX_KHR);
    swapchainBuilder.set_desired_extent(_currentWindowExtent.width, _currentWindowExtent.height);
    swapchainBuilder.set_image_usage_flags(VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT); // added so you can blit into the swapchain

    vkb::Swapchain vkbSwapchain = swapchainBuilder.build().value();
    _swapchain = vkbSwapchain.swapchain;
    _swapchainImages = vkbSwapchain.get_images().value();
    _swapchainImageViews = vkbSwapchain.get_image_views().value();
    _swachainImageFormat = vkbSwapchain.image_format;
}

void VKBackEnd::CreateCommandBuffers()
{
    VkCommandPoolCreateInfo commandPoolInfo = {};
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    commandPoolInfo.pNext = nullptr;

//    for (int i = 0; i < FRAME_OVERLAP; i++) {
//        VK_CHECK(vkCreateCommandPool(_device, &commandPoolInfo, nullptr, &_frames[i]._commandPool));
//        VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
//        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//        commandBufferAllocateInfo.commandPool = _frames[i]._commandPool;
//        commandBufferAllocateInfo.commandBufferCount = 1;
//        commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//        commandBufferAllocateInfo.pNext = nullptr;
////        VK_CHECK(vkAllocateCommandBuffers(_device, &commandBufferAllocateInfo, &_frames[i]._commandBuffer));
//    }

    //create command pool for upload context
    VkCommandPoolCreateInfo uploadCommandPoolInfo = {};
    uploadCommandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    uploadCommandPoolInfo.flags = 0;
    uploadCommandPoolInfo.pNext = nullptr;

    //create command buffer for upload context
    VK_CHECK(vkCreateCommandPool(_device, &uploadCommandPoolInfo, nullptr, &_uploadContext._commandPool));
    VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.commandPool = _uploadContext._commandPool;
    commandBufferAllocateInfo.commandBufferCount = 1;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferAllocateInfo.pNext = nullptr;
    VK_CHECK(vkAllocateCommandBuffers(_device, &commandBufferAllocateInfo, &_uploadContext._commandBuffer));
}


void VKBackEnd::CreateSyncStructures() {

    VkFenceCreateInfo fenceCreateInfo = {};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    fenceCreateInfo.pNext = nullptr;

    VkSemaphoreCreateInfo semaphoreCreateInfo = {};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreCreateInfo.flags = 0;
    semaphoreCreateInfo.pNext = nullptr;

    //for (int i = 0; i < FRAME_OVERLAP; i++) {
    //    VK_CHECK(vkCreateFence(_device, &fenceCreateInfo, nullptr, &_frames[i]._renderFence));
    //    VK_CHECK(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &_frames[i]._presentSemaphore));
    //    VK_CHECK(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &_frames[i]._renderSemaphore));
    //}

    VkFenceCreateInfo uploadFenceCreateInfo = {};
    uploadFenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    uploadFenceCreateInfo.flags = 0;
    uploadFenceCreateInfo.pNext = nullptr;

    VK_CHECK(vkCreateFence(_device, &uploadFenceCreateInfo, nullptr, &_uploadContext._uploadFence));
}

void VKBackEnd::CreateSampler() {
    VkSamplerCreateInfo samplerInfo = {};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.compareOp = VK_COMPARE_OP_NEVER;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 12.0f;
    samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
    samplerInfo.maxAnisotropy = _gpuProperties.limits.maxSamplerAnisotropy;;
    samplerInfo.anisotropyEnable = VK_TRUE;
    samplerInfo.pNext = nullptr;
    vkCreateSampler(_device, &samplerInfo, nullptr, &_sampler);
}

uint32_t alignedSize(uint32_t value, uint32_t alignment) {
    return (value + alignment - 1) & ~(alignment - 1);
}


//                     //
//      Callbacks      //
//                     //

void VKBackEnd::FramebufferResizeCallback(GLFWwindow* window, int width, int height) {
    _frameBufferResized = true;
}
