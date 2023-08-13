/*
 *  VkPipelineLayoutCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
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
    VkPipelineLayoutCreateInfoAccessor(JNIEnv *env, jobject &obj) {
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

    void getpNext(VkPipelineLayoutCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    uint32_t getsetLayoutCount() {
        return (uint32_t) (jint) env->GetIntField(obj, setLayoutCountField); // primitive
    }

    void getpSetLayouts(VkPipelineLayoutCreateInfo &clazzInfo) {
        auto pSetLayoutsArray = (jlongArray) env->GetObjectField(obj, pSetLayoutsField);
        if (pSetLayoutsArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pSetLayoutsArray);
        // primitive array?
        std::vector<VkDescriptorSetLayout> pSetLayouts(size);
        env->GetLongArrayRegion(pSetLayoutsArray, 0, size,
                                reinterpret_cast<jlong *>(pSetLayouts.data()));
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkDescriptorSetLayout[size];
        std::copy(pSetLayouts.begin(), pSetLayouts.end(), copy);
        clazzInfo.pSetLayouts = copy;
    }

    uint32_t getpushConstantRangeCount() {
        return (uint32_t) (jint) env->GetIntField(obj, pushConstantRangeCountField); // primitive
    }

    void getpPushConstantRanges(VkPipelineLayoutCreateInfo &clazzInfo) {
        auto pPushConstantRangesArray = (jobjectArray) env->GetObjectField(obj,
                                                                           pPushConstantRangesField);
        if (pPushConstantRangesArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pPushConstantRangesArray);
        std::vector<VkPushConstantRange> pPushConstantRanges;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pPushConstantRangesArray,
                                                                i); // actual type is VkPushConstantRange[];
            // experimental optimize accessor
            VkPushConstantRangeAccessor accessor(env, element);
            VkPushConstantRange ref{};
            accessor.fromObject(ref);
            pPushConstantRanges.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkPushConstantRange[size];
        std::copy(pPushConstantRanges.begin(), pPushConstantRanges.end(), copy);
        clazzInfo.pPushConstantRanges = copy;
    }

    void fromObject(VkPipelineLayoutCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        clazzInfo.setLayoutCount = getsetLayoutCount(); // Object uint32_t
        getpSetLayouts(clazzInfo);  // Long Object Array
        clazzInfo.pushConstantRangeCount = getpushConstantRangeCount(); // Object uint32_t
        getpPushConstantRanges(clazzInfo);  // VkPushConstantRange Object Array
    }

    ~VkPipelineLayoutCreateInfoAccessor() {
    }

};
