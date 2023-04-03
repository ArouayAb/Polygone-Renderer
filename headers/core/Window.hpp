//
// Created by Arouay on 30/03/2023.
//

#ifndef DRAFT_VK_WINDOW_HPP
#define DRAFT_VK_WINDOW_HPP

#include <memory>
#include <GLFW/glfw3.h>
#include <vector>

namespace dvk {

    struct WindowHint {
        int hint;
        int value;
    };

    class Window {
    private:
        struct DestroyGLFWwindow {
            void operator()(GLFWwindow* ptr){
                glfwDestroyWindow(ptr);
            }
        };
        const uint32_t HEIGHT;
        const uint32_t WIDTH;
        bool framebufferResized;
        std::unique_ptr<GLFWwindow, DestroyGLFWwindow> window;

        void createWindow(const std::vector<WindowHint>& windowHints);
    public:
        Window();
        ~Window();

        [[nodiscard]]
        GLFWwindow* getRawWindow();
        [[nodiscard]]
        bool isFramebufferResized() const;
        void setFramebufferResized(bool framebufferResized);
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        template<typename Lambda>
        void startLoop(Lambda&& cb) {
            while (!glfwWindowShouldClose(this->window.get()))
            {
                glfwPollEvents();
                cb();
            }
        }
    };

} // dvk

#endif //DRAFT_VK_WINDOW_HPP
