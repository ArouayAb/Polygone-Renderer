//
// Created by Arouay on 02/04/2023.
//

#ifndef DRAFT_VK_FRAMEBUFFERS_HPP
#define DRAFT_VK_FRAMEBUFFERS_HPP

#include <vulkan/vulkan_core.h>
#include <vector>

namespace dvk {

    class Framebuffers {
    private:
        std::vector<VkFramebuffer> swapchainFramebuffers;
        VkDevice* device;
        std::vector<VkImageView>* swapChainImageViews;
        VkRenderPass* renderPass;
        VkExtent2D* swapchainExtent;

        void createFramebuffers();
    public:
        Framebuffers(VkDevice *device, std::vector<VkImageView>* swapChainImageViews, VkRenderPass* renderPass, VkExtent2D* swapchainExtent);
        ~Framebuffers();

        std::vector<VkFramebuffer>* getFramebuffers();
    };

} // dvk

#endif //DRAFT_VK_FRAMEBUFFERS_HPP
