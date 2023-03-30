//
// Created by Arouay on 30/03/2023.
//

#ifndef DRAFT_VK_EXTENTIONSUTILS_HPP
#define DRAFT_VK_EXTENTIONSUTILS_HPP


#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <set>
#include <GLFW/glfw3.h>

namespace dvk::extensions_utils {
    std::vector<const char*> getRequiredExtensions();
    void checkExtensionsCompatibility(
            std::vector<const char*>& glfwExtensions,
            std::vector<VkExtensionProperties>& vkCompatibleExtensions
    );

    bool checkDeviceExensionsSupport(VkPhysicalDevice device);
}


#endif //DRAFT_VK_EXTENTIONSUTILS_HPP
