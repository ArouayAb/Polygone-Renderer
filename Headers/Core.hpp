#ifndef CORE
#define CORE

#ifdef NDEBUG
const bool enable_Validation_Layers = false;
#else
const bool enable_Validation_Layers = true;
#endif

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include "QueueFamilyIndices.hpp"
#include "SwapChainSupportDetails.hpp"
#include <vector>
#include <set>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <cstring>

class Core
{
public:
	void run();
	Core();

private:
	GLFWwindow* window;
	const uint32_t HEIGHT = 600;
	const uint32_t WIDTH = 800;

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

	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	std::vector<VkFramebuffer> swapchainFramebuffers;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;

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

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);

	void pickPhysicalDevice();

	void createLogicalDevice();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormat);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
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

	void createSemaphores();

	void drawFrame();

	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();
};

#endif