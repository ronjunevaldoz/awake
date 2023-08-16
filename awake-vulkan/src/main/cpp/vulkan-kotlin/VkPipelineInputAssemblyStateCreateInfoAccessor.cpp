/*
 *  VkPipelineInputAssemblyStateCreateInfoAccessor.cpp
 *  Vulkan accessor for VkPipelineInputAssemblyStateCreateInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkPipelineInputAssemblyStateCreateInfoAccessor.h>

VkPipelineInputAssemblyStateCreateInfoAccessor::VkPipelineInputAssemblyStateCreateInfoAccessor(
        JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    topologyField = env->GetFieldID(clazz, "topology",
                                    "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkPrimitiveTopology;");
    primitiveRestartEnableField = env->GetFieldID(clazz, "primitiveRestartEnable", "Z");
}

VkStructureType
VkPipelineInputAssemblyStateCreateInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

uint32_t
VkPipelineInputAssemblyStateCreateInfoAccessor::getflags() {
    return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
}

void
VkPipelineInputAssemblyStateCreateInfoAccessor::fromObject(
        VkPipelineInputAssemblyStateCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Other void*
    clazzInfo.flags = getflags(); // Primitive uint32_t
    clazzInfo.topology = gettopology(); // Enum VkPrimitiveTopology
    clazzInfo.primitiveRestartEnable = getprimitiveRestartEnable(); // Primitive VkBool32
}

VkBool32
VkPipelineInputAssemblyStateCreateInfoAccessor::getprimitiveRestartEnable() {
    return (VkBool32) (jboolean) env->GetBooleanField(obj,
                                                      primitiveRestartEnableField); // primitive
}

VkPrimitiveTopology
VkPipelineInputAssemblyStateCreateInfoAccessor::gettopology() {
    auto topologyEnum = (jobject) env->GetObjectField(obj, topologyField);
    return (VkPrimitiveTopology) enum_utils::getEnumFromObject(env, topologyEnum);
}

void
VkPipelineInputAssemblyStateCreateInfoAccessor::getpNext(
        VkPipelineInputAssemblyStateCreateInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

VkPipelineInputAssemblyStateCreateInfoAccessor::~VkPipelineInputAssemblyStateCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

