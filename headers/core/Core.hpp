//
// Created by Arouay on 03/04/2023.
//

#ifndef DRAFT_VK_CORE_HPP
#define DRAFT_VK_CORE_HPP

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

namespace dvk::Core {

    class Core {
    private:
        int currentFrame = 0;
        const int MAX_FRAMES_IN_FLIGHT = 2;
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
        Core();

        void drawFrame();
        void start();
    };

} // dvk

#endif //DRAFT_VK_CORE_HPP
