/*
 *  VkVertexInputAttributeDescriptionAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkVertexInputAttributeDescriptionAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID locationField;
private:
    jfieldID bindingField;
private:
    jfieldID formatField;
private:
    jfieldID offsetField;
public:
    VkVertexInputAttributeDescriptionAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        locationField = env->GetFieldID(clazz, "location", "I");
        bindingField = env->GetFieldID(clazz, "binding", "I");
        formatField = env->GetFieldID(clazz, "format",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFormat;");
        offsetField = env->GetFieldID(clazz, "offset", "I");
    }

    uint32_t getlocation() {
        return (uint32_t) (jint) env->GetIntField(obj, locationField); // primitive
    }

    uint32_t getbinding() {
        return (uint32_t) (jint) env->GetIntField(obj, bindingField); // primitive
    }

    VkFormat getformat() {
        auto formatEnum = (jobject) env->GetObjectField(obj, formatField);
        return (VkFormat) enum_utils::getEnumFromObject(env, formatEnum);
    }

    uint32_t getoffset() {
        return (uint32_t) (jint) env->GetIntField(obj, offsetField); // primitive
    }

    void fromObject(VkVertexInputAttributeDescription &clazzInfo) {
        clazzInfo.location = getlocation(); // Object uint32_t
        clazzInfo.binding = getbinding(); // Object uint32_t
        clazzInfo.format = getformat(); // Enum VkFormat
        clazzInfo.offset = getoffset(); // Object uint32_t
    }

    ~VkVertexInputAttributeDescriptionAccessor() {
    }

};
