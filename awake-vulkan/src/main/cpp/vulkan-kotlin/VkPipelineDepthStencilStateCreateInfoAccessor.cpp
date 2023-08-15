/*
 *  VkPipelineDepthStencilStateCreateInfoAccessor.cpp
 *  Vulkan accessor for VkPipelineDepthStencilStateCreateInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkPipelineDepthStencilStateCreateInfoAccessor.h>

VkPipelineDepthStencilStateCreateInfoAccessor::VkPipelineDepthStencilStateCreateInfoAccessor(
        JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    depthTestEnableField = env->GetFieldID(clazz, "depthTestEnable", "Z");
    depthWriteEnableField = env->GetFieldID(clazz, "depthWriteEnable", "Z");
    depthCompareOpField = env->GetFieldID(clazz, "depthCompareOp",
                                          "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkCompareOp;");
    depthBoundsTestEnableField = env->GetFieldID(clazz, "depthBoundsTestEnable", "Z");
    stencilTestEnableField = env->GetFieldID(clazz, "stencilTestEnable", "Z");
    frontField = env->GetFieldID(clazz, "front",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/models/VkStencilOpState;");
    backField = env->GetFieldID(clazz, "back",
                                "Lio/github/ronjunevaldoz/awake/vulkan/models/VkStencilOpState;");
    minDepthBoundsField = env->GetFieldID(clazz, "minDepthBounds", "F");
    maxDepthBoundsField = env->GetFieldID(clazz, "maxDepthBounds", "F");
}

float
VkPipelineDepthStencilStateCreateInfoAccessor::getmaxDepthBounds() {
    return (float) (jfloat) env->GetFloatField(obj, maxDepthBoundsField); // primitive
}

bool
VkPipelineDepthStencilStateCreateInfoAccessor::getdepthWriteEnable() {
    return (bool) (jboolean) env->GetBooleanField(obj, depthWriteEnableField); // primitive
}

bool
VkPipelineDepthStencilStateCreateInfoAccessor::getstencilTestEnable() {
    return (bool) (jboolean) env->GetBooleanField(obj, stencilTestEnableField); // primitive
}

void
VkPipelineDepthStencilStateCreateInfoAccessor::getfront(
        VkPipelineDepthStencilStateCreateInfo &clazzInfo) {
    auto frontObj = (jobject) env->GetObjectField(obj, frontField);
    if (frontObj == nullptr) {
        return;
    }
    VkStencilOpStateAccessor accessor(env, frontObj);
    VkStencilOpState ref{};
    accessor.fromObject(ref);
    clazzInfo.front = ref;
}

void
VkPipelineDepthStencilStateCreateInfoAccessor::getpNext(
        VkPipelineDepthStencilStateCreateInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

VkStructureType
VkPipelineDepthStencilStateCreateInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

bool
VkPipelineDepthStencilStateCreateInfoAccessor::getdepthBoundsTestEnable() {
    return (bool) (jboolean) env->GetBooleanField(obj, depthBoundsTestEnableField); // primitive
}

uint32_t
VkPipelineDepthStencilStateCreateInfoAccessor::getflags() {
    return (uint32_t)(jint)
    env->GetIntField(obj, flagsField); // primitive
}

void
VkPipelineDepthStencilStateCreateInfoAccessor::fromObject(
        VkPipelineDepthStencilStateCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Object void*
    clazzInfo.flags = getflags(); // Object uint32_t
    clazzInfo.depthTestEnable = getdepthTestEnable(); // Object bool
    clazzInfo.depthWriteEnable = getdepthWriteEnable(); // Object bool
    clazzInfo.depthCompareOp = getdepthCompareOp(); // Enum VkCompareOp
    clazzInfo.depthBoundsTestEnable = getdepthBoundsTestEnable(); // Object bool
    clazzInfo.stencilTestEnable = getstencilTestEnable(); // Object bool
    getfront(clazzInfo); // Object VkStencilOpState
    getback(clazzInfo); // Object VkStencilOpState
    clazzInfo.minDepthBounds = getminDepthBounds(); // Object float
    clazzInfo.maxDepthBounds = getmaxDepthBounds(); // Object float
}

float
VkPipelineDepthStencilStateCreateInfoAccessor::getminDepthBounds() {
    return (float) (jfloat) env->GetFloatField(obj, minDepthBoundsField); // primitive
}

void
VkPipelineDepthStencilStateCreateInfoAccessor::getback(
        VkPipelineDepthStencilStateCreateInfo &clazzInfo) {
    auto backObj = (jobject) env->GetObjectField(obj, backField);
    if (backObj == nullptr) {
        return;
    }
    VkStencilOpStateAccessor accessor(env, backObj);
    VkStencilOpState ref{};
    accessor.fromObject(ref);
    clazzInfo.back = ref;
}

bool
VkPipelineDepthStencilStateCreateInfoAccessor::getdepthTestEnable() {
    return (bool) (jboolean) env->GetBooleanField(obj, depthTestEnableField); // primitive
}

VkCompareOp
VkPipelineDepthStencilStateCreateInfoAccessor::getdepthCompareOp() {
    auto depthCompareOpEnum = (jobject) env->GetObjectField(obj, depthCompareOpField);
    return (VkCompareOp) enum_utils::getEnumFromObject(env, depthCompareOpEnum);
}

VkPipelineDepthStencilStateCreateInfoAccessor::~VkPipelineDepthStencilStateCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

