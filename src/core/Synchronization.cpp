//
// Created by Arouay on 02/04/2023.
//

#include <vulkan/vulkan_core.h>
#include <stdexcept>
#include "Synchronization.hpp"

namespace dvk {
    Synchronization::Synchronization(VkDevice* device, std::vector<VkImage>* swapchainImages, VkQueue* graphicsQueue, const int MAX_FRAMES_IN_FLIGHT) :
        device(device),
        swapchainImages(swapchainImages),
        graphicsQueue(graphicsQueue),
        MAX_FRAMES_IN_FLIGHT(MAX_FRAMES_IN_FLIGHT)
    {
        createSyncObjects();
    }

    Synchronization::~Synchronization() {
        vkQueueWaitIdle(*graphicsQueue);
        for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
        {
            vkDestroySemaphore(*device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(*device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(*device, inFlightFences[i], nullptr);
        }
    }

    void Synchronization::createSyncObjects()
    {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
        imagesInFlight.resize(swapchainImages->size(), VK_NULL_HANDLE); //?

        VkSemaphoreCreateInfo semaphoreInfos{};
        semaphoreInfos.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfos{};
        fenceInfos.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfos.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
        {
            if (vkCreateSemaphore(*device, &semaphoreInfos, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(*device, &semaphoreInfos, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS	||
                vkCreateFence(*device, &fenceInfos, nullptr, &inFlightFences[i]) != VK_SUCCESS){
                throw std::runtime_error("Failed to create syncronization objects for a frame!");
            }
        }
    }

    std::vector<VkSemaphore>* Synchronization::getImageAvailableSemaphores() {
        return &imageAvailableSemaphores;
    }

    std::vector<VkSemaphore>* Synchronization::getRenderFinishedSemaphores() {
        return &renderFinishedSemaphores;
    }

    std::vector<VkFence>* Synchronization::getInFlightFences() {
        return &inFlightFences;
    }

    std::vector<VkFence>* Synchronization::getImagesInFlight() {
        return &imagesInFlight;
    }
} // dvk