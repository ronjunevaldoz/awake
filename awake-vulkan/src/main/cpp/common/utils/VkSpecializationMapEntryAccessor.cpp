/*
 *  VkSpecializationMapEntryAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkSpecializationMapEntryAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID constantIDField;
private:
    jfieldID offsetField;
private:
    jfieldID sizeField;
public:
    VkSpecializationMapEntryAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        constantIDField = env->GetFieldID(clazz, "constantID", "I");
        offsetField = env->GetFieldID(clazz, "offset", "I");
        sizeField = env->GetFieldID(clazz, "size", "J");
    }

    uint32_t getconstantID() {
        return (uint32_t) (jint) env->GetIntField(obj, constantIDField); // primitive
    }

    uint32_t getoffset() {
        return (uint32_t) (jint) env->GetIntField(obj, offsetField); // primitive
    }

    uint64_t getsize() {
        return (uint64_t) (jlong) env->GetLongField(obj, sizeField); // primitive
    }

    void fromObject(VkSpecializationMapEntry &clazzInfo) {
        clazzInfo.constantID = getconstantID(); // Object uint32_t
        clazzInfo.offset = getoffset(); // Object uint32_t
        clazzInfo.size = getsize(); // Object uint64_t
    }

    ~VkSpecializationMapEntryAccessor() {
    }

};
