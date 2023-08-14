/*
 *  VkPipelineTessellationStateCreateInfoAccessor.cpp
 *  Vulkan accessor for VkPipelineTessellationStateCreateInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkPipelineTessellationStateCreateInfoAccessor.h>

VkPipelineTessellationStateCreateInfoAccessor::VkPipelineTessellationStateCreateInfoAccessor(
        JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    patchControlPointsField = env->GetFieldID(clazz, "patchControlPoints", "I");
}

VkStructureType
VkPipelineTessellationStateCreateInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

uint32_t
VkPipelineTessellationStateCreateInfoAccessor::getflags() {
    return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
}

void
VkPipelineTessellationStateCreateInfoAccessor::getpNext(
        VkPipelineTessellationStateCreateInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

void
VkPipelineTessellationStateCreateInfoAccessor::fromObject(
        VkPipelineTessellationStateCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Object void*
    clazzInfo.flags = getflags(); // Object uint32_t
    clazzInfo.patchControlPoints = getpatchControlPoints(); // Object uint32_t
}

uint32_t
VkPipelineTessellationStateCreateInfoAccessor::getpatchControlPoints() {
    return (uint32_t) (jint) env->GetIntField(obj, patchControlPointsField); // primitive
}

VkPipelineTessellationStateCreateInfoAccessor::~VkPipelineTessellationStateCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

