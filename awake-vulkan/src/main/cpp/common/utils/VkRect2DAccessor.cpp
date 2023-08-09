/*
 *  VkRect2DAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkOffset2DAccessor.cpp>
#include <VkExtent2DAccessor.cpp>

class VkRect2DAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID offsetField;
private:
    jfieldID extentField;
public:
    VkRect2DAccessor(JNIEnv *env, jobject obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        offsetField = env->GetFieldID(clazz, "offset",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/models/VkOffset2D;");
        extentField = env->GetFieldID(clazz, "extent",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D;");
    }

    VkOffset2D getoffset() {
        auto offsetObj = (jobject) env->GetObjectField(obj, offsetField);
        VkOffset2DAccessor accessor(env, offsetObj);
        if (offsetObj == nullptr) {
            return {};
        }
        return (VkOffset2D) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    VkExtent2D getextent() {
        auto extentObj = (jobject) env->GetObjectField(obj, extentField);
        VkExtent2DAccessor accessor(env, extentObj);
        if (extentObj == nullptr) {
            return {};
        }
        return (VkExtent2D) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    VkRect2D fromObject() {
        VkRect2D clazzInfo{};
        clazzInfo.offset = getoffset(); // Object
        clazzInfo.extent = getextent(); // Object
        return clazzInfo;
    }

    ~VkRect2DAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
