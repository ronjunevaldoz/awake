/*
 *  VkAttachmentDescriptionAccessor.cpp
 *  Vulkan accessor for VkAttachmentDescription
 *  Created by Ron June Valdoz */

#include  <includes/VkAttachmentDescriptionAccessor.h>

VkAttachmentDescriptionAccessor::VkAttachmentDescriptionAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    flagsField = env->GetFieldID(clazz, "flags", "I");
    formatField = env->GetFieldID(clazz, "format",
                                  "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFormat;");
    samplesField = env->GetFieldID(clazz, "samples",
                                   "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkSampleCountFlagBits;");
    loadOpField = env->GetFieldID(clazz, "loadOp",
                                  "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkAttachmentLoadOp;");
    storeOpField = env->GetFieldID(clazz, "storeOp",
                                   "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkAttachmentStoreOp;");
    stencilLoadOpField = env->GetFieldID(clazz, "stencilLoadOp",
                                         "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkAttachmentLoadOp;");
    stencilStoreOpField = env->GetFieldID(clazz, "stencilStoreOp",
                                          "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkAttachmentStoreOp;");
    initialLayoutField = env->GetFieldID(clazz, "initialLayout",
                                         "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkImageLayout;");
    finalLayoutField = env->GetFieldID(clazz, "finalLayout",
                                       "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkImageLayout;");
}

uint32_t
VkAttachmentDescriptionAccessor::getflags() {
    return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
}

VkSampleCountFlagBits
VkAttachmentDescriptionAccessor::getsamples() {
    auto samplesEnum = (jobject) env->GetObjectField(obj, samplesField);
    return (VkSampleCountFlagBits) enum_utils::getEnumFromObject(env, samplesEnum);
}

VkAttachmentStoreOp
VkAttachmentDescriptionAccessor::getstencilStoreOp() {
    auto stencilStoreOpEnum = (jobject) env->GetObjectField(obj, stencilStoreOpField);
    return (VkAttachmentStoreOp) enum_utils::getEnumFromObject(env, stencilStoreOpEnum);
}

VkAttachmentLoadOp
VkAttachmentDescriptionAccessor::getloadOp() {
    auto loadOpEnum = (jobject) env->GetObjectField(obj, loadOpField);
    return (VkAttachmentLoadOp) enum_utils::getEnumFromObject(env, loadOpEnum);
}

VkImageLayout
VkAttachmentDescriptionAccessor::getfinalLayout() {
    auto finalLayoutEnum = (jobject) env->GetObjectField(obj, finalLayoutField);
    return (VkImageLayout) enum_utils::getEnumFromObject(env, finalLayoutEnum);
}

VkAttachmentStoreOp
VkAttachmentDescriptionAccessor::getstoreOp() {
    auto storeOpEnum = (jobject) env->GetObjectField(obj, storeOpField);
    return (VkAttachmentStoreOp) enum_utils::getEnumFromObject(env, storeOpEnum);
}

VkImageLayout
VkAttachmentDescriptionAccessor::getinitialLayout() {
    auto initialLayoutEnum = (jobject) env->GetObjectField(obj, initialLayoutField);
    return (VkImageLayout) enum_utils::getEnumFromObject(env, initialLayoutEnum);
}

VkFormat
VkAttachmentDescriptionAccessor::getformat() {
    auto formatEnum = (jobject) env->GetObjectField(obj, formatField);
    return (VkFormat) enum_utils::getEnumFromObject(env, formatEnum);
}

VkAttachmentLoadOp
VkAttachmentDescriptionAccessor::getstencilLoadOp() {
    auto stencilLoadOpEnum = (jobject) env->GetObjectField(obj, stencilLoadOpField);
    return (VkAttachmentLoadOp) enum_utils::getEnumFromObject(env, stencilLoadOpEnum);
}

void
VkAttachmentDescriptionAccessor::fromObject(VkAttachmentDescription &clazzInfo) {
    clazzInfo.flags = getflags(); // Primitive uint32_t
    clazzInfo.format = getformat(); // Enum VkFormat
    clazzInfo.samples = getsamples(); // Enum VkSampleCountFlagBits
    clazzInfo.loadOp = getloadOp(); // Enum VkAttachmentLoadOp
    clazzInfo.storeOp = getstoreOp(); // Enum VkAttachmentStoreOp
    clazzInfo.stencilLoadOp = getstencilLoadOp(); // Enum VkAttachmentLoadOp
    clazzInfo.stencilStoreOp = getstencilStoreOp(); // Enum VkAttachmentStoreOp
    clazzInfo.initialLayout = getinitialLayout(); // Enum VkImageLayout
    clazzInfo.finalLayout = getfinalLayout(); // Enum VkImageLayout
}

VkAttachmentDescriptionAccessor::~VkAttachmentDescriptionAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

