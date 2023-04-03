//
// Created by Arouay on 03/04/2023.
//

#include "Core.hpp"

namespace dvk::Core {
    Core::Core() :
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
                    device.getGraphicsQueue(),
                    MAX_FRAMES_IN_FLIGHT
            )
    {

    }

    void Core::drawFrame()
    {
        vkWaitForFences(*(device.getDevice()), 1, &(*(synchronization.getInFlightFences()))[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        vkAcquireNextImageKHR(*(device.getDevice()), *(swapchain.getSwapChain()), UINT64_MAX, (*(synchronization.getImageAvailableSemaphores()))[currentFrame], VK_NULL_HANDLE, &imageIndex);

        if ((*(synchronization.getImagesInFlight()))[imageIndex] != VK_NULL_HANDLE){
            vkWaitForFences(*(device.getDevice()), 1, &(*(synchronization.getImagesInFlight()))[imageIndex], VK_TRUE, UINT64_MAX);
        }
        (*(synchronization.getImagesInFlight()))[imageIndex] = (*(synchronization.getInFlightFences()))[currentFrame];

        VkSemaphore waitSemaphores[] = {(*(synchronization.getImageAvailableSemaphores()))[currentFrame]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        VkSemaphore signalSemaphore[] = {(*(synchronization.getRenderFinishedSemaphores()))[currentFrame]};

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &(*(commandBuffers.getCommandBuffer()))[imageIndex];
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphore;

        vkResetFences(*(device.getDevice()), 1, &(*(synchronization.getInFlightFences()))[currentFrame]);

        if (vkQueueSubmit(*(device.getGraphicsQueue()), 1, &submitInfo, (*(synchronization.getInFlightFences()))[currentFrame]) != VK_SUCCESS){
            throw std::runtime_error("Failed to submit graphics queue!");
        }

        VkSwapchainKHR swapChains[] = {*(swapchain.getSwapChain())};
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.pWaitSemaphores = signalSemaphore;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageIndex;
        presentInfo.pResults = nullptr;
        presentInfo.waitSemaphoreCount = 1;

        vkQueuePresentKHR(*(device.getPresentationQueue()), &presentInfo);
        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void Core::init() {

    }

    void Core::start() {
        this->window.startLoop([this](){
            std::cout << "frame draw" << std::endl;
            this->drawFrame();
        });
    }

} // dvk