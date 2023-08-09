/*
 *  VkViewportAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkViewportAccessor {
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
private:
    jfieldID widthField;
private:
    jfieldID heightField;
private:
    jfieldID minDepthField;
private:
    jfieldID maxDepthField;
public:
    VkViewportAccessor(JNIEnv *env, jobject obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        xField = env->GetFieldID(clazz, "x", "F");
        yField = env->GetFieldID(clazz, "y", "F");
        widthField = env->GetFieldID(clazz, "width", "F");
        heightField = env->GetFieldID(clazz, "height", "F");
        minDepthField = env->GetFieldID(clazz, "minDepth", "F");
        maxDepthField = env->GetFieldID(clazz, "maxDepth", "F");
    }

    float getx() {
        return (float) (jfloat) env->GetFloatField(obj, xField); // primitive
    }

    float gety() {
        return (float) (jfloat) env->GetFloatField(obj, yField); // primitive
    }

    float getwidth() {
        return (float) (jfloat) env->GetFloatField(obj, widthField); // primitive
    }

    float getheight() {
        return (float) (jfloat) env->GetFloatField(obj, heightField); // primitive
    }

    float getminDepth() {
        return (float) (jfloat) env->GetFloatField(obj, minDepthField); // primitive
    }

    float getmaxDepth() {
        return (float) (jfloat) env->GetFloatField(obj, maxDepthField); // primitive
    }

    VkViewport fromObject() {
        VkViewport clazzInfo{};
        clazzInfo.x = getx(); // Object
        clazzInfo.y = gety(); // Object
        clazzInfo.width = getwidth(); // Object
        clazzInfo.height = getheight(); // Object
        clazzInfo.minDepth = getminDepth(); // Object
        clazzInfo.maxDepth = getmaxDepth(); // Object
        return clazzInfo;
    }

    ~VkViewportAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
