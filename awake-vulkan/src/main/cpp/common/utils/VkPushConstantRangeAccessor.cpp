/*
 *  VkPushConstantRangeAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkPushConstantRangeAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID stageFlagsField;
private:
    jfieldID offsetField;
private:
    jfieldID sizeField;
public:
    VkPushConstantRangeAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        stageFlagsField = env->GetFieldID(clazz, "stageFlags", "I");
        offsetField = env->GetFieldID(clazz, "offset", "I");
        sizeField = env->GetFieldID(clazz, "size", "I");
    }

    uint32_t getstageFlags() {
        return (uint32_t) (jint) env->GetIntField(obj, stageFlagsField); // primitive
    }

    uint32_t getoffset() {
        return (uint32_t) (jint) env->GetIntField(obj, offsetField); // primitive
    }

    uint32_t getsize() {
        return (uint32_t) (jint) env->GetIntField(obj, sizeField); // primitive
    }

    void fromObject(VkPushConstantRange &clazzInfo) {
        clazzInfo.stageFlags = getstageFlags(); // Object uint32_t
        clazzInfo.offset = getoffset(); // Object uint32_t
        clazzInfo.size = getsize(); // Object uint32_t
    }

    ~VkPushConstantRangeAccessor() {
    }

};
