/*
 *  VkPipelineColorBlendStateCreateInfoAccessor.cpp
 *  Vulkan accessor for VkPipelineColorBlendStateCreateInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkPipelineColorBlendStateCreateInfoAccessor.h>

VkPipelineColorBlendStateCreateInfoAccessor::VkPipelineColorBlendStateCreateInfoAccessor(
        JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    logicOpEnableField = env->GetFieldID(clazz, "logicOpEnable", "Z");
    logicOpField = env->GetFieldID(clazz, "logicOp",
                                   "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkLogicOp;");
    pAttachmentsField = env->GetFieldID(clazz, "pAttachments",
                                        "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineColorBlendAttachmentState;");
    blendConstantsField = env->GetFieldID(clazz, "blendConstants", "[F");
}

VkStructureType
VkPipelineColorBlendStateCreateInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

VkBool32
VkPipelineColorBlendStateCreateInfoAccessor::getlogicOpEnable() {
    return (VkBool32) (jboolean) env->GetBooleanField(obj, logicOpEnableField); // primitive
}

uint32_t
VkPipelineColorBlendStateCreateInfoAccessor::getflags() {
    return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
}

void
VkPipelineColorBlendStateCreateInfoAccessor::getpAttachments(
        VkPipelineColorBlendStateCreateInfo &clazzInfo) {
    auto pAttachmentsArray = (jobjectArray) env->GetObjectField(obj, pAttachmentsField);
    if (pAttachmentsArray == nullptr) {
        clazzInfo.attachmentCount = 0;
        clazzInfo.pAttachments = nullptr;
        return;
    }
    auto size = env->GetArrayLength(pAttachmentsArray);
    std::vector<VkPipelineColorBlendAttachmentState> pAttachments;
    for (int i = 0; i < size; ++i) {
        auto element = (jobject) env->GetObjectArrayElement(pAttachmentsArray,
                                                            i); // actual type is VkPipelineColorBlendAttachmentState[];
        // experimental optimize accessor
        VkPipelineColorBlendAttachmentStateAccessor accessor(env, element);
        VkPipelineColorBlendAttachmentState ref{};
        accessor.fromObject(ref);
        pAttachments.push_back(ref);
    }
    // processing array data
    auto attachmentCount = static_cast<uint32_t>(pAttachments.size());
    clazzInfo.attachmentCount = attachmentCount;
    // Make a copy of the object to ensure proper memory management;
    auto copy = new VkPipelineColorBlendAttachmentState[size];
    std::copy(pAttachments.begin(), pAttachments.end(), copy);
    clazzInfo.pAttachments = copy;
}

void
VkPipelineColorBlendStateCreateInfoAccessor::fromObject(
        VkPipelineColorBlendStateCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Other void*
    clazzInfo.flags = getflags(); // Primitive uint32_t
    clazzInfo.logicOpEnable = getlogicOpEnable(); // Primitive VkBool32
    clazzInfo.logicOp = getlogicOp(); // Enum VkLogicOp
    getpAttachments(clazzInfo);  // VkPipelineColorBlendAttachmentState Object Array
    getblendConstants(clazzInfo);  // float Object Array
}

void
VkPipelineColorBlendStateCreateInfoAccessor::getblendConstants(
        VkPipelineColorBlendStateCreateInfo &clazzInfo) {
    auto blendConstantsArray = (jfloatArray) env->GetObjectField(obj, blendConstantsField);
    if (blendConstantsArray == nullptr) {
        // const array
        // clazzInfo.blendConstants = nullptr;
        return;
    }
    auto size = env->GetArrayLength(blendConstantsArray);
    // primitive array?
    std::vector<float> blendConstants(size);
    env->GetFloatArrayRegion(blendConstantsArray, 0, size,
                             reinterpret_cast<jfloat *>(blendConstants.data()));
    // processing array data
    std::copy(blendConstants.begin(), blendConstants.end(),
              clazzInfo.blendConstants); // fixed array size
}

void
VkPipelineColorBlendStateCreateInfoAccessor::getpNext(
        VkPipelineColorBlendStateCreateInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

VkLogicOp
VkPipelineColorBlendStateCreateInfoAccessor::getlogicOp() {
    auto logicOpEnum = (jobject) env->GetObjectField(obj, logicOpField);
    return (VkLogicOp) enum_utils::getEnumFromObject(env, logicOpEnum);
}

VkPipelineColorBlendStateCreateInfoAccessor::~VkPipelineColorBlendStateCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

