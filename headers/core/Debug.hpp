//
// Created by Arouay on 30/03/2023.
//

#ifndef DRAFT_VK_DEBUG_HPP
#define DRAFT_VK_DEBUG_HPP

#include <vector>
#include <vulkan/vulkan_core.h>

namespace dvk {

    class Debug {
    private:
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        std::vector<const char*> validationLayers{};
        VkDebugUtilsMessengerEXT debugMessenger{};
        VkInstance* instance;

        static VkBool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData
                );
        VkResult createDebugUtilsMessengerEXT();
        void destroyDebugUtilsMessengerEXT();
    public:
        explicit Debug(VkInstance* instance);
        ~Debug();

        bool checkValidationLayerSupport();
        void setupDebugMessenger();
        static void fillDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        [[nodiscard]] const std::vector<const char *> &getValidationLayers() const;
    };

} // dvk

#endif //DRAFT_VK_DEBUG_HPP
