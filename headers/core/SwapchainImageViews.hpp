//
// Created by Arouay on 02/04/2023.
//

#ifndef DRAFT_VK_SWAPCHAINIMAGEVIEWS_HPP
#define DRAFT_VK_SWAPCHAINIMAGEVIEWS_HPP

#include <vulkan/vulkan_core.h>
#include <vector>

namespace dvk {

    class SwapchainImageViews {
    private:
        std::vector<VkImageView> swapChainImageViews;
        VkDevice* device;
        std::vector<VkImage>* swapChainImages;
        VkFormat* swapChainImageFormat;

        void createImageViews();
    public:
        SwapchainImageViews(VkDevice* device, std::vector<VkImage>* swapChainImages, VkFormat* swapChainImageFormat);
        ~SwapchainImageViews();

        std::vector<VkImageView>* getSwapchainImageViews();
    };

} // dvk

#endif //DRAFT_VK_SWAPCHAINIMAGEVIEWS_HPP
