/*
 *  VkPipelineDynamicStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

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
    VkPipelineDynamicStateCreateInfoAccessor(JNIEnv *env, jobject &obj) {
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

    void getpNext(VkPipelineDynamicStateCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    void getpDynamicStates(VkPipelineDynamicStateCreateInfo &clazzInfo) {
        auto pDynamicStatesArray = (jobjectArray) env->GetObjectField(obj, pDynamicStatesField);
        if (pDynamicStatesArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pDynamicStatesArray);
        std::vector<VkDynamicState> pDynamicStates;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pDynamicStatesArray,
                                                                i); // actual type is VkDynamicState[];
            pDynamicStates.push_back(static_cast<VkDynamicState>(enum_utils::getEnumFromObject(env,
                                                                                               element))); // type is enum
        }
        // processing
        auto dynamicStateCount = static_cast<uint32_t>(pDynamicStates.size());
        clazzInfo.dynamicStateCount = dynamicStateCount;
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkDynamicState[size];
        std::copy(pDynamicStates.begin(), pDynamicStates.end(), copy);
        clazzInfo.pDynamicStates = copy;
    }

    void fromObject(VkPipelineDynamicStateCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        getpDynamicStates(clazzInfo);  // VkDynamicState Object Array
    }

    ~VkPipelineDynamicStateCreateInfoAccessor() {
    }

};
