//
// Created by Ron June Valdoz on 8/2/23.
//

#include "VkGraphicsPipelineCreateInfoConverter.h"
#include "enum_utils.h"
#include "VkPipelineShaderStageCreateInfoConverter.h"

VkGraphicsPipelineCreateInfoConverter::VkGraphicsPipelineCreateInfoConverter(JNIEnv *env) {
    this->env = env;

    // Find the class and fields IDs for VkGraphicsPipelineCreateInfo
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/VkGraphicsPipelineCreateInfo"); // Update with the actual class path
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    stageCountField = env->GetFieldID(clazz, "stageCount", "I");
    pStagesField = env->GetFieldID(clazz, "pStages",
                                   "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/VkPipelineShaderStageCreateInfo;");
    pVertexInputStateField = env->GetFieldID(clazz, "pVertexInputState", "J");
    pInputAssemblyStateField = env->GetFieldID(clazz, "pInputAssemblyState", "J");
    pTessellationStateField = env->GetFieldID(clazz, "pTessellationState", "J");
    pViewportStateField = env->GetFieldID(clazz, "pViewportState", "J");
    pRasterizationStateField = env->GetFieldID(clazz, "pRasterizationState", "J");
    pMultisampleStateField = env->GetFieldID(clazz, "pMultisampleState", "J");
    pDepthStencilStateField = env->GetFieldID(clazz, "pDepthStencilState", "J");
    pColorBlendStateField = env->GetFieldID(clazz, "pColorBlendState", "J");
    pDynamicStateField = env->GetFieldID(clazz, "pDynamicState", "J");
    layoutField = env->GetFieldID(clazz, "layout", "J");
    renderPassField = env->GetFieldID(clazz, "renderPass", "J");
    subpassField = env->GetFieldID(clazz, "subpass", "I");
    basePipelineHandleField = env->GetFieldID(clazz, "basePipelineHandle", "J");
    basePipelineIndexField = env->GetFieldID(clazz, "basePipelineIndex", "I");
}

VkGraphicsPipelineCreateInfo
VkGraphicsPipelineCreateInfoConverter::fromObject(jobject pCreateInfo) {
    VkGraphicsPipelineCreateInfo result;
    VkPipelineShaderStageCreateInfoConverter shaderStageConverter(env);
    auto typeObj = env->GetObjectField(pCreateInfo, sTypeField);
    auto pNextObj = env->GetObjectField(pCreateInfo, pNextField);
    auto stagesObj = (jobjectArray) env->GetObjectField(pCreateInfo, pStagesField);
    auto stageCount = env->GetIntField(pCreateInfo, stageCountField);
    auto stageSize = env->GetArrayLength(stagesObj);
    std::vector<VkPipelineShaderStageCreateInfo> stages;
    for (int i = 0; i < stageSize; ++i) {
        auto stageObj = env->GetObjectArrayElement(stagesObj, i);
        auto stageInfo = shaderStageConverter.fromObject(stageObj);
        stages.push_back(stageInfo);
        env->DeleteLocalRef(stageObj);
    }

    // Extract the values from the Java/Kotlin object and assign them to the VkGraphicsPipelineCreateInfo fields
    result.sType = static_cast<VkStructureType>(enum_utils::getEnumFromObject(env, typeObj));
    result.pNext = static_cast<void *>(pNextObj);
    result.flags = static_cast<VkPipelineCreateFlags>(env->GetIntField(pCreateInfo, flagsField));
    result.stageCount = static_cast<uint32_t>(stages.size());
    result.pStages = stages.data();
//    result.pVertexInputState = reinterpret_cast<VkPipelineVertexInputStateCreateInfo*>(env->GetLongField(createInfo, pVertexInputStateField));
//    result.pInputAssemblyState = reinterpret_cast<VkPipelineInputAssemblyStateCreateInfo*>(env->GetLongField(createInfo, pInputAssemblyStateField));
//    result.pTessellationState = reinterpret_cast<VkPipelineTessellationStateCreateInfo*>(env->GetLongField(createInfo, pTessellationStateField));
//    result.pViewportState = reinterpret_cast<VkPipelineViewportStateCreateInfo*>(env->GetLongField(createInfo, pViewportStateField));
//    result.pRasterizationState = reinterpret_cast<VkPipelineRasterizationStateCreateInfo*>(env->GetLongField(createInfo, pRasterizationStateField));
//    result.pMultisampleState = reinterpret_cast<VkPipelineMultisampleStateCreateInfo*>(env->GetLongField(createInfo, pMultisampleStateField));
//    result.pDepthStencilState = reinterpret_cast<VkPipelineDepthStencilStateCreateInfo*>(env->GetLongField(createInfo, pDepthStencilStateField));
//    result.pColorBlendState = reinterpret_cast<VkPipelineColorBlendStateCreateInfo*>(env->GetLongField(createInfo, pColorBlendStateField));
//    result.pDynamicState = reinterpret_cast<VkPipelineDynamicStateCreateInfo*>(env->GetLongField(createInfo, pDynamicStateField));
    result.layout = reinterpret_cast<VkPipelineLayout>(env->GetLongField(pCreateInfo, layoutField));
    result.renderPass = reinterpret_cast<VkRenderPass>(env->GetLongField(pCreateInfo,
                                                                         renderPassField));
    result.subpass = env->GetIntField(pCreateInfo, subpassField);
    result.basePipelineHandle = reinterpret_cast<VkPipeline>(env->GetLongField(pCreateInfo,
                                                                               basePipelineHandleField));
    result.basePipelineIndex = env->GetIntField(pCreateInfo, basePipelineIndexField);
    env->DeleteLocalRef(typeObj);
    env->DeleteLocalRef(stagesObj);
    return result;
}

VkGraphicsPipelineCreateInfoConverter::~VkGraphicsPipelineCreateInfoConverter() {
    env->DeleteLocalRef(clazz);
    sTypeField = nullptr;
    pNextField = nullptr;
    flagsField = nullptr;
    stageCountField = nullptr;
    pStagesField = nullptr;
    pVertexInputStateField = nullptr;
    pInputAssemblyStateField = nullptr;
    pTessellationStateField = nullptr;
    pViewportStateField = nullptr;
    pRasterizationStateField = nullptr;
    pMultisampleStateField = nullptr;
    pDepthStencilStateField = nullptr;
    pColorBlendStateField = nullptr;
    pDynamicStateField = nullptr;
    layoutField = nullptr;
    renderPassField = nullptr;
    subpassField = nullptr;
    basePipelineHandleField = nullptr;
    basePipelineIndexField = nullptr;
}
