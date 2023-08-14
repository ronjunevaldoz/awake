/*
 *  VkPipelineLayoutCreateInfoAccessor.cpp
 *  Vulkan accessor for VkPipelineLayoutCreateInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkPipelineLayoutCreateInfoAccessor.h>

VkPipelineLayoutCreateInfoAccessor::VkPipelineLayoutCreateInfoAccessor(JNIEnv *env, jobject obj) {
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

VkStructureType
VkPipelineLayoutCreateInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

uint32_t
VkPipelineLayoutCreateInfoAccessor::getflags() {
    return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
}

uint32_t
VkPipelineLayoutCreateInfoAccessor::getpushConstantRangeCount() {
    return (uint32_t) (jint) env->GetIntField(obj, pushConstantRangeCountField); // primitive
}

void
VkPipelineLayoutCreateInfoAccessor::getpPushConstantRanges(VkPipelineLayoutCreateInfo &clazzInfo) {
    auto pPushConstantRangesArray = (jobjectArray) env->GetObjectField(obj,
                                                                       pPushConstantRangesField);
    if (pPushConstantRangesArray == nullptr) {
        clazzInfo.pPushConstantRanges = nullptr;
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
    // processing array data
    // Make a copy of the object to ensure proper memory management;
    auto copy = new VkPushConstantRange[size];
    std::copy(pPushConstantRanges.begin(), pPushConstantRanges.end(), copy);
    clazzInfo.pPushConstantRanges = copy;
}

void
VkPipelineLayoutCreateInfoAccessor::fromObject(VkPipelineLayoutCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Object void*
    clazzInfo.flags = getflags(); // Object uint32_t
    clazzInfo.setLayoutCount = getsetLayoutCount(); // Object uint32_t
    getpSetLayouts(clazzInfo);  // Long Object Array
    clazzInfo.pushConstantRangeCount = getpushConstantRangeCount(); // Object uint32_t
    getpPushConstantRanges(clazzInfo);  // VkPushConstantRange Object Array
}

void
VkPipelineLayoutCreateInfoAccessor::getpNext(VkPipelineLayoutCreateInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

uint32_t
VkPipelineLayoutCreateInfoAccessor::getsetLayoutCount() {
    return (uint32_t) (jint) env->GetIntField(obj, setLayoutCountField); // primitive
}

void
VkPipelineLayoutCreateInfoAccessor::getpSetLayouts(VkPipelineLayoutCreateInfo &clazzInfo) {
    auto pSetLayoutsArray = (jlongArray) env->GetObjectField(obj, pSetLayoutsField);
    if (pSetLayoutsArray == nullptr) {
        clazzInfo.pSetLayouts = nullptr;
        return;
    }
    auto size = env->GetArrayLength(pSetLayoutsArray);
    // primitive array?
    std::vector<VkDescriptorSetLayout> pSetLayouts(size);
    env->GetLongArrayRegion(pSetLayoutsArray, 0, size,
                            reinterpret_cast<jlong *>(pSetLayouts.data()));
    // processing array data
    // Make a copy of the object to ensure proper memory management;
    auto copy = new VkDescriptorSetLayout[size];
    std::copy(pSetLayouts.begin(), pSetLayouts.end(), copy);
    clazzInfo.pSetLayouts = copy;
}

VkPipelineLayoutCreateInfoAccessor::~VkPipelineLayoutCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

