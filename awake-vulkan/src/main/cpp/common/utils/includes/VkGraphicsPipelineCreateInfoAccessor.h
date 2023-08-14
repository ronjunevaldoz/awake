/*
 *  VkGraphicsPipelineCreateInfoAccessor.h
 *  Vulkan accessor for VkGraphicsPipelineCreateInfo
 *  Created by Ron June Valdoz */

#ifndef VKGRAPHICSPIPELINECREATEINFOACCESSOR_H
#define VKGRAPHICSPIPELINECREATEINFOACCESSOR_H

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkPipelineShaderStageCreateInfoAccessor.cpp>
#include <VkPipelineVertexInputStateCreateInfoAccessor.cpp>
#include <VkPipelineInputAssemblyStateCreateInfoAccessor.cpp>
#include <VkPipelineTessellationStateCreateInfoAccessor.cpp>
#include <VkPipelineViewportStateCreateInfoAccessor.cpp>
#include <VkPipelineRasterizationStateCreateInfoAccessor.cpp>
#include <VkPipelineMultisampleStateCreateInfoAccessor.cpp>
#include <VkPipelineDepthStencilStateCreateInfoAccessor.cpp>
#include <VkPipelineColorBlendStateCreateInfoAccessor.cpp>
#include <VkPipelineDynamicStateCreateInfoAccessor.cpp>

class VkGraphicsPipelineCreateInfoAccessor {
private:
    JNIEnv *env;
    jobject obj;
    jclass clazz;
    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID pStagesField;
    jfieldID pVertexInputStateField;
    jfieldID pInputAssemblyStateField;
    jfieldID pTessellationStateField;
    jfieldID pViewportStateField;
    jfieldID pRasterizationStateField;
    jfieldID pMultisampleStateField;
    jfieldID pDepthStencilStateField;
    jfieldID pColorBlendStateField;
    jfieldID pDynamicStateField;
    jfieldID layoutField;
    jfieldID renderPassField;
    jfieldID subpassField;
    jfieldID basePipelineHandleField;
    jfieldID basePipelineIndexField;
    jfieldID stageCountField;
public:
    VkGraphicsPipelineCreateInfoAccessor(JNIEnv *env, jobject obj);

    void getpStages(VkGraphicsPipelineCreateInfo &clazzInfo);

    VkPipeline getbasePipelineHandle();

    void getpTessellationState(VkGraphicsPipelineCreateInfo &clazzInfo);

    void getpRasterizationState(VkGraphicsPipelineCreateInfo &clazzInfo);

    void getpDepthStencilState(VkGraphicsPipelineCreateInfo &clazzInfo);

    uint32_t getsubpass();

    VkRenderPass getrenderPass();

    uint32_t getstageCount();

    VkStructureType getsType();

    int32_t getbasePipelineIndex();

    uint32_t getflags();

    void getpViewportState(VkGraphicsPipelineCreateInfo &clazzInfo);

    void getpInputAssemblyState(VkGraphicsPipelineCreateInfo &clazzInfo);

    void getpColorBlendState(VkGraphicsPipelineCreateInfo &clazzInfo);

    VkPipelineLayout getlayout();

    void getpNext(VkGraphicsPipelineCreateInfo &clazzInfo);

    void fromObject(VkGraphicsPipelineCreateInfo &clazzInfo);

    void getpVertexInputState(VkGraphicsPipelineCreateInfo &clazzInfo);

    void getpDynamicState(VkGraphicsPipelineCreateInfo &clazzInfo);

    void getpMultisampleState(VkGraphicsPipelineCreateInfo &clazzInfo);

    ~VkGraphicsPipelineCreateInfoAccessor();
};

#endif // VKGRAPHICSPIPELINECREATEINFOACCESSOR_H