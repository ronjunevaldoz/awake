/*
 *  VkPipelineColorBlendAttachmentStateAccessor.cpp
 *  Vulkan accessor for VkPipelineColorBlendAttachmentState
 *  Created by Ron June Valdoz */

#include  <includes/VkPipelineColorBlendAttachmentStateAccessor.h>

VkPipelineColorBlendAttachmentStateAccessor::VkPipelineColorBlendAttachmentStateAccessor(
        JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    blendEnableField = env->GetFieldID(clazz, "blendEnable", "Z");
    srcColorBlendFactorField = env->GetFieldID(clazz, "srcColorBlendFactor",
                                               "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendFactor;");
    dstColorBlendFactorField = env->GetFieldID(clazz, "dstColorBlendFactor",
                                               "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendFactor;");
    colorBlendOpField = env->GetFieldID(clazz, "colorBlendOp",
                                        "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendOp;");
    srcAlphaBlendFactorField = env->GetFieldID(clazz, "srcAlphaBlendFactor",
                                               "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendFactor;");
    dstAlphaBlendFactorField = env->GetFieldID(clazz, "dstAlphaBlendFactor",
                                               "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendFactor;");
    alphaBlendOpField = env->GetFieldID(clazz, "alphaBlendOp",
                                        "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendOp;");
    colorWriteMaskField = env->GetFieldID(clazz, "colorWriteMask", "I");
}

VkBlendOp
VkPipelineColorBlendAttachmentStateAccessor::getcolorBlendOp() {
    auto colorBlendOpEnum = (jobject) env->GetObjectField(obj, colorBlendOpField);
    return (VkBlendOp) enum_utils::getEnumFromObject(env, colorBlendOpEnum);
}

VkBlendFactor
VkPipelineColorBlendAttachmentStateAccessor::getsrcColorBlendFactor() {
    auto srcColorBlendFactorEnum = (jobject) env->GetObjectField(obj, srcColorBlendFactorField);
    return (VkBlendFactor) enum_utils::getEnumFromObject(env, srcColorBlendFactorEnum);
}

void
VkPipelineColorBlendAttachmentStateAccessor::fromObject(
        VkPipelineColorBlendAttachmentState &clazzInfo) {
    clazzInfo.blendEnable = getblendEnable(); // Object bool
    clazzInfo.srcColorBlendFactor = getsrcColorBlendFactor(); // Enum VkBlendFactor
    clazzInfo.dstColorBlendFactor = getdstColorBlendFactor(); // Enum VkBlendFactor
    clazzInfo.colorBlendOp = getcolorBlendOp(); // Enum VkBlendOp
    clazzInfo.srcAlphaBlendFactor = getsrcAlphaBlendFactor(); // Enum VkBlendFactor
    clazzInfo.dstAlphaBlendFactor = getdstAlphaBlendFactor(); // Enum VkBlendFactor
    clazzInfo.alphaBlendOp = getalphaBlendOp(); // Enum VkBlendOp
    clazzInfo.colorWriteMask = getcolorWriteMask(); // Object uint32_t
}

uint32_t
VkPipelineColorBlendAttachmentStateAccessor::getcolorWriteMask() {
    return (uint32_t)(jint)
    env->GetIntField(obj, colorWriteMaskField); // primitive
}

VkBlendFactor
VkPipelineColorBlendAttachmentStateAccessor::getdstColorBlendFactor() {
    auto dstColorBlendFactorEnum = (jobject) env->GetObjectField(obj, dstColorBlendFactorField);
    return (VkBlendFactor) enum_utils::getEnumFromObject(env, dstColorBlendFactorEnum);
}

VkBlendFactor
VkPipelineColorBlendAttachmentStateAccessor::getsrcAlphaBlendFactor() {
    auto srcAlphaBlendFactorEnum = (jobject) env->GetObjectField(obj, srcAlphaBlendFactorField);
    return (VkBlendFactor) enum_utils::getEnumFromObject(env, srcAlphaBlendFactorEnum);
}

VkBlendOp
VkPipelineColorBlendAttachmentStateAccessor::getalphaBlendOp() {
    auto alphaBlendOpEnum = (jobject) env->GetObjectField(obj, alphaBlendOpField);
    return (VkBlendOp) enum_utils::getEnumFromObject(env, alphaBlendOpEnum);
}

VkBlendFactor
VkPipelineColorBlendAttachmentStateAccessor::getdstAlphaBlendFactor() {
    auto dstAlphaBlendFactorEnum = (jobject) env->GetObjectField(obj, dstAlphaBlendFactorField);
    return (VkBlendFactor) enum_utils::getEnumFromObject(env, dstAlphaBlendFactorEnum);
}

bool
VkPipelineColorBlendAttachmentStateAccessor::getblendEnable() {
    return (bool) (jboolean) env->GetBooleanField(obj, blendEnableField); // primitive
}

VkPipelineColorBlendAttachmentStateAccessor::~VkPipelineColorBlendAttachmentStateAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

