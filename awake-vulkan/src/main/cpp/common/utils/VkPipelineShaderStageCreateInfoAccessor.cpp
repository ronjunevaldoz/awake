/*
 *  VkPipelineShaderStageCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
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
    VkPipelineShaderStageCreateInfoAccessor(JNIEnv *env, jobject obj) {
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

    void *getpNext() {
        return (void *) (jobject) env->GetObjectField(obj, pNextField); // Object??
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    VkShaderStageFlagBits getstage() {
        auto stageEnum = (jobject) env->GetObjectField(obj, stageField);
        return (VkShaderStageFlagBits) enum_utils::getEnumFromObject(env, stageEnum);
    }

    uint64_t getmodule() {
        return (uint64_t) (jlong) env->GetLongField(obj, moduleField); // primitive
    }

    const char *getpName() {
        auto pNameObj = (jstring) env->GetObjectField(obj, pNameField);
        auto str = (const char *) env->GetStringUTFChars(pNameObj, nullptr);
        auto result = strdup(str); // Allocate memory and copy the string
        env->ReleaseStringUTFChars(pNameObj, str); // Release the local string reference
        return result;
    }

    std::vector<VkSpecializationInfo> getpSpecializationInfo() {
        auto pSpecializationInfoArray = (jobjectArray) env->GetObjectField(obj,
                                                                           pSpecializationInfoField);
        if (pSpecializationInfoArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pSpecializationInfoArray);
        std::vector<VkSpecializationInfo> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pSpecializationInfoArray,
                                                                i); // actual type is VkSpecializationInfo[];
            // experimental optimize accessor
            VkSpecializationInfoAccessor accessor(env, element);
            array.push_back(accessor.fromObject());
        }
        return array;
    }

    VkPipelineShaderStageCreateInfo fromObject() {
        VkPipelineShaderStageCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.stage = getstage(); // Object
        clazzInfo.module = getmodule(); // Object
        clazzInfo.pName = getpName(); // Object
        clazzInfo.pSpecializationInfo = getpSpecializationInfo().data(); // Object Array
        return clazzInfo;
    }

    ~VkPipelineShaderStageCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
