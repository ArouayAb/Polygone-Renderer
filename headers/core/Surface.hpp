//
// Created by Arouay on 31/03/2023.
//

#ifndef DRAFT_VK_SURFACE_HPP
#define DRAFT_VK_SURFACE_HPP

#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

namespace dvk {

    class Surface {
    private:
        GLFWwindow* window;
        VkInstance* instance;
        VkSurfaceKHR surface{};
    public:
        Surface(GLFWwindow* window, VkInstance* instance);
        ~Surface();

        VkSurfaceKHR* getSurface();
    };

} // dvk

#endif //DRAFT_VK_SURFACE_HPP
