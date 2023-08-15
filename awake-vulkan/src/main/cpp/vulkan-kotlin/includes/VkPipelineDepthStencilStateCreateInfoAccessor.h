/*
 *  VkPipelineDepthStencilStateCreateInfoAccessor.h
 *  Vulkan accessor for VkPipelineDepthStencilStateCreateInfo
 *  Created by Ron June Valdoz */

#ifndef VKPIPELINEDEPTHSTENCILSTATECREATEINFOACCESSOR_H
#define VKPIPELINEDEPTHSTENCILSTATECREATEINFOACCESSOR_H

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkStencilOpStateAccessor.h>

class VkPipelineDepthStencilStateCreateInfoAccessor {
private:
    JNIEnv *env;
    jobject obj;
    jclass clazz;
    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID depthTestEnableField;
    jfieldID depthWriteEnableField;
    jfieldID depthCompareOpField;
    jfieldID depthBoundsTestEnableField;
    jfieldID stencilTestEnableField;
    jfieldID frontField;
    jfieldID backField;
    jfieldID minDepthBoundsField;
    jfieldID maxDepthBoundsField;
public:
    VkPipelineDepthStencilStateCreateInfoAccessor(JNIEnv *env, jobject obj);

    float getmaxDepthBounds();

    bool getdepthWriteEnable();

    bool getstencilTestEnable();

    void getfront(VkPipelineDepthStencilStateCreateInfo &clazzInfo);

    void getpNext(VkPipelineDepthStencilStateCreateInfo &clazzInfo);

    VkStructureType getsType();

    bool getdepthBoundsTestEnable();

    uint32_t getflags();

    void fromObject(VkPipelineDepthStencilStateCreateInfo &clazzInfo);

    float getminDepthBounds();

    void getback(VkPipelineDepthStencilStateCreateInfo &clazzInfo);

    bool getdepthTestEnable();

    VkCompareOp getdepthCompareOp();

    ~VkPipelineDepthStencilStateCreateInfoAccessor();
};

#endif // VKPIPELINEDEPTHSTENCILSTATECREATEINFOACCESSOR_H