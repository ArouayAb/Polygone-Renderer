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
        std::unique_ptr<Window> window;
        std::unique_ptr<Instance> instance;
        std::unique_ptr<Surface> surface;
        std::unique_ptr<Debug> debug;
        std::unique_ptr<Device> device;
        std::unique_ptr<Swapchain> swapchain;
        std::unique_ptr<SwapchainImageViews> swapchainImageViews;
        std::unique_ptr<RenderPass> renderPass;
        std::unique_ptr<GraphicsPipeline> graphicsPipeline;
        std::unique_ptr<Framebuffers> framebuffers;
        std::unique_ptr<CommandBuffers> commandBuffers;
        std::unique_ptr<Synchronization> synchronization;

        void recreateSwapchain();
        void init();
    public:
        Core();

        void drawFrame();
        void start();
    };

} // dvk

#endif //DRAFT_VK_CORE_HPP
