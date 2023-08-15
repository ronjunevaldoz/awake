/*
 *  VkStencilOpStateAccessor.cpp
 *  Vulkan accessor for VkStencilOpState
 *  Created by Ron June Valdoz */

#include  <includes/VkStencilOpStateAccessor.h>

VkStencilOpStateAccessor::VkStencilOpStateAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    failOpField = env->GetFieldID(clazz, "failOp",
                                  "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStencilOp;");
    passOpField = env->GetFieldID(clazz, "passOp",
                                  "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStencilOp;");
    depthFailOpField = env->GetFieldID(clazz, "depthFailOp",
                                       "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStencilOp;");
    compareOpField = env->GetFieldID(clazz, "compareOp",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkCompareOp;");
    compareMaskField = env->GetFieldID(clazz, "compareMask", "I");
    writeMaskField = env->GetFieldID(clazz, "writeMask", "I");
    referenceField = env->GetFieldID(clazz, "reference", "I");
}

VkStencilOp
VkStencilOpStateAccessor::getfailOp() {
    auto failOpEnum = (jobject) env->GetObjectField(obj, failOpField);
    return (VkStencilOp) enum_utils::getEnumFromObject(env, failOpEnum);
}

uint32_t
VkStencilOpStateAccessor::getcompareMask() {
    return (uint32_t)(jint)
    env->GetIntField(obj, compareMaskField); // primitive
}

uint32_t
VkStencilOpStateAccessor::getreference() {
    return (uint32_t)(jint)
    env->GetIntField(obj, referenceField); // primitive
}

VkCompareOp
VkStencilOpStateAccessor::getcompareOp() {
    auto compareOpEnum = (jobject) env->GetObjectField(obj, compareOpField);
    return (VkCompareOp) enum_utils::getEnumFromObject(env, compareOpEnum);
}

uint32_t
VkStencilOpStateAccessor::getwriteMask() {
    return (uint32_t)(jint)
    env->GetIntField(obj, writeMaskField); // primitive
}

void
VkStencilOpStateAccessor::fromObject(VkStencilOpState &clazzInfo) {
    clazzInfo.failOp = getfailOp(); // Enum VkStencilOp
    clazzInfo.passOp = getpassOp(); // Enum VkStencilOp
    clazzInfo.depthFailOp = getdepthFailOp(); // Enum VkStencilOp
    clazzInfo.compareOp = getcompareOp(); // Enum VkCompareOp
    clazzInfo.compareMask = getcompareMask(); // Object uint32_t
    clazzInfo.writeMask = getwriteMask(); // Object uint32_t
    clazzInfo.reference = getreference(); // Object uint32_t
}

VkStencilOp
VkStencilOpStateAccessor::getpassOp() {
    auto passOpEnum = (jobject) env->GetObjectField(obj, passOpField);
    return (VkStencilOp) enum_utils::getEnumFromObject(env, passOpEnum);
}

VkStencilOp
VkStencilOpStateAccessor::getdepthFailOp() {
    auto depthFailOpEnum = (jobject) env->GetObjectField(obj, depthFailOpField);
    return (VkStencilOp) enum_utils::getEnumFromObject(env, depthFailOpEnum);
}

VkStencilOpStateAccessor::~VkStencilOpStateAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

