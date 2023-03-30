#ifndef QUEUE_FAMILY_INDICES
#define QUEUE_FAMILY_INDICES

#include <optional>
#include <cstdint>

namespace dvk {

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentationFamily;

        bool isComplete() const;
    };
}

#endif