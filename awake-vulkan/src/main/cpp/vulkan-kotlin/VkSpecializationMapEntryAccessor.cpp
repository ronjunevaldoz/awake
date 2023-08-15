/*
 *  VkSpecializationMapEntryAccessor.cpp
 *  Vulkan accessor for VkSpecializationMapEntry
 *  Created by Ron June Valdoz */

#include  <includes/VkSpecializationMapEntryAccessor.h>

VkSpecializationMapEntryAccessor::VkSpecializationMapEntryAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    constantIDField = env->GetFieldID(clazz, "constantID", "I");
    offsetField = env->GetFieldID(clazz, "offset", "I");
    sizeField = env->GetFieldID(clazz, "size", "J");
}

void
VkSpecializationMapEntryAccessor::fromObject(VkSpecializationMapEntry &clazzInfo) {
    clazzInfo.constantID = getconstantID(); // Object uint32_t
    clazzInfo.offset = getoffset(); // Object uint32_t
    clazzInfo.size = getsize(); // Object uint64_t
}

uint64_t
VkSpecializationMapEntryAccessor::getsize() {
    return (uint64_t)(jlong)
    env->GetLongField(obj, sizeField); // primitive
}

uint32_t
VkSpecializationMapEntryAccessor::getconstantID() {
    return (uint32_t)(jint)
    env->GetIntField(obj, constantIDField); // primitive
}

uint32_t
VkSpecializationMapEntryAccessor::getoffset() {
    return (uint32_t)(jint)
    env->GetIntField(obj, offsetField); // primitive
}

VkSpecializationMapEntryAccessor::~VkSpecializationMapEntryAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

