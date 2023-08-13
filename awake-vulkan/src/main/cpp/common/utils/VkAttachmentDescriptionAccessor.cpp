/*
 *  VkAttachmentDescriptionAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkAttachmentDescriptionAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID flagsField;
private:
    jfieldID formatField;
private:
    jfieldID samplesField;
private:
    jfieldID loadOpField;
private:
    jfieldID storeOpField;
private:
    jfieldID stencilLoadOpField;
private:
    jfieldID stencilStoreOpField;
private:
    jfieldID initialLayoutField;
private:
    jfieldID finalLayoutField;
public:
    VkAttachmentDescriptionAccessor(JNIEnv *env, jobject &obj) {
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

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    VkFormat getformat() {
        auto formatEnum = (jobject) env->GetObjectField(obj, formatField);
        return (VkFormat) enum_utils::getEnumFromObject(env, formatEnum);
    }

    VkSampleCountFlagBits getsamples() {
        auto samplesEnum = (jobject) env->GetObjectField(obj, samplesField);
        return (VkSampleCountFlagBits) enum_utils::getEnumFromObject(env, samplesEnum);
    }

    VkAttachmentLoadOp getloadOp() {
        auto loadOpEnum = (jobject) env->GetObjectField(obj, loadOpField);
        return (VkAttachmentLoadOp) enum_utils::getEnumFromObject(env, loadOpEnum);
    }

    VkAttachmentStoreOp getstoreOp() {
        auto storeOpEnum = (jobject) env->GetObjectField(obj, storeOpField);
        return (VkAttachmentStoreOp) enum_utils::getEnumFromObject(env, storeOpEnum);
    }

    VkAttachmentLoadOp getstencilLoadOp() {
        auto stencilLoadOpEnum = (jobject) env->GetObjectField(obj, stencilLoadOpField);
        return (VkAttachmentLoadOp) enum_utils::getEnumFromObject(env, stencilLoadOpEnum);
    }

    VkAttachmentStoreOp getstencilStoreOp() {
        auto stencilStoreOpEnum = (jobject) env->GetObjectField(obj, stencilStoreOpField);
        return (VkAttachmentStoreOp) enum_utils::getEnumFromObject(env, stencilStoreOpEnum);
    }

    VkImageLayout getinitialLayout() {
        auto initialLayoutEnum = (jobject) env->GetObjectField(obj, initialLayoutField);
        return (VkImageLayout) enum_utils::getEnumFromObject(env, initialLayoutEnum);
    }

    VkImageLayout getfinalLayout() {
        auto finalLayoutEnum = (jobject) env->GetObjectField(obj, finalLayoutField);
        return (VkImageLayout) enum_utils::getEnumFromObject(env, finalLayoutEnum);
    }

    void fromObject(VkAttachmentDescription &clazzInfo) {
        clazzInfo.flags = getflags(); // Object uint32_t
        clazzInfo.format = getformat(); // Enum VkFormat
        clazzInfo.samples = getsamples(); // Enum VkSampleCountFlagBits
        clazzInfo.loadOp = getloadOp(); // Enum VkAttachmentLoadOp
        clazzInfo.storeOp = getstoreOp(); // Enum VkAttachmentStoreOp
        clazzInfo.stencilLoadOp = getstencilLoadOp(); // Enum VkAttachmentLoadOp
        clazzInfo.stencilStoreOp = getstencilStoreOp(); // Enum VkAttachmentStoreOp
        clazzInfo.initialLayout = getinitialLayout(); // Enum VkImageLayout
        clazzInfo.finalLayout = getfinalLayout(); // Enum VkImageLayout
    }

    ~VkAttachmentDescriptionAccessor() {
    }

};
