//
// Created by Arouay on 02/04/2023.
//

#ifndef DRAFT_VK_SYNCHRONIZATION_HPP
#define DRAFT_VK_SYNCHRONIZATION_HPP

#include <vector>
#include <vulkan/vulkan_core.h>

namespace dvk {

    class Synchronization {
    private:
        const int MAX_FRAMES_IN_FLIGHT;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        VkDevice* device;
        std::vector<VkImage>* swapchainImages;
        VkQueue* graphicsQueue;

        void createSyncObjects();
    public:
        Synchronization(VkDevice* device, std::vector<VkImage>* swapchainImages, VkQueue* graphicsQueue, int MAX_FRAMES_IN_FLIGHT);
        ~Synchronization();

        std::vector<VkSemaphore>* getImageAvailableSemaphores();
        std::vector<VkSemaphore>* getRenderFinishedSemaphores();
        std::vector<VkFence>* getInFlightFences();
        std::vector<VkFence>* getImagesInFlight();
    };

} // dvk

#endif //DRAFT_VK_SYNCHRONIZATION_HPP
