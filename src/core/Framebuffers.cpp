//
// Created by Arouay on 02/04/2023.
//

#include <stdexcept>
#include "Framebuffers.hpp"

namespace dvk {
    Framebuffers::Framebuffers(VkDevice *device, std::vector<VkImageView>* swapChainImageViews, VkRenderPass* renderPass, VkExtent2D* swapchainExtent) :
        device(device),
        swapChainImageViews(swapChainImageViews),
        renderPass(renderPass),
        swapchainExtent(swapchainExtent)
    {
        createFramebuffers();
    }

    Framebuffers::~Framebuffers() {
        for(auto framebuffer : swapchainFramebuffers){
            vkDestroyFramebuffer(*device, framebuffer, nullptr);
        }
    }

    void Framebuffers::createFramebuffers()
    {
        swapchainFramebuffers.resize(swapChainImageViews->size());

        for(size_t i = 0; i < swapchainFramebuffers.size(); i++)
        {
            VkImageView attachments[] = {
                    (*swapChainImageViews)[i]
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = *renderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.layers = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.height = swapchainExtent->height;
            framebufferInfo.width = swapchainExtent->width;

            if (vkCreateFramebuffer(*device, &framebufferInfo, nullptr, &swapchainFramebuffers[i]) != VK_SUCCESS){
                throw std::runtime_error("Failed to create framebuffer!");
            }
        }
    }

    std::vector<VkFramebuffer> *Framebuffers::getFramebuffers() {
        return &swapchainFramebuffers;
    }

} // dvk