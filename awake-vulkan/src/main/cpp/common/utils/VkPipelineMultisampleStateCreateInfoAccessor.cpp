/*
 *  VkPipelineMultisampleStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkPipelineMultisampleStateCreateInfoAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID sTypeField;
private:
    jfieldID pNextField;
private:
    jfieldID flagsField;
private:
    jfieldID rasterizationSamplesField;
private:
    jfieldID sampleShadingEnableField;
private:
    jfieldID minSampleShadingField;
private:
    jfieldID pSampleMaskField;
private:
    jfieldID alphaToCoverageEnableField;
private:
    jfieldID alphaToOneEnableField;
public:
    VkPipelineMultisampleStateCreateInfoAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        rasterizationSamplesField = env->GetFieldID(clazz, "rasterizationSamples",
                                                    "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkSampleCountFlagBits;");
        sampleShadingEnableField = env->GetFieldID(clazz, "sampleShadingEnable", "Z");
        minSampleShadingField = env->GetFieldID(clazz, "minSampleShading", "F");
        pSampleMaskField = env->GetFieldID(clazz, "pSampleMask", "I");
        alphaToCoverageEnableField = env->GetFieldID(clazz, "alphaToCoverageEnable", "Z");
        alphaToOneEnableField = env->GetFieldID(clazz, "alphaToOneEnable", "Z");
    }

    VkStructureType getsType() {
        auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
        return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    }

    void getpNext(VkPipelineMultisampleStateCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    VkSampleCountFlagBits getrasterizationSamples() {
        auto rasterizationSamplesEnum = (jobject) env->GetObjectField(obj,
                                                                      rasterizationSamplesField);
        return (VkSampleCountFlagBits) enum_utils::getEnumFromObject(env, rasterizationSamplesEnum);
    }

    bool getsampleShadingEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj, sampleShadingEnableField); // primitive
    }

    float getminSampleShading() {
        return (float) (jfloat) env->GetFloatField(obj, minSampleShadingField); // primitive
    }

    void getpSampleMask(VkPipelineMultisampleStateCreateInfo &clazzInfo) {
        auto ptr = (uint32_t) env->GetIntField(obj, pSampleMaskField); // Primitive Pointer
        clazzInfo.pSampleMask = &ptr; // Primitive Pointer
    }

    bool getalphaToCoverageEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj, alphaToCoverageEnableField); // primitive
    }

    bool getalphaToOneEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj, alphaToOneEnableField); // primitive
    }

    void fromObject(VkPipelineMultisampleStateCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        clazzInfo.rasterizationSamples = getrasterizationSamples(); // Enum VkSampleCountFlagBits
        clazzInfo.sampleShadingEnable = getsampleShadingEnable(); // Object bool
        clazzInfo.minSampleShading = getminSampleShading(); // Object float
        getpSampleMask(clazzInfo); // Pointer
        clazzInfo.alphaToCoverageEnable = getalphaToCoverageEnable(); // Object bool
        clazzInfo.alphaToOneEnable = getalphaToOneEnable(); // Object bool
    }

    ~VkPipelineMultisampleStateCreateInfoAccessor() {
    }

};
