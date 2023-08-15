/*
 *  VkSubpassDependencyAccessor.cpp
 *  Vulkan accessor for VkSubpassDependency
 *  Created by Ron June Valdoz */

#include  <includes/VkSubpassDependencyAccessor.h>

VkSubpassDependencyAccessor::VkSubpassDependencyAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    srcSubpassField = env->GetFieldID(clazz, "srcSubpass", "I");
    dstSubpassField = env->GetFieldID(clazz, "dstSubpass", "I");
    srcStageMaskField = env->GetFieldID(clazz, "srcStageMask", "I");
    dstStageMaskField = env->GetFieldID(clazz, "dstStageMask", "I");
    srcAccessMaskField = env->GetFieldID(clazz, "srcAccessMask", "I");
    dstAccessMaskField = env->GetFieldID(clazz, "dstAccessMask", "I");
    dependencyFlagsField = env->GetFieldID(clazz, "dependencyFlags", "I");
}

uint32_t
VkSubpassDependencyAccessor::getdstStageMask() {
    return (uint32_t)(jint)
    env->GetIntField(obj, dstStageMaskField); // primitive
}

uint32_t
VkSubpassDependencyAccessor::getdstAccessMask() {
    return (uint32_t)(jint)
    env->GetIntField(obj, dstAccessMaskField); // primitive
}

uint32_t
VkSubpassDependencyAccessor::getsrcSubpass() {
    return (uint32_t)(jint)
    env->GetIntField(obj, srcSubpassField); // primitive
}

uint32_t
VkSubpassDependencyAccessor::getdstSubpass() {
    return (uint32_t)(jint)
    env->GetIntField(obj, dstSubpassField); // primitive
}

uint32_t
VkSubpassDependencyAccessor::getdependencyFlags() {
    return (uint32_t)(jint)
    env->GetIntField(obj, dependencyFlagsField); // primitive
}

uint32_t
VkSubpassDependencyAccessor::getsrcAccessMask() {
    return (uint32_t)(jint)
    env->GetIntField(obj, srcAccessMaskField); // primitive
}

uint32_t
VkSubpassDependencyAccessor::getsrcStageMask() {
    return (uint32_t)(jint)
    env->GetIntField(obj, srcStageMaskField); // primitive
}

void
VkSubpassDependencyAccessor::fromObject(VkSubpassDependency &clazzInfo) {
    clazzInfo.srcSubpass = getsrcSubpass(); // Object uint32_t
    clazzInfo.dstSubpass = getdstSubpass(); // Object uint32_t
    clazzInfo.srcStageMask = getsrcStageMask(); // Object uint32_t
    clazzInfo.dstStageMask = getdstStageMask(); // Object uint32_t
    clazzInfo.srcAccessMask = getsrcAccessMask(); // Object uint32_t
    clazzInfo.dstAccessMask = getdstAccessMask(); // Object uint32_t
    clazzInfo.dependencyFlags = getdependencyFlags(); // Object uint32_t
}

VkSubpassDependencyAccessor::~VkSubpassDependencyAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}
