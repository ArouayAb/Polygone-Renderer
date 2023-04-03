//
// Created by Arouay on 02/04/2023.
//

#include "Swapchain.hpp"
#include "SwapchainSupportDetails.hpp"
#include "QueueFamilyIndices.hpp"

namespace dvk {

    dvk::Swapchain::Swapchain(GLFWwindow* window, VkSurfaceKHR* surface, VkPhysicalDevice* physicalDevice, VkDevice* device) :
        window(window),
        surface(surface),
        physicalDevice(physicalDevice),
        device(device)
    {
        createSwapChain();
    }

    dvk::Swapchain::~Swapchain() {
        vkDestroySwapchainKHR(*device, swapChain, nullptr);
    }

    VkSurfaceFormatKHR Swapchain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for (const auto& availableFormat : availableFormats)
        {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }
    VkPresentModeKHR Swapchain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
    {
        for (const auto& availablePresentMode : availablePresentModes)
        {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }
    VkExtent2D Swapchain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
    {
        if (capabilities.currentExtent.width != UINT32_MAX)
        {
            return capabilities.currentExtent;
        }
        else {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            VkExtent2D actualExtent = {
                    static_cast<uint32_t>(width),
                    static_cast<uint32_t>(height)
            };

            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

            return actualExtent;
        }
    }

    void Swapchain::createSwapChain()
    {
        SwapchainSupportDetails swapChainSupport;
        swapChainSupport.querySwapChainSupportDetails(*physicalDevice, *surface);

        VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
        {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = *surface;
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.presentMode = presentMode;
        createInfo.imageExtent = extent;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices(physicalDevice, surface);
        uint32_t queueFamilyIndices[] = {indices.getGraphicsFamilyValue(), indices.getPresentationFamilyValue()};

        if (indices.getGraphicsFamilyValue() != indices.getPresentationFamilyValue())
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;
            createInfo.pQueueFamilyIndices = nullptr;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(*device, &createInfo, nullptr, &swapChain) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to	create swapchain!");
        }

        vkGetSwapchainImagesKHR(*device, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(*device, swapChain, &imageCount, swapChainImages.data());
    }

    std::vector<VkImage> *Swapchain::getSwapchainImages() {
        return &swapChainImages;
    }

    VkFormat *Swapchain::getSwapchainImageFormat() {
        return &swapChainImageFormat;
    }

    VkExtent2D *Swapchain::getSwapchainExtent() {
        return &swapChainExtent;
    }

    VkSwapchainKHR* Swapchain::getSwapChain() {
        return &swapChain;
    }
}