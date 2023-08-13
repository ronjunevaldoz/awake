/*
 *  VkPipelineShaderStageCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkSpecializationInfoAccessor.cpp>

class VkPipelineShaderStageCreateInfoAccessor {
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
    jfieldID stageField;
private:
    jfieldID moduleField;
private:
    jfieldID pNameField;
private:
    jfieldID pSpecializationInfoField;
public:
    VkPipelineShaderStageCreateInfoAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        stageField = env->GetFieldID(clazz, "stage",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkShaderStageFlagBits;");
        moduleField = env->GetFieldID(clazz, "module", "J");
        pNameField = env->GetFieldID(clazz, "pName", "Ljava/lang/String;");
        pSpecializationInfoField = env->GetFieldID(clazz, "pSpecializationInfo",
                                                   "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkSpecializationInfo;");
    }

    VkStructureType getsType() {
        auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
        return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    }

    void getpNext(VkPipelineShaderStageCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    VkShaderStageFlagBits getstage() {
        auto stageEnum = (jobject) env->GetObjectField(obj, stageField);
        return (VkShaderStageFlagBits) enum_utils::getEnumFromObject(env, stageEnum);
    }

    VkShaderModule getmodule() {
        return reinterpret_cast<VkShaderModule>(env->GetLongField(obj, moduleField)); // VkHandle
    }

    void getpName(VkPipelineShaderStageCreateInfo &clazzInfo) {
        auto pNameObj = (jstring) env->GetObjectField(obj, pNameField);
        auto str = (const char *) env->GetStringUTFChars(pNameObj, nullptr);
        auto result = strdup(str); // Allocate memory and copy the string
        env->ReleaseStringUTFChars(pNameObj, str); // Release the local string reference
        clazzInfo.pName = result;
    }

    void getpSpecializationInfo(VkPipelineShaderStageCreateInfo &clazzInfo) {
        auto pSpecializationInfoArray = (jobjectArray) env->GetObjectField(obj,
                                                                           pSpecializationInfoField);
        if (pSpecializationInfoArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pSpecializationInfoArray);
        std::vector<VkSpecializationInfo> pSpecializationInfo;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pSpecializationInfoArray,
                                                                i); // actual type is VkSpecializationInfo[];
            // experimental optimize accessor
            VkSpecializationInfoAccessor accessor(env, element);
            VkSpecializationInfo ref{};
            accessor.fromObject(ref);
            pSpecializationInfo.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkSpecializationInfo[size];
        std::copy(pSpecializationInfo.begin(), pSpecializationInfo.end(), copy);
        clazzInfo.pSpecializationInfo = copy;
    }

    void fromObject(VkPipelineShaderStageCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        clazzInfo.stage = getstage(); // Enum VkShaderStageFlagBits
        clazzInfo.module = getmodule(); // VkHandle
        getpName(clazzInfo); // Object const char*
        getpSpecializationInfo(clazzInfo);  // VkSpecializationInfo Object Array
    }

    ~VkPipelineShaderStageCreateInfoAccessor() {
    }

};
