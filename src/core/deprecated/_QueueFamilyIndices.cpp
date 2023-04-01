//
// Created by Arouay on 01/04/2023.
//

#include "_QueueFamilyIndices.hpp"

namespace dvk::deprecated {
    bool QueueFamilyIndices::isComplete() const
    {
        return graphicsFamily.has_value() && presentationFamily.has_value();
    }
} // deprecated