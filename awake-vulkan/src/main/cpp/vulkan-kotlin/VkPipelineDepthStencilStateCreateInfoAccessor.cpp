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

VkBool32
VkPipelineDepthStencilStateCreateInfoAccessor::getdepthWriteEnable() {
    return (VkBool32) (jboolean) env->GetBooleanField(obj, depthWriteEnableField); // primitive
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

uint32_t
VkPipelineDepthStencilStateCreateInfoAccessor::getflags() {
    return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
}

VkBool32
VkPipelineDepthStencilStateCreateInfoAccessor::getdepthTestEnable() {
    return (VkBool32) (jboolean) env->GetBooleanField(obj, depthTestEnableField); // primitive
}

VkBool32
VkPipelineDepthStencilStateCreateInfoAccessor::getdepthBoundsTestEnable() {
    return (VkBool32) (jboolean) env->GetBooleanField(obj, depthBoundsTestEnableField); // primitive
}

void
VkPipelineDepthStencilStateCreateInfoAccessor::fromObject(
        VkPipelineDepthStencilStateCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Other void*
    clazzInfo.flags = getflags(); // Primitive uint32_t
    clazzInfo.depthTestEnable = getdepthTestEnable(); // Primitive VkBool32
    clazzInfo.depthWriteEnable = getdepthWriteEnable(); // Primitive VkBool32
    clazzInfo.depthCompareOp = getdepthCompareOp(); // Enum VkCompareOp
    clazzInfo.depthBoundsTestEnable = getdepthBoundsTestEnable(); // Primitive VkBool32
    clazzInfo.stencilTestEnable = getstencilTestEnable(); // Primitive VkBool32
    getfront(clazzInfo); // Other VkStencilOpState
    getback(clazzInfo); // Other VkStencilOpState
    clazzInfo.minDepthBounds = getminDepthBounds(); // Primitive float
    clazzInfo.maxDepthBounds = getmaxDepthBounds(); // Primitive float
}

VkBool32
VkPipelineDepthStencilStateCreateInfoAccessor::getstencilTestEnable() {
    return (VkBool32) (jboolean) env->GetBooleanField(obj, stencilTestEnableField); // primitive
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

VkCompareOp
VkPipelineDepthStencilStateCreateInfoAccessor::getdepthCompareOp() {
    auto depthCompareOpEnum = (jobject) env->GetObjectField(obj, depthCompareOpField);
    return (VkCompareOp) enum_utils::getEnumFromObject(env, depthCompareOpEnum);
}

VkPipelineDepthStencilStateCreateInfoAccessor::~VkPipelineDepthStencilStateCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

