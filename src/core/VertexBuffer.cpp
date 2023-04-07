//
// Created by Arouay on 04/04/2023.
//

#include "VertexBuffer.hpp"
#include "QueueFamilyIndices.hpp"

#include <utility>

namespace dvk {
    VertexBuffer::VertexBuffer(VkDevice* device, VkPhysicalDevice* physicalDevice, VkQueue* graphicsQueue, VkSurfaceKHR* surface) :
        device(device),
        physicalDevice(physicalDevice),
        graphicsQueue(graphicsQueue),
        surface(surface)
    {
        vertices = {
                {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},
                {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
                {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
                {{-0.5f, 0.5}, {0.0f, 0.0f, 1.0f}}
        };
        createVertexBuffer();
    }

    VertexBuffer::VertexBuffer(VkDevice* device, VkPhysicalDevice* physicalDevice, std::vector<Vertex> vertices, VkQueue* graphicsQueue, VkSurfaceKHR* surface) :
        device(device),
        physicalDevice(physicalDevice),
        vertices(std::move(vertices)),
        graphicsQueue(graphicsQueue),
        surface(surface)
    {
        createVertexBuffer();
    }

    VertexBuffer::~VertexBuffer() {
        vkDestroyBuffer(*device, vertexBuffer, nullptr);
        vkFreeMemory(*device, vertexBufferMemory, nullptr);
    }

    void VertexBuffer::createBuffer(
            VkDeviceSize bufferSize,
            VkBufferUsageFlags bufferUsageFlags,
            VkBuffer& buffer,
            VkMemoryPropertyFlags memoryProperties,
            VkDeviceMemory& bufferMemory
            ) {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = bufferSize;
        bufferInfo.usage = bufferUsageFlags;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(*device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create vertex buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(*device, buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(
                memRequirements.memoryTypeBits,
                memoryProperties
        );

        if (vkAllocateMemory(*device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate vertex buffer memory!");
        }

        vkBindBufferMemory(*device, buffer, bufferMemory, 0);
    }

    void VertexBuffer::createVertexBuffer() {
        VkDeviceSize bufferSize = sizeof(Vertex) * this->vertices.size();
        createBuffer(
                bufferSize,
                VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                stagingBuffer,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                stagingBufferMemory
        );
        fillMemory(bufferSize);
        createBuffer(
                bufferSize,
                VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                vertexBuffer,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                vertexBufferMemory
        );
        copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

        // TODO: potential memory leak, should make Buffer class into RAII
        vkDestroyBuffer(*device, stagingBuffer, nullptr);
        vkFreeMemory(*device, stagingBufferMemory, nullptr);
    }

    void VertexBuffer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
        QueueFamilyIndices queueFamilyIndices(physicalDevice, surface);

        VkCommandPoolCreateInfo commandPoolInfos{};
        commandPoolInfos.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        commandPoolInfos.queueFamilyIndex = queueFamilyIndices.getGraphicsFamilyValue();
        commandPoolInfos.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

        VkCommandPool commandPool{};
        if (vkCreateCommandPool(*device, &commandPoolInfos, nullptr, &commandPool) != VK_SUCCESS){
            throw std::runtime_error("Failed to create command pool!");
        }

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(*device, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        VkBufferCopy copyRegion{};
        copyRegion.srcOffset = 0;
        copyRegion.dstOffset = 0;
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(*graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(*graphicsQueue);

        // TODO: Potential memory leak, turn CommandBuffer class into a generic RAII class
        vkDestroyCommandPool(*device, commandPool, nullptr);
    }

    uint32_t VertexBuffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(*physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

    void VertexBuffer::allocateMemory() {
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(*device, vertexBuffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(
                memRequirements.memoryTypeBits,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
                );

        if (vkAllocateMemory(*device, &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate vertex buffer memory!");
        }

        vkBindBufferMemory(*device, vertexBuffer, vertexBufferMemory, 0);
    }

    void VertexBuffer::fillMemory(VkDeviceSize size) {
        void* data;
        vkMapMemory(*device, stagingBufferMemory, 0, size, 0, &data);
        memcpy(data, vertices.data(), (size_t) size);
        vkUnmapMemory(*device, stagingBufferMemory);
    }

    VkBuffer* VertexBuffer::getVertexBuffer() {
        return &vertexBuffer;
    }

    std::vector<Vertex>* VertexBuffer::getVertices() {
        return &vertices;
    }
} // dvk