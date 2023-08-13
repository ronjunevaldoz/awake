/*
 *  VkPipelineVertexInputStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkVertexInputBindingDescriptionAccessor.cpp>
#include <VkVertexInputAttributeDescriptionAccessor.cpp>

class VkPipelineVertexInputStateCreateInfoAccessor {
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
    jfieldID pVertexBindingDescriptionsField;
private:
    jfieldID pVertexAttributeDescriptionsField;
public:
    VkPipelineVertexInputStateCreateInfoAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        pVertexBindingDescriptionsField = env->GetFieldID(clazz, "pVertexBindingDescriptions",
                                                          "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkVertexInputBindingDescription;");
        pVertexAttributeDescriptionsField = env->GetFieldID(clazz, "pVertexAttributeDescriptions",
                                                            "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkVertexInputAttributeDescription;");
    }

    VkStructureType getsType() {
        auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
        return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    }

    void getpNext(VkPipelineVertexInputStateCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    void getpVertexBindingDescriptions(VkPipelineVertexInputStateCreateInfo &clazzInfo) {
        auto pVertexBindingDescriptionsArray = (jobjectArray) env->GetObjectField(obj,
                                                                                  pVertexBindingDescriptionsField);
        if (pVertexBindingDescriptionsArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pVertexBindingDescriptionsArray);
        std::vector<VkVertexInputBindingDescription> pVertexBindingDescriptions;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pVertexBindingDescriptionsArray,
                                                                i); // actual type is VkVertexInputBindingDescription[];
            // experimental optimize accessor
            VkVertexInputBindingDescriptionAccessor accessor(env, element);
            VkVertexInputBindingDescription ref{};
            accessor.fromObject(ref);
            pVertexBindingDescriptions.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkVertexInputBindingDescription[size];
        std::copy(pVertexBindingDescriptions.begin(), pVertexBindingDescriptions.end(), copy);
        clazzInfo.pVertexBindingDescriptions = copy;
    }

    void getpVertexAttributeDescriptions(VkPipelineVertexInputStateCreateInfo &clazzInfo) {
        auto pVertexAttributeDescriptionsArray = (jobjectArray) env->GetObjectField(obj,
                                                                                    pVertexAttributeDescriptionsField);
        if (pVertexAttributeDescriptionsArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pVertexAttributeDescriptionsArray);
        std::vector<VkVertexInputAttributeDescription> pVertexAttributeDescriptions;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pVertexAttributeDescriptionsArray,
                                                                i); // actual type is VkVertexInputAttributeDescription[];
            // experimental optimize accessor
            VkVertexInputAttributeDescriptionAccessor accessor(env, element);
            VkVertexInputAttributeDescription ref{};
            accessor.fromObject(ref);
            pVertexAttributeDescriptions.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkVertexInputAttributeDescription[size];
        std::copy(pVertexAttributeDescriptions.begin(), pVertexAttributeDescriptions.end(), copy);
        clazzInfo.pVertexAttributeDescriptions = copy;
    }

    void fromObject(VkPipelineVertexInputStateCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        getpVertexBindingDescriptions(clazzInfo);  // VkVertexInputBindingDescription Object Array
        getpVertexAttributeDescriptions(
                clazzInfo);  // VkVertexInputAttributeDescription Object Array
    }

    ~VkPipelineVertexInputStateCreateInfoAccessor() {
    }

};
