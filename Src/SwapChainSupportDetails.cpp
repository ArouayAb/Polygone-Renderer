#include "SwapChainSupportDetails.hpp"

void SwapChainSupportDetails::querySwapChainSupportDetails(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	//SurfaceCapabilities
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &this->capabilities);

	//SurfaceFormats
	uint32_t formatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount != 0)
	{
		this->formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, this->formats.data());
	}

	//PresentationModes
	uint32_t presentModeCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0)
	{
		this->presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, this->presentModes.data());
	}
}