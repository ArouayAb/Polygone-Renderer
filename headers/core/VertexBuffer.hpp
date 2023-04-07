//
// Created by Arouay on 04/04/2023.
//

#ifndef DRAFT_VK_VERTEXBUFFER_HPP
#define DRAFT_VK_VERTEXBUFFER_HPP

#include <vulkan/vulkan.h>
#include "Vertex.hpp"

namespace dvk {

    class VertexBuffer {
    private:
        VkDevice* device;
        VkPhysicalDevice* physicalDevice;
        VkQueue* graphicsQueue;
        VkSurfaceKHR* surface;
        VkBuffer stagingBuffer{};
        VkDeviceMemory stagingBufferMemory{};
        VkBuffer vertexBuffer{};
        VkDeviceMemory vertexBufferMemory{};
        VkBufferCreateInfo bufferInfo{};
        std::vector<Vertex> vertices{};

        void createVertexBuffer();
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        void allocateMemory();
        void fillMemory(VkDeviceSize size);
        void createBuffer(
                VkDeviceSize bufferSize,
                VkBufferUsageFlags bufferUsageFlags,
                VkBuffer& buffer,
                VkMemoryPropertyFlags memoryProperties,
                VkDeviceMemory& bufferMemory
                );
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    public:
        VertexBuffer(VkDevice* device, VkPhysicalDevice* physicalDevice, VkQueue* graphicsQueue, VkSurfaceKHR* surface);
        VertexBuffer(VkDevice* device, VkPhysicalDevice* physicalDevice, std::vector<Vertex> vertices, VkQueue* graphicsQueue, VkSurfaceKHR* surface);
        ~VertexBuffer();

        VkBuffer* getVertexBuffer();
        std::vector<Vertex>* getVertices();
    };

} // dvk

#endif //DRAFT_VK_VERTEXBUFFER_HPP
