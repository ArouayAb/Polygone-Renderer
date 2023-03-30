//
// Created by Arouay on 29/03/2023.
//

#ifndef VK_DRAFT_MAINVIEW_H
#define VK_DRAFT_MAINVIEW_H


#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include "Window.hpp"
#include "Instance.hpp"

namespace dvk {
    class Engine {
    private:
        Window window;
        Instance instance;
        Debug debug;

        void init();
    public:
        Engine();

        void run();
    };
}


#endif //VK_DRAFT_MAINVIEW_H
