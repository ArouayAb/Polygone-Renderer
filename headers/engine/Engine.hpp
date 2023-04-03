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
#include "Surface.hpp"
#include "Device.hpp"
#include "Swapchain.hpp"
#include "SwapchainImageViews.hpp"
#include "RenderPass.hpp"
#include "GraphicsPipeline.hpp"
#include "Framebuffers.hpp"
#include "CommandBuffers.hpp"
#include "Synchronization.hpp"

namespace dvk {
    class Engine {
    private:
        Window window;
        Instance instance;
        Surface surface;
        Debug debug;
        Device device;
        Swapchain swapchain;
        SwapchainImageViews swapchainImageViews;
        RenderPass renderPass;
        GraphicsPipeline graphicsPipeline;
        Framebuffers framebuffers;
        CommandBuffers commandBuffers;
        Synchronization synchronization;

        void init();
    public:
        Engine();

        void run();
    };
}


#endif //VK_DRAFT_MAINVIEW_H
