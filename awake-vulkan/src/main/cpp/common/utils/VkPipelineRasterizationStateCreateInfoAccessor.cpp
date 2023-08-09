/*
 *  VkPipelineRasterizationStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
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
    VkPipelineRasterizationStateCreateInfoAccessor(JNIEnv *env, jobject obj) {
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

    void *getpNext() {
        return (void *) (jobject) env->GetObjectField(obj, pNextField); // Object??
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

    VkPipelineRasterizationStateCreateInfo fromObject() {
        VkPipelineRasterizationStateCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.depthClampEnable = getdepthClampEnable(); // Object
        clazzInfo.rasterizerDiscardEnable = getrasterizerDiscardEnable(); // Object
        clazzInfo.polygonMode = getpolygonMode(); // Object
        clazzInfo.cullMode = getcullMode(); // Object
        clazzInfo.frontFace = getfrontFace(); // Object
        clazzInfo.depthBiasEnable = getdepthBiasEnable(); // Object
        clazzInfo.depthBiasConstantFactor = getdepthBiasConstantFactor(); // Object
        clazzInfo.depthBiasClamp = getdepthBiasClamp(); // Object
        clazzInfo.depthBiasSlopeFactor = getdepthBiasSlopeFactor(); // Object
        clazzInfo.lineWidth = getlineWidth(); // Object
        return clazzInfo;
    }

    ~VkPipelineRasterizationStateCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
