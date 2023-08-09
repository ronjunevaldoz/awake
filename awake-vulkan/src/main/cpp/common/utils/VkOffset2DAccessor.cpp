/*
 *  VkOffset2DAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkOffset2DAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID xField;
private:
    jfieldID yField;
public:
    VkOffset2DAccessor(JNIEnv *env, jobject obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        xField = env->GetFieldID(clazz, "x", "I");
        yField = env->GetFieldID(clazz, "y", "I");
    }

    uint32_t getx() {
        return (uint32_t) (jint) env->GetIntField(obj, xField); // primitive
    }

    uint32_t gety() {
        return (uint32_t) (jint) env->GetIntField(obj, yField); // primitive
    }

    VkOffset2D fromObject() {
        VkOffset2D clazzInfo{};
        clazzInfo.x = getx(); // Object
        clazzInfo.y = gety(); // Object
        return clazzInfo;
    }

    ~VkOffset2DAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
