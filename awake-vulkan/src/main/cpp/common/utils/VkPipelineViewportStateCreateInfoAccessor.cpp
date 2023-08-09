/*
 *  VkPipelineViewportStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkViewportAccessor.cpp>
#include <VkRect2DAccessor.cpp>

class VkPipelineViewportStateCreateInfoAccessor {
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
    jfieldID pViewportsField;
private:
    jfieldID pScissorsField;
public:
    VkPipelineViewportStateCreateInfoAccessor(JNIEnv *env, jobject obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        pViewportsField = env->GetFieldID(clazz, "pViewports",
                                          "[Lio/github/ronjunevaldoz/awake/vulkan/models/VkViewport;");
        pScissorsField = env->GetFieldID(clazz, "pScissors",
                                         "[Lio/github/ronjunevaldoz/awake/vulkan/models/VkRect2D;");
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

    std::vector<VkViewport> getpViewports() {
        auto pViewportsArray = (jobjectArray) env->GetObjectField(obj, pViewportsField);
        if (pViewportsArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pViewportsArray);
        std::vector<VkViewport> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pViewportsArray,
                                                                i); // actual type is VkViewport[];
            // experimental optimize accessor
            VkViewportAccessor accessor(env, element);
            array.push_back(accessor.fromObject());
        }
        return array;
    }

    std::vector<VkRect2D> getpScissors() {
        auto pScissorsArray = (jobjectArray) env->GetObjectField(obj, pScissorsField);
        if (pScissorsArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pScissorsArray);
        std::vector<VkRect2D> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pScissorsArray,
                                                                i); // actual type is VkRect2D[];
            // experimental optimize accessor
            VkRect2DAccessor accessor(env, element);
            array.push_back(accessor.fromObject());
        }
        return array;
    }

    VkPipelineViewportStateCreateInfo fromObject() {
        VkPipelineViewportStateCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.pViewports = getpViewports().data(); // Object Array
        clazzInfo.pScissors = getpScissors().data(); // Object Array
        return clazzInfo;
    }

    ~VkPipelineViewportStateCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
