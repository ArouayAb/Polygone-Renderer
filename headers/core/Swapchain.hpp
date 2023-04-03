//
// Created by Arouay on 02/04/2023.
//

#ifndef DRAFT_VK_SWAPCHAIN_HPP
#define DRAFT_VK_SWAPCHAIN_HPP

#include <vulkan/vulkan_core.h>
#include <vector>
#include <GLFW/glfw3.h>

namespace dvk {

    class Swapchain {
    private:
        VkSwapchainKHR swapChain{};
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat{};
        VkExtent2D swapChainExtent{};
        GLFWwindow* window;
        VkSurfaceKHR* surface;
        VkPhysicalDevice* physicalDevice;
        VkDevice* device;

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(std::vector<VkPresentModeKHR> availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void createSwapChain();
    public:
        Swapchain(GLFWwindow* window, VkSurfaceKHR* surface, VkPhysicalDevice* physicalDevice, VkDevice* device);
        ~Swapchain();

        std::vector<VkImage>* getSwapchainImages();
        VkFormat* getSwapchainImageFormat();
        VkExtent2D* getSwapchainExtent();

        VkSwapchainKHR* getSwapChain();
    };

}

#endif //DRAFT_VK_SWAPCHAIN_HPP
