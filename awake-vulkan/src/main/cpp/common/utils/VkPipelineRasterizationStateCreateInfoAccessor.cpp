/*
 *  VkPipelineRasterizationStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkPipelineRasterizationStateCreateInfoAccessor {
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
    jfieldID depthClampEnableField;
private:
    jfieldID rasterizerDiscardEnableField;
private:
    jfieldID polygonModeField;
private:
    jfieldID cullModeField;
private:
    jfieldID frontFaceField;
private:
    jfieldID depthBiasEnableField;
private:
    jfieldID depthBiasConstantFactorField;
private:
    jfieldID depthBiasClampField;
private:
    jfieldID depthBiasSlopeFactorField;
private:
    jfieldID lineWidthField;
public:
    VkPipelineRasterizationStateCreateInfoAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        depthClampEnableField = env->GetFieldID(clazz, "depthClampEnable", "Z");
        rasterizerDiscardEnableField = env->GetFieldID(clazz, "rasterizerDiscardEnable", "Z");
        polygonModeField = env->GetFieldID(clazz, "polygonMode",
                                           "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkPolygonMode;");
        cullModeField = env->GetFieldID(clazz, "cullMode", "I");
        frontFaceField = env->GetFieldID(clazz, "frontFace",
                                         "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFrontFace;");
        depthBiasEnableField = env->GetFieldID(clazz, "depthBiasEnable", "Z");
        depthBiasConstantFactorField = env->GetFieldID(clazz, "depthBiasConstantFactor", "F");
        depthBiasClampField = env->GetFieldID(clazz, "depthBiasClamp", "F");
        depthBiasSlopeFactorField = env->GetFieldID(clazz, "depthBiasSlopeFactor", "F");
        lineWidthField = env->GetFieldID(clazz, "lineWidth", "F");
    }

    VkStructureType getsType() {
        auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
        return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    }

    void getpNext(VkPipelineRasterizationStateCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    bool getdepthClampEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj, depthClampEnableField); // primitive
    }

    bool getrasterizerDiscardEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      rasterizerDiscardEnableField); // primitive
    }

    VkPolygonMode getpolygonMode() {
        auto polygonModeEnum = (jobject) env->GetObjectField(obj, polygonModeField);
        return (VkPolygonMode) enum_utils::getEnumFromObject(env, polygonModeEnum);
    }

    uint32_t getcullMode() {
        return (uint32_t) (jint) env->GetIntField(obj, cullModeField); // primitive
    }

    VkFrontFace getfrontFace() {
        auto frontFaceEnum = (jobject) env->GetObjectField(obj, frontFaceField);
        return (VkFrontFace) enum_utils::getEnumFromObject(env, frontFaceEnum);
    }

    bool getdepthBiasEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj, depthBiasEnableField); // primitive
    }

    float getdepthBiasConstantFactor() {
        return (float) (jfloat) env->GetFloatField(obj, depthBiasConstantFactorField); // primitive
    }

    float getdepthBiasClamp() {
        return (float) (jfloat) env->GetFloatField(obj, depthBiasClampField); // primitive
    }

    float getdepthBiasSlopeFactor() {
        return (float) (jfloat) env->GetFloatField(obj, depthBiasSlopeFactorField); // primitive
    }

    float getlineWidth() {
        return (float) (jfloat) env->GetFloatField(obj, lineWidthField); // primitive
    }

    void fromObject(VkPipelineRasterizationStateCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        clazzInfo.depthClampEnable = getdepthClampEnable(); // Object bool
        clazzInfo.rasterizerDiscardEnable = getrasterizerDiscardEnable(); // Object bool
        clazzInfo.polygonMode = getpolygonMode(); // Enum VkPolygonMode
        clazzInfo.cullMode = getcullMode(); // Object uint32_t
        clazzInfo.frontFace = getfrontFace(); // Enum VkFrontFace
        clazzInfo.depthBiasEnable = getdepthBiasEnable(); // Object bool
        clazzInfo.depthBiasConstantFactor = getdepthBiasConstantFactor(); // Object float
        clazzInfo.depthBiasClamp = getdepthBiasClamp(); // Object float
        clazzInfo.depthBiasSlopeFactor = getdepthBiasSlopeFactor(); // Object float
        clazzInfo.lineWidth = getlineWidth(); // Object float
    }

    ~VkPipelineRasterizationStateCreateInfoAccessor() {
    }

};
