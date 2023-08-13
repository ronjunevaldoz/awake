/*
 *  VkPipelineColorBlendAttachmentStateAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkPipelineColorBlendAttachmentStateAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID blendEnableField;
private:
    jfieldID srcColorBlendFactorField;
private:
    jfieldID dstColorBlendFactorField;
private:
    jfieldID colorBlendOpField;
private:
    jfieldID srcAlphaBlendFactorField;
private:
    jfieldID dstAlphaBlendFactorField;
private:
    jfieldID alphaBlendOpField;
private:
    jfieldID colorWriteMaskField;
public:
    VkPipelineColorBlendAttachmentStateAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        blendEnableField = env->GetFieldID(clazz, "blendEnable", "Z");
        srcColorBlendFactorField = env->GetFieldID(clazz, "srcColorBlendFactor",
                                                   "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendFactor;");
        dstColorBlendFactorField = env->GetFieldID(clazz, "dstColorBlendFactor",
                                                   "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendFactor;");
        colorBlendOpField = env->GetFieldID(clazz, "colorBlendOp",
                                            "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendOp;");
        srcAlphaBlendFactorField = env->GetFieldID(clazz, "srcAlphaBlendFactor",
                                                   "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendFactor;");
        dstAlphaBlendFactorField = env->GetFieldID(clazz, "dstAlphaBlendFactor",
                                                   "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendFactor;");
        alphaBlendOpField = env->GetFieldID(clazz, "alphaBlendOp",
                                            "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkBlendOp;");
        colorWriteMaskField = env->GetFieldID(clazz, "colorWriteMask", "I");
    }

    bool getblendEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj, blendEnableField); // primitive
    }

    VkBlendFactor getsrcColorBlendFactor() {
        auto srcColorBlendFactorEnum = (jobject) env->GetObjectField(obj, srcColorBlendFactorField);
        return (VkBlendFactor) enum_utils::getEnumFromObject(env, srcColorBlendFactorEnum);
    }

    VkBlendFactor getdstColorBlendFactor() {
        auto dstColorBlendFactorEnum = (jobject) env->GetObjectField(obj, dstColorBlendFactorField);
        return (VkBlendFactor) enum_utils::getEnumFromObject(env, dstColorBlendFactorEnum);
    }

    VkBlendOp getcolorBlendOp() {
        auto colorBlendOpEnum = (jobject) env->GetObjectField(obj, colorBlendOpField);
        return (VkBlendOp) enum_utils::getEnumFromObject(env, colorBlendOpEnum);
    }

    VkBlendFactor getsrcAlphaBlendFactor() {
        auto srcAlphaBlendFactorEnum = (jobject) env->GetObjectField(obj, srcAlphaBlendFactorField);
        return (VkBlendFactor) enum_utils::getEnumFromObject(env, srcAlphaBlendFactorEnum);
    }

    VkBlendFactor getdstAlphaBlendFactor() {
        auto dstAlphaBlendFactorEnum = (jobject) env->GetObjectField(obj, dstAlphaBlendFactorField);
        return (VkBlendFactor) enum_utils::getEnumFromObject(env, dstAlphaBlendFactorEnum);
    }

    VkBlendOp getalphaBlendOp() {
        auto alphaBlendOpEnum = (jobject) env->GetObjectField(obj, alphaBlendOpField);
        return (VkBlendOp) enum_utils::getEnumFromObject(env, alphaBlendOpEnum);
    }

    uint32_t getcolorWriteMask() {
        return (uint32_t) (jint) env->GetIntField(obj, colorWriteMaskField); // primitive
    }

    void fromObject(VkPipelineColorBlendAttachmentState &clazzInfo) {
        clazzInfo.blendEnable = getblendEnable(); // Object bool
        clazzInfo.srcColorBlendFactor = getsrcColorBlendFactor(); // Enum VkBlendFactor
        clazzInfo.dstColorBlendFactor = getdstColorBlendFactor(); // Enum VkBlendFactor
        clazzInfo.colorBlendOp = getcolorBlendOp(); // Enum VkBlendOp
        clazzInfo.srcAlphaBlendFactor = getsrcAlphaBlendFactor(); // Enum VkBlendFactor
        clazzInfo.dstAlphaBlendFactor = getdstAlphaBlendFactor(); // Enum VkBlendFactor
        clazzInfo.alphaBlendOp = getalphaBlendOp(); // Enum VkBlendOp
        clazzInfo.colorWriteMask = getcolorWriteMask(); // Object uint32_t
    }

    ~VkPipelineColorBlendAttachmentStateAccessor() {
    }

};
