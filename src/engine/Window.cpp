//
// Created by Arouay on 30/03/2023.
//

#include <vector>
#include "Window.hpp"

namespace dvk {

    std::shared_ptr<GLFWwindow> Window::getRawWindow() const {
        return window;
    }

    Window::Window() : HEIGHT(600), WIDTH(800) {
        glfwInit();
        createWindow(
                std::vector<WindowHint>{
                        WindowHint{GLFW_CLIENT_API, GLFW_NO_API},
                        WindowHint{GLFW_RESIZABLE, GLFW_FALSE}
                });
    }

    void Window::createWindow(const std::vector<WindowHint>& windowHints) {
        for (const auto &item: windowHints) {
            glfwWindowHint(item.hint, item.value);
        }

        std::unique_ptr<GLFWwindow, DestroyGLFWwindow> adaptedWindowHandle(
                glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr)
        );

        window = std::move(adaptedWindowHandle);
    }

    Window::~Window() {
        glfwDestroyWindow(this->window.get());
        glfwTerminate();
    }
} // dvk