//
// Created by Arouay on 30/03/2023.
//

#include <vector>
#include <sstream>
#include "Window.hpp"

namespace dvk {

    GLFWwindow* Window::getRawWindow() {
        return this->window.get();
    }

    Window::Window() : HEIGHT(1080), WIDTH(1920), framebufferResized(false) {
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

    void Window::showStats() {
        // Measure speed
        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;
        nbFrames++;
        if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
//            cout << 1000.0/double(nbFrames) << endl;

            double fps = double(nbFrames) / delta;

            std::stringstream ss;
            ss  << " [" << (1/fps) * 1000 << " ms" << " - " <<  fps << " FPS]";

            glfwSetWindowTitle(window.get(), ss.str().c_str());

            nbFrames = 0;
            lastTime = currentTime;
        }
    }
} // dvk