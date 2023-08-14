/*
 *  VkPipelineViewportStateCreateInfoAccessor.h
 *  Vulkan accessor for VkPipelineViewportStateCreateInfo
 *  Created by Ron June Valdoz */

#ifndef VKPIPELINEVIEWPORTSTATECREATEINFOACCESSOR_H
#define VKPIPELINEVIEWPORTSTATECREATEINFOACCESSOR_H

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkViewportAccessor.cpp>
#include <VkRect2DAccessor.cpp>

class VkPipelineViewportStateCreateInfoAccessor {
private:
    JNIEnv *env;
    jobject obj;
    jclass clazz;
    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID pViewportsField;
    jfieldID pScissorsField;
public:
    VkPipelineViewportStateCreateInfoAccessor(JNIEnv *env, jobject obj);

    VkStructureType getsType();

    uint32_t getflags();

    void getpNext(VkPipelineViewportStateCreateInfo &clazzInfo);

    void fromObject(VkPipelineViewportStateCreateInfo &clazzInfo);

    void getpViewports(VkPipelineViewportStateCreateInfo &clazzInfo);

    void getpScissors(VkPipelineViewportStateCreateInfo &clazzInfo);

    ~VkPipelineViewportStateCreateInfoAccessor();
};

#endif // VKPIPELINEVIEWPORTSTATECREATEINFOACCESSOR_H