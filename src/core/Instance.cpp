//
// Created by Arouay on 30/03/2023.
//

#include <memory>
#include "Instance.hpp"
#include "Constants.hpp"
#include "ExtentionsUtils.hpp"

namespace dvk {
    Instance::Instance() {
        init();
    }

    Instance::~Instance() {
        vkDestroyInstance(instance, nullptr);
    }

    void Instance::init() {

        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "First Triangle!";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        std::vector<const char*> glfwExtensions = extensions_utils::getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(glfwExtensions.size());
        createInfo.ppEnabledExtensionNames = glfwExtensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (constants::enable_Validation_Layers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(Debug::getValidationLayers().size());
            createInfo.ppEnabledLayerNames = Debug::getValidationLayers().data();

            Debug::fillDebugUtilsMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = &debugCreateInfo;
        }
        else
        {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        Debug::checkValidationLayerSupport();
        extensions_utils::checkExtensionsCompatibility(glfwExtensions, extensions);

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create an instance!");
        }
    }

    VkInstance* Instance::getInstance() {
        return &instance;
    }
} // dvk