//
// Created by Arouay on 30/03/2023.
//

#ifndef DRAFT_VK_INSTANCE_HPP
#define DRAFT_VK_INSTANCE_HPP

#include <vulkan/vulkan_core.h>
#include <iostream>
#include <vector>
#include "Debug.hpp"

namespace dvk {

    class Instance {
    private:
        VkApplicationInfo appInfo{};
        VkInstance instance{};

        void init();
    public:
        Instance();
        ~Instance();

        [[nodiscard]]
        VkInstance* getInstance();
    };

} // dvk

#endif //DRAFT_VK_INSTANCE_HPP
