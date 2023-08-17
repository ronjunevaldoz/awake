/*
 *  VkSurfaceFormatKHRMutator.cpp
 *  Vulkan mutator for VkSurfaceFormatKHR
 *  Created by Ron June Valdoz */

#include <includes/VkSurfaceFormatKHRMutator.h>

VkSurfaceFormatKHRMutator::VkSurfaceFormatKHRMutator(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/presentation/swapchain/VkSurfaceFormatKHR");
    formatField = env->GetFieldID(clazz, "format",
                                  "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFormat;");
    colorSpaceField = env->GetFieldID(clazz, "colorSpace",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkColorSpaceKHR;");
}

jobject
VkSurfaceFormatKHRMutator::toObject(VkSurfaceFormatKHR source) {
    auto constructor = env->GetMethodID(clazz, "<init>", "()V");
    auto newObj = env->NewObject(clazz, constructor);
    env->SetObjectField(newObj, formatField,
                        enum_utils::setEnumFromVulkan(env, static_cast<jint>(source.format),
                                                      "io/github/ronjunevaldoz/awake/vulkan/enums/VkFormat"));
    env->SetObjectField(newObj, colorSpaceField,
                        enum_utils::setEnumFromVulkan(env, static_cast<jint>(source.colorSpace),
                                                      "io/github/ronjunevaldoz/awake/vulkan/enums/VkColorSpaceKHR"));
    return newObj;
}

VkSurfaceFormatKHRMutator::~VkSurfaceFormatKHRMutator() {
    // env->DeleteGlobalRef(clazz);
}

