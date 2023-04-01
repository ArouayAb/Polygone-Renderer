#ifndef QUEUE_FAMILY_INDICES
#define QUEUE_FAMILY_INDICES

#include <optional>
#include <cstdint>
#include <vulkan/vulkan_core.h>
#include <vector>
#include "Device.hpp"

namespace dvk {

    class QueueFamilyIndices
    {
    private:
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentationFamily;

        void findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
    public:
        explicit QueueFamilyIndices(VkPhysicalDevice* device, VkSurfaceKHR* surface);

        [[nodiscard]]
        bool isComplete() const;

        uint32_t getGraphicsFamilyValue();
        uint32_t getPresentationFamilyValue();
    };
}

#endif