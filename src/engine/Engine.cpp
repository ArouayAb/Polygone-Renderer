//
// Created by Arouay on 29/03/2023.
//

#include "Engine.hpp"

namespace dvk {

    void Engine::init() {

    }

    Engine::Engine() :
        debug(instance.getInstance()),
        surface(window.getRawWindow(), instance.getInstance()),
        device(instance.getInstance(), surface.getSurface()),
        swapchain(
                window.getRawWindow(),
                surface.getSurface(),
                device.getPhysicalDevice(),
                device.getDevice()
                ),
        swapchainImageViews(
                device.getDevice(),
                swapchain.getSwapchainImages(),
                swapchain.getSwapchainImageFormat()
                ),
        renderPass(device.getDevice(), swapchain.getSwapchainImageFormat()),
        graphicsPipeline(
                device.getDevice(),
                renderPass.getRenderPass(),
                swapchain.getSwapchainExtent()
                ),
        framebuffers(
                device.getDevice(),
                swapchainImageViews.getSwapchainImageViews(),
                renderPass.getRenderPass(),
                swapchain.getSwapchainExtent()
                ),
        commandBuffers(
                device.getPhysicalDevice(),
                device.getDevice(),
                surface.getSurface(),
                framebuffers.getFramebuffers(),
                renderPass.getRenderPass(),
                swapchain.getSwapchainExtent(),
                graphicsPipeline.getGraphicsPipeline()
                ),
        synchronization(
                device.getDevice(),
                swapchain.getSwapchainImages(),
                device.getGraphicsQueue()
                )
    {
        init();
    }

    void Engine::run() {
        this->window.startLoop([](){
            std::cout << "frame draw" << std::endl;
//            drawFrame();
        });
    }
}
