//
// Created by Arouay on 31/03/2023.
//

#include "Device.hpp"

namespace dvk {
    Device::Device(VkInstance* instance, VkSurfaceKHR* surface) :
        instance(instance),
        surface(surface)
    {
        pickPhysicalDevice();
        createLogicalDevice();
    }

    Device::~Device() {
        vkDestroyDevice(device, nullptr);
    }

    bool Device::isDeviceSuitable(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices(&device, surface);
        bool deviceExtensionsSupported = extensions_utils::checkDeviceExensionsSupport(device);

        bool swapChainAdequate = false;
        if (deviceExtensionsSupported)
        {
            SwapChainSupportDetails	swapChainSupport;
            swapChainSupport.querySwapChainSupportDetails(device, *surface);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return indices.isComplete() && deviceExtensionsSupported && swapChainAdequate;
    }

    void Device::pickPhysicalDevice()
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(*instance, &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            throw std::runtime_error("No vulkan compatible GPU found!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(*instance, &deviceCount, devices.data());

        for (const auto& device : devices)
        {
            if (isDeviceSuitable(device))
            {
                physicalDevice = device;
//			break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE)
        {
            throw std::runtime_error("Unable to find suitable GPU!");
        }
    }

    void Device::createLogicalDevice()
    {
        QueueFamilyIndices indices(&physicalDevice, surface);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.getGraphicsFamilyValue(), indices.getPresentationFamilyValue() };

        float queuePriority = 1.0f;
        for (uint32_t familyQueue : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = familyQueue;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions_utils::deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = extensions_utils::deviceExtensions.data();

        if (constants::enable_Validation_Layers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(Debug::getValidationLayers().size());
            createInfo.ppEnabledLayerNames = Debug::getValidationLayers().data();
        }
        else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create logical device!");
        }

        vkGetDeviceQueue(device, indices.getGraphicsFamilyValue(), 0, &graphicsQueue);
        vkGetDeviceQueue(device, indices.getPresentationFamilyValue(), 0, &presentationQueue);
    }
} // dvk