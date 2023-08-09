/*
 *  VkPipelineVertexInputStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
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
    VkPipelineVertexInputStateCreateInfoAccessor(JNIEnv *env, jobject obj) {
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

    void *getpNext() {
        return (void *) (jobject) env->GetObjectField(obj, pNextField); // Object??
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    std::vector<VkVertexInputBindingDescription> getpVertexBindingDescriptions() {
        auto pVertexBindingDescriptionsArray = (jobjectArray) env->GetObjectField(obj,
                                                                                  pVertexBindingDescriptionsField);
        if (pVertexBindingDescriptionsArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pVertexBindingDescriptionsArray);
        std::vector<VkVertexInputBindingDescription> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pVertexBindingDescriptionsArray,
                                                                i); // actual type is VkVertexInputBindingDescription[];
            // experimental optimize accessor
            VkVertexInputBindingDescriptionAccessor accessor(env, element);
            array.push_back(accessor.fromObject());
        }
        return array;
    }

    std::vector<VkVertexInputAttributeDescription> getpVertexAttributeDescriptions() {
        auto pVertexAttributeDescriptionsArray = (jobjectArray) env->GetObjectField(obj,
                                                                                    pVertexAttributeDescriptionsField);
        if (pVertexAttributeDescriptionsArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pVertexAttributeDescriptionsArray);
        std::vector<VkVertexInputAttributeDescription> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pVertexAttributeDescriptionsArray,
                                                                i); // actual type is VkVertexInputAttributeDescription[];
            // experimental optimize accessor
            VkVertexInputAttributeDescriptionAccessor accessor(env, element);
            array.push_back(accessor.fromObject());
        }
        return array;
    }

    VkPipelineVertexInputStateCreateInfo fromObject() {
        VkPipelineVertexInputStateCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.pVertexBindingDescriptions = getpVertexBindingDescriptions().data(); // Object Array
        clazzInfo.pVertexAttributeDescriptions = getpVertexAttributeDescriptions().data(); // Object Array
        return clazzInfo;
    }

    ~VkPipelineVertexInputStateCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
