//
// Created by Arouay on 02/04/2023.
//

#include <vulkan/vulkan_core.h>
#include <stdexcept>
#include "GraphicsPipeline.hpp"
#include "ShadersUtils.hpp"

namespace dvk {
    GraphicsPipeline::GraphicsPipeline(VkDevice *device, VkRenderPass *renderPass, VkExtent2D *swapChainExtent) :
        device(device),
        renderPass(renderPass),
        swapChainExtent(swapChainExtent)
    {
        createGraphicsPipeline();
    }

    GraphicsPipeline::~GraphicsPipeline() {
        vkDestroyShaderModule(*device, fragShaderModule, nullptr);
        vkDestroyShaderModule(*device, vertShaderModule, nullptr);

        vkDestroyPipeline(*device, graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(*device, pipelineLayout, nullptr);
    }

    VkShaderModule GraphicsPipeline::createShaderModule(const std::vector<char>& code)
    {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(*device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create shader module!");
        }

        return shaderModule;
    }

    void GraphicsPipeline::createGraphicsPipeline()
    {
        auto vertShaderCode = utils::readFile(R"(C:\Users\Arouay\Documents\Projects\draft-vk\resources\shaders\shader.spv)");
        auto fragShaderCode = utils::readFile(R"(C:\Users\Arouay\Documents\Projects\draft-vk\resources\shaders\frag.spv)");

        vertShaderModule = createShaderModule(vertShaderCode);
        fragShaderModule = createShaderModule(fragShaderCode);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vertShaderModule;
        vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = fragShaderModule;
        fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

        VkPipelineVertexInputStateCreateInfo vertexInputState{};
        vertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputState.vertexBindingDescriptionCount = 0;
        vertexInputState.pVertexBindingDescriptions = nullptr;
        vertexInputState.vertexBindingDescriptionCount = 0;
        vertexInputState.pVertexAttributeDescriptions = nullptr;

        VkPipelineInputAssemblyStateCreateInfo inputAssemblyState{};
        inputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssemblyState.primitiveRestartEnable = VK_FALSE;

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(swapChainExtent->width);
        viewport.height = static_cast<float>(swapChainExtent->height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = *swapChainExtent;

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo rasterizerState{};
        rasterizerState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizerState.depthClampEnable = VK_FALSE;
        rasterizerState.rasterizerDiscardEnable = VK_FALSE;
        rasterizerState.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizerState.lineWidth = 1.0f;
        rasterizerState.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizerState.frontFace = VK_FRONT_FACE_CLOCKWISE;
        rasterizerState.depthBiasEnable = VK_FALSE;
        rasterizerState.depthBiasClamp = 0.0f;
        rasterizerState.depthBiasConstantFactor = 0.0f;
        rasterizerState.depthBiasSlopeFactor = 0.0f;

        VkPipelineMultisampleStateCreateInfo multisamplingState{};
        multisamplingState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisamplingState.sampleShadingEnable = VK_FALSE;
        multisamplingState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisamplingState.minSampleShading = 1.0f;
        multisamplingState.pSampleMask = nullptr;
        multisamplingState.alphaToOneEnable = VK_FALSE;
        multisamplingState.alphaToCoverageEnable = VK_FALSE;

        VkPipelineColorBlendAttachmentState colorblendAttachementState{};
        colorblendAttachementState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorblendAttachementState.blendEnable = VK_TRUE;
        colorblendAttachementState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        colorblendAttachementState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorblendAttachementState.colorBlendOp = VK_BLEND_OP_ADD;
        colorblendAttachementState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colorblendAttachementState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        colorblendAttachementState.alphaBlendOp = VK_BLEND_OP_ADD;

        VkPipelineColorBlendStateCreateInfo colorblendState{};
        colorblendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorblendState.logicOpEnable = VK_FALSE;
        colorblendState.logicOp = VK_LOGIC_OP_COPY;
        colorblendState.attachmentCount = 1;
        colorblendState.pAttachments = &colorblendAttachementState;
        colorblendState.blendConstants[0] = 0.0f;
        colorblendState.blendConstants[1] = 0.0f;
        colorblendState.blendConstants[2] = 0.0f;
        colorblendState.blendConstants[3] = 0.0f;

        VkDynamicState dynamicStates[] = {
                VK_DYNAMIC_STATE_VIEWPORT,
                VK_DYNAMIC_STATE_BLEND_CONSTANTS
        };

        VkPipelineDynamicStateCreateInfo dynamicState{};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.dynamicStateCount = 2;
        dynamicState.pDynamicStates = dynamicStates;

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;

        if (vkCreatePipelineLayout(*device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS){
            throw std::runtime_error("failed to create pipeline layout!");
        }

        VkGraphicsPipelineCreateInfo graphicsPipelineInfo{};
        graphicsPipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        graphicsPipelineInfo.stageCount = 2;
        graphicsPipelineInfo.pStages = shaderStages;
        graphicsPipelineInfo.pVertexInputState = &vertexInputState;
        graphicsPipelineInfo.pInputAssemblyState = &inputAssemblyState;
        graphicsPipelineInfo.pViewportState = &viewportState;
        graphicsPipelineInfo.pRasterizationState = &rasterizerState;
        graphicsPipelineInfo.pMultisampleState = &multisamplingState;
        graphicsPipelineInfo.pDepthStencilState = nullptr;
        graphicsPipelineInfo.pColorBlendState = &colorblendState;
        graphicsPipelineInfo.pDynamicState = nullptr;
        graphicsPipelineInfo.layout = pipelineLayout;
        graphicsPipelineInfo.renderPass = *renderPass;
        graphicsPipelineInfo.subpass = 0;
        graphicsPipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
        graphicsPipelineInfo.basePipelineIndex = -1;

        if (vkCreateGraphicsPipelines(*device, VK_NULL_HANDLE, 1, &graphicsPipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS){
            throw std::runtime_error("Failed to create graphics pipeline!");
        }
    }

    VkPipeline *GraphicsPipeline::getGraphicsPipeline() {
        return &graphicsPipeline;
    }
} // dvk