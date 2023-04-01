#include "QueueFamilyIndices.hpp"

namespace dvk {
    bool QueueFamilyIndices::isComplete() const
    {
        return graphicsFamily.has_value() && presentationFamily.has_value();
    }

    void QueueFamilyIndices::findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
    {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        VkBool32 presentationSupport = false;
        int index = 0;
        for (const auto& queueFamily : queueFamilies)
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                graphicsFamily = index;
            }

            vkGetPhysicalDeviceSurfaceSupportKHR(device, index, surface, &presentationSupport);
            if (presentationSupport)
            {
                presentationFamily = index;
            }

            if (isComplete())
            {
                break;
            }

            index++;
        }
    }

    QueueFamilyIndices::QueueFamilyIndices(VkPhysicalDevice* device, VkSurfaceKHR* surface) {
        findQueueFamilies(*device, *surface);
    }

    uint32_t QueueFamilyIndices::getGraphicsFamilyValue() {
        return graphicsFamily.value();
    }

    uint32_t QueueFamilyIndices::getPresentationFamilyValue() {
        return presentationFamily.value();
    }
}