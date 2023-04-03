#ifndef CORE
#define CORE

#ifdef NDEBUG
const bool enable_Validation_Layers = false;
#else
const bool enable_Validation_Layers = true;
#endif

#include "vulkan/vulkan.h"

#include <GLFW/glfw3.h>
#include "QueueFamilyIndices.hpp"
#include "SwapchainSupportDetails.hpp"
#include "_QueueFamilyIndices.hpp"
#include <vector>
#include <set>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <cstring>

namespace dvk {

    class _Core
    {
    public:
        void run();
        _Core();

    private:
        GLFWwindow* window;
        const uint32_t HEIGHT = 600;
        const uint32_t WIDTH = 800;

        const int MAX_FRAMES_IN_FLIGHT = 2;

        std::vector<const char*> deviceExtensions;
        std::vector<const char*> validationLayers;
        VkDebugUtilsMessengerEXT debugMessenger;

        VkInstance instance;

        VkQueue graphicsQueue;

        VkQueue presentationQueue;

        VkPhysicalDevice physicalDevice;

        VkDevice device;

        VkSurfaceKHR surface;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        VkRenderPass renderPass{};
        VkPipelineLayout pipelineLayout{};
        VkPipeline graphicsPipeline{};

        std::vector<VkFramebuffer> swapchainFramebuffers;

        VkCommandPool commandPool{};
        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        int currentFrame = 0;

        bool checkValidationLayerSupport();
        static VkBool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData);
        void fillDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        VkResult createDebugUtilsMessengerEXT(
                VkInstance instance,
                const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                const VkAllocationCallbacks* pAllocator,
                VkDebugUtilsMessengerEXT* pDebugMessenger);
        void destroyDebugUtilsMessengerEXT(
                VkInstance instance,
                VkDebugUtilsMessengerEXT debugMessenger,
                const VkAllocationCallbacks* pAllocator);
        void setupDebugMessenger();

        std::vector<const char*> getRequiredExtensions();
        void checkExtensionsCompatibility(std::vector<const char*>& glfwExtensions, std::vector<VkExtensionProperties>& vkCompatibleExtensions);

        bool checkDeviceExensionsSupport(VkPhysicalDevice device);

        void createInstance();

        void createSurface();

        deprecated::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        bool isDeviceSuitable(VkPhysicalDevice device);

        void pickPhysicalDevice();

        void createLogicalDevice();

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormat);
        VkPresentModeKHR chooseSwapPresentMode(std::vector<VkPresentModeKHR> availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        void createSwapChain();

        void createImageViews();

        static std::vector<char> readFile(const std::string& fileName);

        VkShaderModule createShaderModule(const std::vector<char>& code);

        void createRenderPass();

        void createGraphicsPipeline();

        void createFramebuffers();

        void createCommandPool();
        void createCommandBuffers();

        void createSyncObjects();

        void drawFrame();

        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();
    };
}

#endif