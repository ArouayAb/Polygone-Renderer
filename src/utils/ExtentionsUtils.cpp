//
// Created by Arouay on 30/03/2023.
//

#include "ExtentionsUtils.hpp"
#include "Constants.hpp"

namespace dvk::extensions_utils {
    std::vector<const char*> deviceExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    std::vector<const char*> getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount); // (first, last)

        if (constants::enable_Validation_Layers)
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        return extensions;
    }

    void checkExtensionsCompatibility(std::vector<const char*>& glfwExtensions, std::vector<VkExtensionProperties>& vkCompatibleExtensions)
    {
        std::vector<std::string> vkCompatibleExtensionName;
        for (auto& ie : vkCompatibleExtensions)
        {
            std::string bufferName(ie.extensionName);
            vkCompatibleExtensionName.push_back(bufferName);
        }

        for (auto& ie : glfwExtensions)
        {
            if (vkCompatibleExtensionName.end() == std::find(vkCompatibleExtensionName.begin(), vkCompatibleExtensionName.end(), ie))
            {
                std::string extensionName(ie);
                throw std::runtime_error("\nMissing Vulkan extension: " + extensionName);
            }
        }
    }

    bool checkDeviceExensionsSupport(VkPhysicalDevice device)
    {
        uint32_t availableDeviceExtensionsCount = 0;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &availableDeviceExtensionsCount, nullptr);

        std::vector<VkExtensionProperties> availableDeviceExtensions(availableDeviceExtensionsCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &availableDeviceExtensionsCount, availableDeviceExtensions.data());

        std::set<std::string> requiredExtensions( deviceExtensions.begin(), deviceExtensions.end() );
        for (const auto& extension : availableDeviceExtensions)
        {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }
}