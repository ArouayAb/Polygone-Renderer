//
// Created by Arouay on 30/03/2023.
//

#include "Debug.hpp"
#include "Constants.hpp"

namespace dvk {

    std::vector<const char*> Debug::validationLayers = {};

    bool Debug::checkValidationLayerSupport()
    {
        uint32_t ValidationLayersCount = 0;
        vkEnumerateInstanceLayerProperties(&ValidationLayersCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(ValidationLayersCount);
        vkEnumerateInstanceLayerProperties(&ValidationLayersCount, availableLayers.data());

        uint32_t layerFoundCount = 0;
        for (auto& iv : validationLayers)
        {
            bool layerFound = false;

            for (auto& iav : availableLayers)
            {
                if (std::strcmp(iv, iav.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (layerFound)
            {
                layerFoundCount++;
            }
        }

        if (layerFoundCount == validationLayers.size())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    VkBool32 VKAPI_CALL Debug::debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData)
    {
        if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
        {
            std::cerr << "\nValidation Layer: " << pCallbackData->pMessage << std::endl;
        }
        return VK_FALSE;
    }

    void Debug::fillDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
    {
        if (!constants::enable_Validation_Layers) return;

        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                                     | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                                 | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;
    }

    VkResult Debug::createDebugUtilsMessengerEXT(VkInstance* instance)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(*instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(*instance, &createInfo, nullptr, &debugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void Debug::destroyDebugUtilsMessengerEXT(VkInstance* instance)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(*instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(*instance, debugMessenger, nullptr);
        }
    }

    void Debug::setupDebugMessenger()
    {
        fillDebugUtilsMessengerCreateInfo(createInfo);

        if (createDebugUtilsMessengerEXT(instance) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create debug messenger.");
        };
    }

    Debug::Debug(VkInstance* instance) : instance(instance){

        if (constants::enable_Validation_Layers && !checkValidationLayerSupport())
        {
            throw std::runtime_error("\nValidation layer requested but not available.");
        }

        setupDebugMessenger();
    }

    Debug::~Debug() {
        destroyDebugUtilsMessengerEXT(instance);
    }

    const std::vector<const char *> &Debug::getValidationLayers() {
        return validationLayers;
    }

} // dvk