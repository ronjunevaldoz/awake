/*
 *  VkAttachmentReferenceAccessor.cpp
 *  Vulkan accessor for VkAttachmentReference
 *  Created by Ron June Valdoz */

#include  <includes/VkAttachmentReferenceAccessor.h>

VkAttachmentReferenceAccessor::VkAttachmentReferenceAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    attachmentField = env->GetFieldID(clazz, "attachment", "I");
    layoutField = env->GetFieldID(clazz, "layout",
                                  "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkImageLayout;");
}

void
VkAttachmentReferenceAccessor::fromObject(VkAttachmentReference &clazzInfo) {
    clazzInfo.attachment = getattachment(); // Object uint32_t
    clazzInfo.layout = getlayout(); // Enum VkImageLayout
}

VkImageLayout
VkAttachmentReferenceAccessor::getlayout() {
    auto layoutEnum = (jobject) env->GetObjectField(obj, layoutField);
    return (VkImageLayout) enum_utils::getEnumFromObject(env, layoutEnum);
}

uint32_t
VkAttachmentReferenceAccessor::getattachment() {
    return (uint32_t)(jint)
    env->GetIntField(obj, attachmentField); // primitive
}

VkAttachmentReferenceAccessor::~VkAttachmentReferenceAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

