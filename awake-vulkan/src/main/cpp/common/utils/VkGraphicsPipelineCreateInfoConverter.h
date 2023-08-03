//
// Created by Ron June Valdoz on 8/2/23.
//

#ifndef AWAKE_VKGRAPHICSPIPELINECREATEINFOCONVERTER_H
#define AWAKE_VKGRAPHICSPIPELINECREATEINFOCONVERTER_H

#include <vulkan/vulkan.h>
#include <jni.h>
#include <vector>

class VkGraphicsPipelineCreateInfoConverter {
private:
    jclass clazz;
    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID stageCountField;
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
    JNIEnv *env;

public:
    explicit VkGraphicsPipelineCreateInfoConverter(JNIEnv *env);

    VkGraphicsPipelineCreateInfo fromObject(jobject createInfo);

    ~VkGraphicsPipelineCreateInfoConverter();
};


#endif //AWAKE_VKGRAPHICSPIPELINECREATEINFOCONVERTER_H
