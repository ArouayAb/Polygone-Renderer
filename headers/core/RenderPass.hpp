//
// Created by Arouay on 02/04/2023.
//

#ifndef DRAFT_VK_RENDERPASS_HPP
#define DRAFT_VK_RENDERPASS_HPP

#include <vulkan/vulkan_core.h>

namespace dvk {

    class RenderPass {
    private:
        VkRenderPass renderPass{};
        VkDevice* device;
        VkFormat* swapchainImageFormat;

        void createRenderPass();
    public:
        RenderPass(VkDevice* device, VkFormat* swapchainImageFormat);
        ~RenderPass();

        VkRenderPass* getRenderPass();
    };

} // dvk

#endif //DRAFT_VK_RENDERPASS_HPP
