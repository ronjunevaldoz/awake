/*
 *  VkExtent2DAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkExtent2DAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID widthField;
private:
    jfieldID heightField;
public:
    VkExtent2DAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        widthField = env->GetFieldID(clazz, "width", "I");
        heightField = env->GetFieldID(clazz, "height", "I");
    }

    uint32_t getwidth() {
        return (uint32_t) (jint) env->GetIntField(obj, widthField); // primitive
    }

    uint32_t getheight() {
        return (uint32_t) (jint) env->GetIntField(obj, heightField); // primitive
    }

    void fromObject(VkExtent2D &clazzInfo) {
        clazzInfo.width = getwidth(); // Object uint32_t
        clazzInfo.height = getheight(); // Object uint32_t
    }

    ~VkExtent2DAccessor() {
    }

};
