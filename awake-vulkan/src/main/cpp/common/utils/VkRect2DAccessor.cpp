/*
 *  VkRect2DAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
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
    VkRect2DAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        offsetField = env->GetFieldID(clazz, "offset",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/models/VkOffset2D;");
        extentField = env->GetFieldID(clazz, "extent",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D;");
    }

    void getoffset(VkRect2D &clazzInfo) {
        auto offsetObj = (jobject) env->GetObjectField(obj, offsetField);
        if (offsetObj == nullptr) {
            return;
        }
        VkOffset2DAccessor accessor(env, offsetObj);
        VkOffset2D ref{};
        accessor.fromObject(ref);
        clazzInfo.offset = ref;
    }

    void getextent(VkRect2D &clazzInfo) {
        auto extentObj = (jobject) env->GetObjectField(obj, extentField);
        if (extentObj == nullptr) {
            return;
        }
        VkExtent2DAccessor accessor(env, extentObj);
        VkExtent2D ref{};
        accessor.fromObject(ref);
        clazzInfo.extent = ref;
    }

    void fromObject(VkRect2D &clazzInfo) {
        getoffset(clazzInfo); // Object VkOffset2D
        getextent(clazzInfo); // Object VkExtent2D
    }

    ~VkRect2DAccessor() {
    }

};
