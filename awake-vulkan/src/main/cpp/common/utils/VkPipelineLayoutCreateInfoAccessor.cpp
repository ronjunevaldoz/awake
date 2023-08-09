/*
 *  VkPipelineLayoutCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkPushConstantRangeAccessor.cpp>

class VkPipelineLayoutCreateInfoAccessor {
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
    jfieldID setLayoutCountField;
private:
    jfieldID pSetLayoutsField;
private:
    jfieldID pushConstantRangeCountField;
private:
    jfieldID pPushConstantRangesField;
public:
    VkPipelineLayoutCreateInfoAccessor(JNIEnv *env, jobject obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        setLayoutCountField = env->GetFieldID(clazz, "setLayoutCount", "I");
        pSetLayoutsField = env->GetFieldID(clazz, "pSetLayouts", "[Ljava/lang/Long;");
        pushConstantRangeCountField = env->GetFieldID(clazz, "pushConstantRangeCount", "I");
        pPushConstantRangesField = env->GetFieldID(clazz, "pPushConstantRanges",
                                                   "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPushConstantRange;");
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

    uint32_t getsetLayoutCount() {
        return (uint32_t) (jint) env->GetIntField(obj, setLayoutCountField); // primitive
    }

    std::vector<uint64_t> getpSetLayouts() {
        auto pSetLayoutsArray = (jlongArray) env->GetObjectField(obj, pSetLayoutsField);
        if (pSetLayoutsArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pSetLayoutsArray);
        std::vector<uint64_t> array(size);
        env->GetLongArrayRegion(pSetLayoutsArray, 0, size, reinterpret_cast<jlong *>(array.data()));
        return array;
    }

    uint32_t getpushConstantRangeCount() {
        return (uint32_t) (jint) env->GetIntField(obj, pushConstantRangeCountField); // primitive
    }

    std::vector<VkPushConstantRange> getpPushConstantRanges() {
        auto pPushConstantRangesArray = (jobjectArray) env->GetObjectField(obj,
                                                                           pPushConstantRangesField);
        if (pPushConstantRangesArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pPushConstantRangesArray);
        std::vector<VkPushConstantRange> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pPushConstantRangesArray,
                                                                i); // actual type is VkPushConstantRange[];
            // experimental optimize accessor
            VkPushConstantRangeAccessor accessor(env, element);
            array.push_back(accessor.fromObject());
        }
        return array;
    }

    VkPipelineLayoutCreateInfo fromObject() {
        VkPipelineLayoutCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.setLayoutCount = getsetLayoutCount(); // Object
        clazzInfo.pSetLayouts = getpSetLayouts().data(); // Object Array
        clazzInfo.pushConstantRangeCount = getpushConstantRangeCount(); // Object
        clazzInfo.pPushConstantRanges = getpPushConstantRanges().data(); // Object Array
        return clazzInfo;
    }

    ~VkPipelineLayoutCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
