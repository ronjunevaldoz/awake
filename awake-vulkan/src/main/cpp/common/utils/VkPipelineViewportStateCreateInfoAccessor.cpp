/*
 *  VkPipelineViewportStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
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
    VkPipelineViewportStateCreateInfoAccessor(JNIEnv *env, jobject &obj) {
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

    void getpNext(VkPipelineViewportStateCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    void getpViewports(VkPipelineViewportStateCreateInfo &clazzInfo) {
        auto pViewportsArray = (jobjectArray) env->GetObjectField(obj, pViewportsField);
        if (pViewportsArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pViewportsArray);
        std::vector<VkViewport> pViewports;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pViewportsArray,
                                                                i); // actual type is VkViewport[];
            // experimental optimize accessor
            VkViewportAccessor accessor(env, element);
            VkViewport ref{};
            accessor.fromObject(ref);
            pViewports.push_back(ref);
        }
        // processing
        auto viewportCount = static_cast<uint32_t>(pViewports.size());
        clazzInfo.viewportCount = viewportCount;
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkViewport[size];
        std::copy(pViewports.begin(), pViewports.end(), copy);
        clazzInfo.pViewports = copy;
    }

    void getpScissors(VkPipelineViewportStateCreateInfo &clazzInfo) {
        auto pScissorsArray = (jobjectArray) env->GetObjectField(obj, pScissorsField);
        if (pScissorsArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pScissorsArray);
        std::vector<VkRect2D> pScissors;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pScissorsArray,
                                                                i); // actual type is VkRect2D[];
            // experimental optimize accessor
            VkRect2DAccessor accessor(env, element);
            VkRect2D ref{};
            accessor.fromObject(ref);
            pScissors.push_back(ref);
        }
        // processing
        auto scissorCount = static_cast<uint32_t>(pScissors.size());
        clazzInfo.scissorCount = scissorCount;
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkRect2D[size];
        std::copy(pScissors.begin(), pScissors.end(), copy);
        clazzInfo.pScissors = copy;
    }

    void fromObject(VkPipelineViewportStateCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        getpViewports(clazzInfo);  // VkViewport Object Array
        getpScissors(clazzInfo);  // VkRect2D Object Array
    }

    ~VkPipelineViewportStateCreateInfoAccessor() {
    }

};
