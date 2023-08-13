/*
 *  VkVertexInputBindingDescriptionAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkVertexInputBindingDescriptionAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID bindingField;
private:
    jfieldID strideField;
private:
    jfieldID inputRateField;
public:
    VkVertexInputBindingDescriptionAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        bindingField = env->GetFieldID(clazz, "binding", "I");
        strideField = env->GetFieldID(clazz, "stride", "I");
        inputRateField = env->GetFieldID(clazz, "inputRate",
                                         "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkVertexInputRate;");
    }

    uint32_t getbinding() {
        return (uint32_t) (jint) env->GetIntField(obj, bindingField); // primitive
    }

    uint32_t getstride() {
        return (uint32_t) (jint) env->GetIntField(obj, strideField); // primitive
    }

    VkVertexInputRate getinputRate() {
        auto inputRateEnum = (jobject) env->GetObjectField(obj, inputRateField);
        return (VkVertexInputRate) enum_utils::getEnumFromObject(env, inputRateEnum);
    }

    void fromObject(VkVertexInputBindingDescription &clazzInfo) {
        clazzInfo.binding = getbinding(); // Object uint32_t
        clazzInfo.stride = getstride(); // Object uint32_t
        clazzInfo.inputRate = getinputRate(); // Enum VkVertexInputRate
    }

    ~VkVertexInputBindingDescriptionAccessor() {
    }

};
