#include "VkRenderer.h"

namespace VKRenderer {


    struct Pipelines {
        //Pipeline gBuffer;
        //Pipeline gBufferSkinned;
        //Pipeline lighting;
        //Pipeline ui;
        //Pipeline uiHiRes;
        //Pipeline debugLines;
        //Pipeline debugPoints;
        //Pipeline debugPointCloud;
        //Pipeline debugProbes;
        //Pipeline bulletHoleDecals;
        //Pipeline glass;
        //Pipeline flipbook;
        //Pipeline horizontalBlur;
        //Pipeline verticalBlur;
        //ComputePipeline computeTest;
        //ComputePipeline computeSkin;
        //ComputePipeline emissiveComposite;
    } _pipelines;



    void SetViewportSize(VkCommandBuffer commandBuffer, int width, int height);
    //void SetViewportSize(VkCommandBuffer commandBuffer, Vulkan::RenderTarget renderTarget);
    //void BindPipeline(VkCommandBuffer commandBuffer, Pipeline& pipeline);
}


void VKRenderer::CreateMinimumShaders()
{

}

void VKRenderer::CreateRenderTargets()
{
}

void VKRenderer::CreateCommandBuffers()
{
}

void VKRenderer::CreateSyncStructures()
{
}

void VKRenderer::CreateSampler()
{
}

void VKRenderer::CreateDescriptorSets()
{
}

void VKRenderer::CreatePipelinesMinimum()
{
}

void VKRenderer::CreateStorageBuffers()
{
}
