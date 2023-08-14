/*
 *  VkPipelineMultisampleStateCreateInfoAccessor.h
 *  Vulkan accessor for VkPipelineMultisampleStateCreateInfo
 *  Created by Ron June Valdoz */

#ifndef VKPIPELINEMULTISAMPLESTATECREATEINFOACCESSOR_H
#define VKPIPELINEMULTISAMPLESTATECREATEINFOACCESSOR_H

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkPipelineMultisampleStateCreateInfoAccessor {
private:
    JNIEnv *env;
    jobject obj;
    jclass clazz;
    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID rasterizationSamplesField;
    jfieldID sampleShadingEnableField;
    jfieldID minSampleShadingField;
    jfieldID pSampleMaskField;
    jfieldID alphaToCoverageEnableField;
    jfieldID alphaToOneEnableField;
public:
    VkPipelineMultisampleStateCreateInfoAccessor(JNIEnv *env, jobject obj);

    VkStructureType getsType();

    bool getalphaToOneEnable();

    uint32_t getflags();

    void fromObject(VkPipelineMultisampleStateCreateInfo &clazzInfo);

    void getpSampleMask(VkPipelineMultisampleStateCreateInfo &clazzInfo);

    bool getalphaToCoverageEnable();

    float getminSampleShading();

    VkSampleCountFlagBits getrasterizationSamples();

    bool getsampleShadingEnable();

    void getpNext(VkPipelineMultisampleStateCreateInfo &clazzInfo);

    ~VkPipelineMultisampleStateCreateInfoAccessor();
};

#endif // VKPIPELINEMULTISAMPLESTATECREATEINFOACCESSOR_H