/*
 *  VkVertexInputBindingDescriptionAccessor.cpp
 *  Vulkan accessor for VkVertexInputBindingDescription
 *  Created by Ron June Valdoz */

#include  <includes/VkVertexInputBindingDescriptionAccessor.h>

VkVertexInputBindingDescriptionAccessor::VkVertexInputBindingDescriptionAccessor(JNIEnv *env,
                                                                                 jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    bindingField = env->GetFieldID(clazz, "binding", "I");
    strideField = env->GetFieldID(clazz, "stride", "I");
    inputRateField = env->GetFieldID(clazz, "inputRate",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkVertexInputRate;");
}

uint32_t
VkVertexInputBindingDescriptionAccessor::getbinding() {
    return (uint32_t)(jint)
    env->GetIntField(obj, bindingField); // primitive
}

VkVertexInputRate
VkVertexInputBindingDescriptionAccessor::getinputRate() {
    auto inputRateEnum = (jobject) env->GetObjectField(obj, inputRateField);
    return (VkVertexInputRate) enum_utils::getEnumFromObject(env, inputRateEnum);
}

uint32_t
VkVertexInputBindingDescriptionAccessor::getstride() {
    return (uint32_t)(jint)
    env->GetIntField(obj, strideField); // primitive
}

void
VkVertexInputBindingDescriptionAccessor::fromObject(VkVertexInputBindingDescription &clazzInfo) {
    clazzInfo.binding = getbinding(); // Object uint32_t
    clazzInfo.stride = getstride(); // Object uint32_t
    clazzInfo.inputRate = getinputRate(); // Enum VkVertexInputRate
}

VkVertexInputBindingDescriptionAccessor::~VkVertexInputBindingDescriptionAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

