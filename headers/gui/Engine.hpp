//
// Created by Arouay on 29/03/2023.
//

#ifndef VK_DRAFT_MAINVIEW_H
#define VK_DRAFT_MAINVIEW_H


#include <GLFW/glfw3.h>
#include <memory>

namespace dvk {
    class Engine {
    private:
        struct DestroyGLFWwindow {
            void operator()(GLFWwindow* ptr){
                glfwDestroyWindow(ptr);
            }
        };

        const uint32_t HEIGHT;
        const uint32_t WIDTH;
        std::unique_ptr<GLFWwindow, DestroyGLFWwindow> window;

        void init();
    public:
        Engine();

        Engine(const uint32_t height, const uint32_t width);

        [[nodiscard]] GLFWwindow& getWindow() const;

        void setWindow(std::unique_ptr<GLFWwindow, DestroyGLFWwindow> window);

        void run();
    };
}


#endif //VK_DRAFT_MAINVIEW_H
