//
// Created by Arouay on 02/04/2023.
//

#ifndef DRAFT_VK_GRAPHICSPIPELINE_HPP
#define DRAFT_VK_GRAPHICSPIPELINE_HPP

#include <vulkan/vulkan_core.h>
#include <vector>

namespace dvk {

    class GraphicsPipeline {
    private:
        VkPipelineLayout pipelineLayout{};
        VkPipeline graphicsPipeline{};
        VkShaderModule vertShaderModule{};
        VkShaderModule fragShaderModule{};
        VkDevice* device;
        VkRenderPass* renderPass;
        VkExtent2D* swapChainExtent;

        VkShaderModule createShaderModule(const std::vector<char>& code);
        void createGraphicsPipeline();
    public:
        GraphicsPipeline(VkDevice *device, VkRenderPass *renderPass, VkExtent2D *swapChainExtent);
        ~GraphicsPipeline();

        VkPipeline* getGraphicsPipeline();
    };

} // dvk

#endif //DRAFT_VK_GRAPHICSPIPELINE_HPP
