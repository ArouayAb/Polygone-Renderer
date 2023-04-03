//
// Created by Arouay on 02/04/2023.
//

#ifndef DRAFT_VK_SHADERSUTILS_HPP
#define DRAFT_VK_SHADERSUTILS_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <vulkan/vulkan_core.h>

namespace dvk::utils {

    std::vector<char> readFile(const std::string& fileName);

} // dvk

#endif //DRAFT_VK_SHADERSUTILS_HPP
