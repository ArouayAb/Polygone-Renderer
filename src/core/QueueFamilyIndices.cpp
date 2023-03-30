#include "QueueFamilyIndices.hpp"

namespace dvk {
    bool QueueFamilyIndices::isComplete() const
    {
        return graphicsFamily.has_value() && presentationFamily.has_value();
    }
}