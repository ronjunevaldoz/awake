/*
 *  VkPushConstantRangeAccessor.cpp
 *  Vulkan accessor for VkPushConstantRange
 *  Created by Ron June Valdoz */

#include  <includes/VkPushConstantRangeAccessor.h>

VkPushConstantRangeAccessor::VkPushConstantRangeAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    stageFlagsField = env->GetFieldID(clazz, "stageFlags", "I");
    offsetField = env->GetFieldID(clazz, "offset", "I");
    sizeField = env->GetFieldID(clazz, "size", "I");
}

void
VkPushConstantRangeAccessor::fromObject(VkPushConstantRange &clazzInfo) {
    clazzInfo.stageFlags = getstageFlags(); // Object uint32_t
    clazzInfo.offset = getoffset(); // Object uint32_t
    clazzInfo.size = getsize(); // Object uint32_t
}

uint32_t
VkPushConstantRangeAccessor::getstageFlags() {
    return (uint32_t) (jint) env->GetIntField(obj, stageFlagsField); // primitive
}

uint32_t
VkPushConstantRangeAccessor::getsize() {
    return (uint32_t) (jint) env->GetIntField(obj, sizeField); // primitive
}

uint32_t
VkPushConstantRangeAccessor::getoffset() {
    return (uint32_t) (jint) env->GetIntField(obj, offsetField); // primitive
}

VkPushConstantRangeAccessor::~VkPushConstantRangeAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

