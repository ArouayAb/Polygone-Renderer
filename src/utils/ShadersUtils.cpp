//
// Created by Arouay on 02/04/2023.
//
#include "ShadersUtils.hpp"

namespace dvk::utils {
    std::vector<char> readFile(const std::string& fileName)
    {
        std::ifstream file(fileName, std::ios::ate | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open shader file!");
        }

        size_t fileBuffer = file.tellg();
        file.seekg(0);

        std::vector<char> buffer(fileBuffer);
        file.read(buffer.data(), fileBuffer);

        file.close();

        return buffer;
    }
} // dvk