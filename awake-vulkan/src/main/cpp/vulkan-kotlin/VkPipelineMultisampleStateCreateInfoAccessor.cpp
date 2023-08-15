/*
 *  VkPipelineMultisampleStateCreateInfoAccessor.cpp
 *  Vulkan accessor for VkPipelineMultisampleStateCreateInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkPipelineMultisampleStateCreateInfoAccessor.h>

VkPipelineMultisampleStateCreateInfoAccessor::VkPipelineMultisampleStateCreateInfoAccessor(
        JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    rasterizationSamplesField = env->GetFieldID(clazz, "rasterizationSamples",
                                                "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkSampleCountFlagBits;");
    sampleShadingEnableField = env->GetFieldID(clazz, "sampleShadingEnable", "Z");
    minSampleShadingField = env->GetFieldID(clazz, "minSampleShading", "F");
    pSampleMaskField = env->GetFieldID(clazz, "pSampleMask", "I");
    alphaToCoverageEnableField = env->GetFieldID(clazz, "alphaToCoverageEnable", "Z");
    alphaToOneEnableField = env->GetFieldID(clazz, "alphaToOneEnable", "Z");
}

VkStructureType
VkPipelineMultisampleStateCreateInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

bool
VkPipelineMultisampleStateCreateInfoAccessor::getalphaToOneEnable() {
    return (bool) (jboolean) env->GetBooleanField(obj, alphaToOneEnableField); // primitive
}

uint32_t
VkPipelineMultisampleStateCreateInfoAccessor::getflags() {
    return (uint32_t)(jint)
    env->GetIntField(obj, flagsField); // primitive
}

void
VkPipelineMultisampleStateCreateInfoAccessor::fromObject(
        VkPipelineMultisampleStateCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Object void*
    clazzInfo.flags = getflags(); // Object uint32_t
    clazzInfo.rasterizationSamples = getrasterizationSamples(); // Enum VkSampleCountFlagBits
    clazzInfo.sampleShadingEnable = getsampleShadingEnable(); // Object bool
    clazzInfo.minSampleShading = getminSampleShading(); // Object float
    getpSampleMask(clazzInfo); // Pointer
    clazzInfo.alphaToCoverageEnable = getalphaToCoverageEnable(); // Object bool
    clazzInfo.alphaToOneEnable = getalphaToOneEnable(); // Object bool
}

void
VkPipelineMultisampleStateCreateInfoAccessor::getpSampleMask(
        VkPipelineMultisampleStateCreateInfo &clazzInfo) {
    auto ptr = (uint32_t) env->GetIntField(obj, pSampleMaskField); // Primitive Pointer
    clazzInfo.pSampleMask = &ptr; // Primitive Pointer
}

bool
VkPipelineMultisampleStateCreateInfoAccessor::getalphaToCoverageEnable() {
    return (bool) (jboolean) env->GetBooleanField(obj, alphaToCoverageEnableField); // primitive
}

float
VkPipelineMultisampleStateCreateInfoAccessor::getminSampleShading() {
    return (float) (jfloat) env->GetFloatField(obj, minSampleShadingField); // primitive
}

VkSampleCountFlagBits
VkPipelineMultisampleStateCreateInfoAccessor::getrasterizationSamples() {
    auto rasterizationSamplesEnum = (jobject) env->GetObjectField(obj, rasterizationSamplesField);
    return (VkSampleCountFlagBits) enum_utils::getEnumFromObject(env, rasterizationSamplesEnum);
}

bool
VkPipelineMultisampleStateCreateInfoAccessor::getsampleShadingEnable() {
    return (bool) (jboolean) env->GetBooleanField(obj, sampleShadingEnableField); // primitive
}

void
VkPipelineMultisampleStateCreateInfoAccessor::getpNext(
        VkPipelineMultisampleStateCreateInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

VkPipelineMultisampleStateCreateInfoAccessor::~VkPipelineMultisampleStateCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

