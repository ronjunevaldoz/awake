/*
 *  VkExtent2DAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
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
    VkExtent2DAccessor(JNIEnv *env, jobject obj) {
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

    VkExtent2D fromObject() {
        VkExtent2D clazzInfo{};
        clazzInfo.width = getwidth(); // Object
        clazzInfo.height = getheight(); // Object
        return clazzInfo;
    }

    ~VkExtent2DAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
