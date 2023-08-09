/*
 *  VkStencilOpStateAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkStencilOpStateAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID failOpField;
private:
    jfieldID passOpField;
private:
    jfieldID depthFailOpField;
private:
    jfieldID compareOpField;
private:
    jfieldID compareMaskField;
private:
    jfieldID writeMaskField;
private:
    jfieldID referenceField;
public:
    VkStencilOpStateAccessor(JNIEnv *env, jobject obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        failOpField = env->GetFieldID(clazz, "failOp",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStencilOp;");
        passOpField = env->GetFieldID(clazz, "passOp",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStencilOp;");
        depthFailOpField = env->GetFieldID(clazz, "depthFailOp",
                                           "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStencilOp;");
        compareOpField = env->GetFieldID(clazz, "compareOp",
                                         "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkCompareOp;");
        compareMaskField = env->GetFieldID(clazz, "compareMask", "I");
        writeMaskField = env->GetFieldID(clazz, "writeMask", "I");
        referenceField = env->GetFieldID(clazz, "reference", "I");
    }

    VkStencilOp getfailOp() {
        auto failOpEnum = (jobject) env->GetObjectField(obj, failOpField);
        return (VkStencilOp) enum_utils::getEnumFromObject(env, failOpEnum);
    }

    VkStencilOp getpassOp() {
        auto passOpEnum = (jobject) env->GetObjectField(obj, passOpField);
        return (VkStencilOp) enum_utils::getEnumFromObject(env, passOpEnum);
    }

    VkStencilOp getdepthFailOp() {
        auto depthFailOpEnum = (jobject) env->GetObjectField(obj, depthFailOpField);
        return (VkStencilOp) enum_utils::getEnumFromObject(env, depthFailOpEnum);
    }

    VkCompareOp getcompareOp() {
        auto compareOpEnum = (jobject) env->GetObjectField(obj, compareOpField);
        return (VkCompareOp) enum_utils::getEnumFromObject(env, compareOpEnum);
    }

    uint32_t getcompareMask() {
        return (uint32_t) (jint) env->GetIntField(obj, compareMaskField); // primitive
    }

    uint32_t getwriteMask() {
        return (uint32_t) (jint) env->GetIntField(obj, writeMaskField); // primitive
    }

    uint32_t getreference() {
        return (uint32_t) (jint) env->GetIntField(obj, referenceField); // primitive
    }

    VkStencilOpState fromObject() {
        VkStencilOpState clazzInfo{};
        clazzInfo.failOp = getfailOp(); // Object
        clazzInfo.passOp = getpassOp(); // Object
        clazzInfo.depthFailOp = getdepthFailOp(); // Object
        clazzInfo.compareOp = getcompareOp(); // Object
        clazzInfo.compareMask = getcompareMask(); // Object
        clazzInfo.writeMask = getwriteMask(); // Object
        clazzInfo.reference = getreference(); // Object
        return clazzInfo;
    }

    ~VkStencilOpStateAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
