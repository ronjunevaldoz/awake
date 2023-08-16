/*
 *  VkSurfaceCapabilitiesKHRMutator.cpp
 *  Vulkan mutator for VkSurfaceCapabilitiesKHR
 *  Created by Ron June Valdoz */

#include  <includes/VkSurfaceCapabilitiesKHRMutator.h>

VkSurfaceCapabilitiesKHRMutator::VkSurfaceCapabilitiesKHRMutator(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/presentation/swapchain/VkSurfaceCapabilitiesKHR");
    minImageCountField = env->GetFieldID(clazz, "minImageCount", "I");
    maxImageCountField = env->GetFieldID(clazz, "maxImageCount", "I");
    currentExtentField = env->GetFieldID(clazz, "currentExtent",
                                         "Lio/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D;");
    minImageExtentField = env->GetFieldID(clazz, "minImageExtent",
                                          "Lio/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D;");
    maxImageExtentField = env->GetFieldID(clazz, "maxImageExtent",
                                          "Lio/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D;");
    maxImageArrayLayersField = env->GetFieldID(clazz, "maxImageArrayLayers", "I");
    supportedTransformsField = env->GetFieldID(clazz, "supportedTransforms", "I");
    currentTransformField = env->GetFieldID(clazz, "currentTransform",
                                            "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkSurfaceTransformFlagBitsKHR;");
    supportedCompositeAlphaField = env->GetFieldID(clazz, "supportedCompositeAlpha", "I");
    supportedUsageFlagsField = env->GetFieldID(clazz, "supportedUsageFlags", "I");
}

jobject
VkSurfaceCapabilitiesKHRMutator::toObject(VkSurfaceCapabilitiesKHR source) {
    auto constructor = env->GetMethodID(clazz, "<init>", "()V");
    auto newObj = env->NewObject(clazz, constructor);
    env->SetIntField(newObj, minImageCountField, static_cast<jint>(source.minImageCount));
    env->SetIntField(newObj, maxImageCountField, static_cast<jint>(source.maxImageCount));
    VkExtent2DMutator currentExtentMutator(env);
    env->SetObjectField(newObj, currentExtentField,
                        currentExtentMutator.toObject(source.currentExtent));
    VkExtent2DMutator minImageExtentMutator(env);
    env->SetObjectField(newObj, minImageExtentField,
                        minImageExtentMutator.toObject(source.minImageExtent));
    VkExtent2DMutator maxImageExtentMutator(env);
    env->SetObjectField(newObj, maxImageExtentField,
                        maxImageExtentMutator.toObject(source.maxImageExtent));
    env->SetIntField(newObj, maxImageArrayLayersField,
                     static_cast<jint>(source.maxImageArrayLayers));
    env->SetIntField(newObj, supportedTransformsField,
                     static_cast<jint>(source.supportedTransforms));
    env->SetObjectField(newObj, currentTransformField, enum_utils::setEnumFromVulkan(env,
                                                                                     static_cast<jint>(source.currentTransform),
                                                                                     "io/github/ronjunevaldoz/awake/vulkan/enums/VkSurfaceTransformFlagBitsKHR"));
    env->SetIntField(newObj, supportedCompositeAlphaField,
                     static_cast<jint>(source.supportedCompositeAlpha));
    env->SetIntField(newObj, supportedUsageFlagsField,
                     static_cast<jint>(source.supportedUsageFlags));
    return newObj;
}

VkSurfaceCapabilitiesKHRMutator::~VkSurfaceCapabilitiesKHRMutator() {
    // env->DeleteGlobalRef(clazz);
}

