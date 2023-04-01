//
// Created by Arouay on 31/03/2023.
//

#ifndef DRAFT_VK_DEVICE_HPP
#define DRAFT_VK_DEVICE_HPP

#include <vulkan/vulkan_core.h>
#include <vector>
#include <stdexcept>
#include "Debug.hpp"
#include "QueueFamilyIndices.hpp"
#include "SwapChainSupportDetails.hpp"
#include "ExtentionsUtils.hpp"
#include "Constants.hpp"

namespace dvk {

    class Device {
    private:
        VkInstance* instance;
        VkSurfaceKHR* surface;
        VkPhysicalDevice physicalDevice{};
        VkDevice device{};
        VkQueue graphicsQueue{};
        VkQueue presentationQueue{};

        bool isDeviceSuitable(VkPhysicalDevice device);
        void pickPhysicalDevice();
        void createLogicalDevice();
    public:
        explicit Device(VkInstance* instance, VkSurfaceKHR* surface);
        ~Device();


    };

} // dvk

#endif //DRAFT_VK_DEVICE_HPP
