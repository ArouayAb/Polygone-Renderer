//
// Created by Arouay on 30/03/2023.
//

#ifndef DRAFT_VK_CONSTANTS_HPP
#define DRAFT_VK_CONSTANTS_HPP
namespace dvk::constants {

    #ifdef NDEBUG
            const bool enable_Validation_Layers = false;
    #else
            const bool enable_Validation_Layers = true;
    #endif
    }

#endif //DRAFT_VK_CONSTANTS_HPP
