//
// Created by Arouay on 31/03/2023.
//

#include <stdexcept>
#include "Surface.hpp"

namespace dvk {
    Surface::Surface(GLFWwindow* window, VkInstance* instance) : window(window), instance(instance) {
        if (glfwCreateWindowSurface(*this->instance, this->window, nullptr, &surface) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create surface!");
        }
    }

    Surface::~Surface() {
        vkDestroySurfaceKHR(*instance, surface, nullptr);
    }
} // dvk