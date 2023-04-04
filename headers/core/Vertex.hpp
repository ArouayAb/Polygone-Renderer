//
// Created by Arouay on 04/04/2023.
//

#ifndef DRAFT_VK_VERTEX_HPP
#define DRAFT_VK_VERTEX_HPP

#include <glm/glm.hpp>
#include "vulkan/vulkan.hpp"

namespace dvk {

    struct Vertex {
        glm::vec2 pos;
        glm::vec3 color;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex),
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescription() {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescription{};
            attributeDescription[0].binding = 0;
            attributeDescription[0].location = 0;
            attributeDescription[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescription[0].offset = offsetof(Vertex, pos);

            attributeDescription[1].binding = 0;
            attributeDescription[1].location = 1;
            attributeDescription[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescription[1].offset = offsetof(Vertex, color);

            return attributeDescription;
        }
    };

} // dvk

#endif //DRAFT_VK_VERTEX_HPP
