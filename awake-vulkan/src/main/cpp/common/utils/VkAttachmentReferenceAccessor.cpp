/*
 *  VkAttachmentReferenceAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkAttachmentReferenceAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID attachmentField;
private:
    jfieldID layoutField;
public:
    VkAttachmentReferenceAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        attachmentField = env->GetFieldID(clazz, "attachment", "I");
        layoutField = env->GetFieldID(clazz, "layout",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkImageLayout;");
    }

    uint32_t getattachment() {
        return (uint32_t) (jint) env->GetIntField(obj, attachmentField); // primitive
    }

    VkImageLayout getlayout() {
        auto layoutEnum = (jobject) env->GetObjectField(obj, layoutField);
        return (VkImageLayout) enum_utils::getEnumFromObject(env, layoutEnum);
    }

    void fromObject(VkAttachmentReference &clazzInfo) {
        clazzInfo.attachment = getattachment(); // Object uint32_t
        clazzInfo.layout = getlayout(); // Enum VkImageLayout
    }

    ~VkAttachmentReferenceAccessor() {
    }

};
