/*
 *  VkSubpassDependencyAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkSubpassDependencyAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID srcSubpassField;
private:
    jfieldID dstSubpassField;
private:
    jfieldID srcStageMaskField;
private:
    jfieldID dstStageMaskField;
private:
    jfieldID srcAccessMaskField;
private:
    jfieldID dstAccessMaskField;
private:
    jfieldID dependencyFlagsField;
public:
    VkSubpassDependencyAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        srcSubpassField = env->GetFieldID(clazz, "srcSubpass", "I");
        dstSubpassField = env->GetFieldID(clazz, "dstSubpass", "I");
        srcStageMaskField = env->GetFieldID(clazz, "srcStageMask", "I");
        dstStageMaskField = env->GetFieldID(clazz, "dstStageMask", "I");
        srcAccessMaskField = env->GetFieldID(clazz, "srcAccessMask", "I");
        dstAccessMaskField = env->GetFieldID(clazz, "dstAccessMask", "I");
        dependencyFlagsField = env->GetFieldID(clazz, "dependencyFlags", "I");
    }

    uint32_t getsrcSubpass() {
        return (uint32_t) (jint) env->GetIntField(obj, srcSubpassField); // primitive
    }

    uint32_t getdstSubpass() {
        return (uint32_t) (jint) env->GetIntField(obj, dstSubpassField); // primitive
    }

    uint32_t getsrcStageMask() {
        return (uint32_t) (jint) env->GetIntField(obj, srcStageMaskField); // primitive
    }

    uint32_t getdstStageMask() {
        return (uint32_t) (jint) env->GetIntField(obj, dstStageMaskField); // primitive
    }

    uint32_t getsrcAccessMask() {
        return (uint32_t) (jint) env->GetIntField(obj, srcAccessMaskField); // primitive
    }

    uint32_t getdstAccessMask() {
        return (uint32_t) (jint) env->GetIntField(obj, dstAccessMaskField); // primitive
    }

    uint32_t getdependencyFlags() {
        return (uint32_t) (jint) env->GetIntField(obj, dependencyFlagsField); // primitive
    }

    void fromObject(VkSubpassDependency &clazzInfo) {
        clazzInfo.srcSubpass = getsrcSubpass(); // Object uint32_t
        clazzInfo.dstSubpass = getdstSubpass(); // Object uint32_t
        clazzInfo.srcStageMask = getsrcStageMask(); // Object uint32_t
        clazzInfo.dstStageMask = getdstStageMask(); // Object uint32_t
        clazzInfo.srcAccessMask = getsrcAccessMask(); // Object uint32_t
        clazzInfo.dstAccessMask = getdstAccessMask(); // Object uint32_t
        clazzInfo.dependencyFlags = getdependencyFlags(); // Object uint32_t
    }

    ~VkSubpassDependencyAccessor() {
    }

};
