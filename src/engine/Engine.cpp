//
// Created by Arouay on 29/03/2023.
//

#include "Engine.hpp"

namespace dvk {
    GLFWwindow& Engine::getWindow() const {
        return *window;
    }

    void Engine::setWindow(std::unique_ptr<GLFWwindow, DestroyGLFWwindow> window) {
        Engine::window = std::move(window);
    }

    void Engine::init() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        std::unique_ptr<GLFWwindow, DestroyGLFWwindow> adaptedWindowHandle(
                glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr)
        );

        window = std::move(adaptedWindowHandle);
    }

    Engine::Engine(const uint32_t height, const uint32_t width) : HEIGHT(height), WIDTH(width) {
        init();
    }

    Engine::Engine() : HEIGHT(600), WIDTH(800) {
        init();
    }

    void Engine::run() {
        while (!glfwWindowShouldClose(window.get()))
        {
            glfwPollEvents();
//            drawFrame();
        }
    }
}
