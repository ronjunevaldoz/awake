/*
 *  VkPipelineInputAssemblyStateCreateInfoAccessor.h
 *  Vulkan accessor for VkPipelineInputAssemblyStateCreateInfo
 *  Created by Ron June Valdoz */

#ifndef VKPIPELINEINPUTASSEMBLYSTATECREATEINFOACCESSOR_H
#define VKPIPELINEINPUTASSEMBLYSTATECREATEINFOACCESSOR_H

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkPipelineInputAssemblyStateCreateInfoAccessor {
private:
    JNIEnv *env;
    jobject obj;
    jclass clazz;
    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID topologyField;
    jfieldID primitiveRestartEnableField;
public:
    VkPipelineInputAssemblyStateCreateInfoAccessor(JNIEnv *env, jobject obj);

    VkStructureType getsType();
    uint32_t getflags();

    bool getprimitiveRestartEnable();

    void fromObject(VkPipelineInputAssemblyStateCreateInfo &clazzInfo);

    VkPrimitiveTopology gettopology();

    void getpNext(VkPipelineInputAssemblyStateCreateInfo &clazzInfo);

    ~VkPipelineInputAssemblyStateCreateInfoAccessor();
};

#endif // VKPIPELINEINPUTASSEMBLYSTATECREATEINFOACCESSOR_H