/*
 *  VkPipelineDepthStencilStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkStencilOpStateAccessor.cpp>

class VkPipelineDepthStencilStateCreateInfoAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID sTypeField;
private:
    jfieldID pNextField;
private:
    jfieldID flagsField;
private:
    jfieldID depthTestEnableField;
private:
    jfieldID depthWriteEnableField;
private:
    jfieldID depthCompareOpField;
private:
    jfieldID depthBoundsTestEnableField;
private:
    jfieldID stencilTestEnableField;
private:
    jfieldID frontField;
private:
    jfieldID backField;
private:
    jfieldID minDepthBoundsField;
private:
    jfieldID maxDepthBoundsField;
public:
    VkPipelineDepthStencilStateCreateInfoAccessor(JNIEnv *env, jobject obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        depthTestEnableField = env->GetFieldID(clazz, "depthTestEnable", "Z");
        depthWriteEnableField = env->GetFieldID(clazz, "depthWriteEnable", "Z");
        depthCompareOpField = env->GetFieldID(clazz, "depthCompareOp",
                                              "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkCompareOp;");
        depthBoundsTestEnableField = env->GetFieldID(clazz, "depthBoundsTestEnable", "Z");
        stencilTestEnableField = env->GetFieldID(clazz, "stencilTestEnable", "Z");
        frontField = env->GetFieldID(clazz, "front",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/models/VkStencilOpState;");
        backField = env->GetFieldID(clazz, "back",
                                    "Lio/github/ronjunevaldoz/awake/vulkan/models/VkStencilOpState;");
        minDepthBoundsField = env->GetFieldID(clazz, "minDepthBounds", "F");
        maxDepthBoundsField = env->GetFieldID(clazz, "maxDepthBounds", "F");
    }

    VkStructureType getsType() {
        auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
        return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    }

    void *getpNext() {
        return (void *) (jobject) env->GetObjectField(obj, pNextField); // Object??
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    bool getdepthTestEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj, depthTestEnableField); // primitive
    }

    bool getdepthWriteEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj, depthWriteEnableField); // primitive
    }

    VkCompareOp getdepthCompareOp() {
        auto depthCompareOpEnum = (jobject) env->GetObjectField(obj, depthCompareOpField);
        return (VkCompareOp) enum_utils::getEnumFromObject(env, depthCompareOpEnum);
    }

    bool getdepthBoundsTestEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj, depthBoundsTestEnableField); // primitive
    }

    bool getstencilTestEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj, stencilTestEnableField); // primitive
    }

    VkStencilOpState getfront() {
        auto frontObj = (jobject) env->GetObjectField(obj, frontField);
        VkStencilOpStateAccessor accessor(env, frontObj);
        if (frontObj == nullptr) {
            return {};
        }
        return (VkStencilOpState) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    VkStencilOpState getback() {
        auto backObj = (jobject) env->GetObjectField(obj, backField);
        VkStencilOpStateAccessor accessor(env, backObj);
        if (backObj == nullptr) {
            return {};
        }
        return (VkStencilOpState) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    float getminDepthBounds() {
        return (float) (jfloat) env->GetFloatField(obj, minDepthBoundsField); // primitive
    }

    float getmaxDepthBounds() {
        return (float) (jfloat) env->GetFloatField(obj, maxDepthBoundsField); // primitive
    }

    VkPipelineDepthStencilStateCreateInfo fromObject() {
        VkPipelineDepthStencilStateCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.depthTestEnable = getdepthTestEnable(); // Object
        clazzInfo.depthWriteEnable = getdepthWriteEnable(); // Object
        clazzInfo.depthCompareOp = getdepthCompareOp(); // Object
        clazzInfo.depthBoundsTestEnable = getdepthBoundsTestEnable(); // Object
        clazzInfo.stencilTestEnable = getstencilTestEnable(); // Object
        clazzInfo.front = getfront(); // Object
        clazzInfo.back = getback(); // Object
        clazzInfo.minDepthBounds = getminDepthBounds(); // Object
        clazzInfo.maxDepthBounds = getmaxDepthBounds(); // Object
        return clazzInfo;
    }

    ~VkPipelineDepthStencilStateCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
