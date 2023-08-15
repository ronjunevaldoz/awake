/*
 *  VkVertexInputAttributeDescriptionAccessor.cpp
 *  Vulkan accessor for VkVertexInputAttributeDescription
 *  Created by Ron June Valdoz */

#include  <includes/VkVertexInputAttributeDescriptionAccessor.h>

VkVertexInputAttributeDescriptionAccessor::VkVertexInputAttributeDescriptionAccessor(JNIEnv *env,
                                                                                     jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    locationField = env->GetFieldID(clazz, "location", "I");
    bindingField = env->GetFieldID(clazz, "binding", "I");
    formatField = env->GetFieldID(clazz, "format",
                                  "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFormat;");
    offsetField = env->GetFieldID(clazz, "offset", "I");
}

uint32_t
VkVertexInputAttributeDescriptionAccessor::getlocation() {
    return (uint32_t)(jint)
    env->GetIntField(obj, locationField); // primitive
}

uint32_t
VkVertexInputAttributeDescriptionAccessor::getbinding() {
    return (uint32_t)(jint)
    env->GetIntField(obj, bindingField); // primitive
}

void
VkVertexInputAttributeDescriptionAccessor::fromObject(
        VkVertexInputAttributeDescription &clazzInfo) {
    clazzInfo.location = getlocation(); // Object uint32_t
    clazzInfo.binding = getbinding(); // Object uint32_t
    clazzInfo.format = getformat(); // Enum VkFormat
    clazzInfo.offset = getoffset(); // Object uint32_t
}

VkFormat
VkVertexInputAttributeDescriptionAccessor::getformat() {
    auto formatEnum = (jobject) env->GetObjectField(obj, formatField);
    return (VkFormat) enum_utils::getEnumFromObject(env, formatEnum);
}

uint32_t
VkVertexInputAttributeDescriptionAccessor::getoffset() {
    return (uint32_t)(jint)
    env->GetIntField(obj, offsetField); // primitive
}

VkVertexInputAttributeDescriptionAccessor::~VkVertexInputAttributeDescriptionAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

