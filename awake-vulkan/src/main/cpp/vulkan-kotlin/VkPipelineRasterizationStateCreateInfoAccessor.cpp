/*
 *  VkPipelineRasterizationStateCreateInfoAccessor.cpp
 *  Vulkan accessor for VkPipelineRasterizationStateCreateInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkPipelineRasterizationStateCreateInfoAccessor.h>

VkPipelineRasterizationStateCreateInfoAccessor::VkPipelineRasterizationStateCreateInfoAccessor(
        JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    depthClampEnableField = env->GetFieldID(clazz, "depthClampEnable", "Z");
    rasterizerDiscardEnableField = env->GetFieldID(clazz, "rasterizerDiscardEnable", "Z");
    polygonModeField = env->GetFieldID(clazz, "polygonMode",
                                       "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkPolygonMode;");
    cullModeField = env->GetFieldID(clazz, "cullMode", "I");
    frontFaceField = env->GetFieldID(clazz, "frontFace",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFrontFace;");
    depthBiasEnableField = env->GetFieldID(clazz, "depthBiasEnable", "Z");
    depthBiasConstantFactorField = env->GetFieldID(clazz, "depthBiasConstantFactor", "F");
    depthBiasClampField = env->GetFieldID(clazz, "depthBiasClamp", "F");
    depthBiasSlopeFactorField = env->GetFieldID(clazz, "depthBiasSlopeFactor", "F");
    lineWidthField = env->GetFieldID(clazz, "lineWidth", "F");
}

float
VkPipelineRasterizationStateCreateInfoAccessor::getlineWidth() {
    return (float) (jfloat) env->GetFloatField(obj, lineWidthField); // primitive
}

VkPolygonMode
VkPipelineRasterizationStateCreateInfoAccessor::getpolygonMode() {
    auto polygonModeEnum = (jobject) env->GetObjectField(obj, polygonModeField);
    return (VkPolygonMode) enum_utils::getEnumFromObject(env, polygonModeEnum);
}

float
VkPipelineRasterizationStateCreateInfoAccessor::getdepthBiasConstantFactor() {
    return (float) (jfloat) env->GetFloatField(obj, depthBiasConstantFactorField); // primitive
}

float
VkPipelineRasterizationStateCreateInfoAccessor::getdepthBiasClamp() {
    return (float) (jfloat) env->GetFloatField(obj, depthBiasClampField); // primitive
}

VkFrontFace
VkPipelineRasterizationStateCreateInfoAccessor::getfrontFace() {
    auto frontFaceEnum = (jobject) env->GetObjectField(obj, frontFaceField);
    return (VkFrontFace) enum_utils::getEnumFromObject(env, frontFaceEnum);
}

bool
VkPipelineRasterizationStateCreateInfoAccessor::getdepthClampEnable() {
    return (bool) (jboolean) env->GetBooleanField(obj, depthClampEnableField); // primitive
}

VkStructureType
VkPipelineRasterizationStateCreateInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

void
VkPipelineRasterizationStateCreateInfoAccessor::getpNext(
        VkPipelineRasterizationStateCreateInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

uint32_t
VkPipelineRasterizationStateCreateInfoAccessor::getflags() {
    return (uint32_t)(jint)
    env->GetIntField(obj, flagsField); // primitive
}

float
VkPipelineRasterizationStateCreateInfoAccessor::getdepthBiasSlopeFactor() {
    return (float) (jfloat) env->GetFloatField(obj, depthBiasSlopeFactorField); // primitive
}

bool
VkPipelineRasterizationStateCreateInfoAccessor::getdepthBiasEnable() {
    return (bool) (jboolean) env->GetBooleanField(obj, depthBiasEnableField); // primitive
}

bool
VkPipelineRasterizationStateCreateInfoAccessor::getrasterizerDiscardEnable() {
    return (bool) (jboolean) env->GetBooleanField(obj, rasterizerDiscardEnableField); // primitive
}

void
VkPipelineRasterizationStateCreateInfoAccessor::fromObject(
        VkPipelineRasterizationStateCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Object void*
    clazzInfo.flags = getflags(); // Object uint32_t
    clazzInfo.depthClampEnable = getdepthClampEnable(); // Object bool
    clazzInfo.rasterizerDiscardEnable = getrasterizerDiscardEnable(); // Object bool
    clazzInfo.polygonMode = getpolygonMode(); // Enum VkPolygonMode
    clazzInfo.cullMode = getcullMode(); // Object uint32_t
    clazzInfo.frontFace = getfrontFace(); // Enum VkFrontFace
    clazzInfo.depthBiasEnable = getdepthBiasEnable(); // Object bool
    clazzInfo.depthBiasConstantFactor = getdepthBiasConstantFactor(); // Object float
    clazzInfo.depthBiasClamp = getdepthBiasClamp(); // Object float
    clazzInfo.depthBiasSlopeFactor = getdepthBiasSlopeFactor(); // Object float
    clazzInfo.lineWidth = getlineWidth(); // Object float
}

uint32_t
VkPipelineRasterizationStateCreateInfoAccessor::getcullMode() {
    return (uint32_t)(jint)
    env->GetIntField(obj, cullModeField); // primitive
}

VkPipelineRasterizationStateCreateInfoAccessor::~VkPipelineRasterizationStateCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

