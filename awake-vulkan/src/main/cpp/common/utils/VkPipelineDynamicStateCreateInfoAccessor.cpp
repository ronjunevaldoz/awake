/*
 *  VkPipelineDynamicStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkDynamicStateAccessor.cpp>

class VkPipelineDynamicStateCreateInfoAccessor {
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
    jfieldID pDynamicStatesField;
public:
    VkPipelineDynamicStateCreateInfoAccessor(JNIEnv *env, jobject obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        pDynamicStatesField = env->GetFieldID(clazz, "pDynamicStates",
                                              "[Lio/github/ronjunevaldoz/awake/vulkan/enums/VkDynamicState;");
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

    std::vector<VkDynamicState> getpDynamicStates() {
        auto pDynamicStatesArray = (jobjectArray) env->GetObjectField(obj, pDynamicStatesField);
        if (pDynamicStatesArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pDynamicStatesArray);
        std::vector<VkDynamicState> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pDynamicStatesArray,
                                                                i); // actual type is VkDynamicState[];
            // experimental optimize accessor
            VkDynamicStateAccessor accessor(env, element);
            array.push_back(accessor.fromObject());
        }
        return array;
    }

    VkPipelineDynamicStateCreateInfo fromObject() {
        VkPipelineDynamicStateCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.pDynamicStates = getpDynamicStates().data(); // Object Array
        return clazzInfo;
    }

    ~VkPipelineDynamicStateCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
