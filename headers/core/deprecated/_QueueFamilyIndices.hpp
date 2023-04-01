//
// Created by Arouay on 01/04/2023.
//

#ifndef DRAFT_VK_QUEUEFAMILYINDICES_HPP
#define DRAFT_VK_QUEUEFAMILYINDICES_HPP

#include <vulkan/vulkan_core.h>
#include <vector>
#include <optional>

namespace dvk::deprecated {

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentationFamily;

        bool isComplete() const;
    };

    } // deprecated

#endif //DRAFT_VK_QUEUEFAMILYINDICES_HPP
