//
// Created by Arouay on 30/03/2023.
//

#include <vector>
#include "Window.hpp"

namespace dvk {

    GLFWwindow* Window::getRawWindow() {
        return this->window.get();
    }

    Window::Window() : HEIGHT(600), WIDTH(800), framebufferResized(false) {
        glfwInit();
        createWindow(
                std::vector<WindowHint>{
                        WindowHint{GLFW_CLIENT_API, GLFW_NO_API},
                        WindowHint{GLFW_RESIZABLE, GLFW_TRUE}
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

        glfwSetWindowUserPointer(window.get(), this);
        glfwSetFramebufferSizeCallback(window.get(), framebufferResizeCallback);
    }

    Window::~Window() {
        glfwDestroyWindow(getRawWindow());
        glfwTerminate();
    }

    bool Window::isFramebufferResized() const {
        return framebufferResized;
    }

    void Window::setFramebufferResized(bool framebufferResized) {
        Window::framebufferResized = framebufferResized;
    }

    void Window::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
        auto windowInstance = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        windowInstance->framebufferResized = true;
    }
} // dvk