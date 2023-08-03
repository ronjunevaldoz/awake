//
// Created by Ron June Valdoz on 8/2/23.
//

#include <vector>
#include "VkShaderModuleCreateInfoConverter.h"
#include "enum_utils.h"

VkShaderModuleCreateInfoConverter::VkShaderModuleCreateInfoConverter(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/VkShaderModuleCreateInfo");
//    constructor = env->GetMethodID(clazz, "<init>", "()V");

    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    codeSizeField = env->GetFieldID(clazz, "codeSize", "J");
    pCodeField = env->GetFieldID(clazz, "pCode", "[B");
}


VkShaderModuleCreateInfo VkShaderModuleCreateInfoConverter::fromObject(jobject pCreateInfoObj) {
    auto typeObj = env->GetObjectField(pCreateInfoObj, sTypeField);
    auto pNextObj = env->GetObjectField(pCreateInfoObj, pNextField);
    auto flags = env->GetIntField(pCreateInfoObj, flagsField);
    auto codeSize = env->GetLongField(pCreateInfoObj, codeSizeField);
    auto codeByteArray = (jbyteArray) env->GetObjectField(pCreateInfoObj, pCodeField);

    jsize fileSize = env->GetArrayLength(codeByteArray);
    std::vector<jbyte> buffer(fileSize);

    env->GetByteArrayRegion(codeByteArray, 0, fileSize, buffer.data());
    env->DeleteLocalRef(codeByteArray);

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;// static_cast<VkStructureType>(enum_utils::getEnumFromObject(env, typeObj));
//    createInfo.pNext = nullptr;//static_cast<void *>(pNextObj);
//    createInfo.flags = 0;//static_cast<uint32_t>(flags);
    createInfo.codeSize = fileSize * sizeof(jbyte);
    auto code = reinterpret_cast<const uint32_t *>(buffer.data());
//    createInfo.codeSize =  buffer.size() / sizeof(uint32_t);
    createInfo.pCode = code;

    buffer.clear();
    env->DeleteLocalRef(typeObj);
    env->DeleteLocalRef(pNextObj);

    return createInfo;
}


VkShaderModuleCreateInfoConverter::~VkShaderModuleCreateInfoConverter() {
    env->DeleteLocalRef(clazz);
    clazz = nullptr;
    sTypeField = nullptr;
    flagsField = nullptr;
    codeSizeField = nullptr;
    pCodeField = nullptr;
}