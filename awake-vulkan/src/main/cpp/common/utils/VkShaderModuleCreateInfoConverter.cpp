/* 
 * VkShaderModuleCreateInfoConverter.cpp
 * Created by Ron June Valdoz on Mon Aug 07 11:15:30 PST 2023
 */

#include <vector>
#include "VkShaderModuleCreateInfoConverter.h"
#include "enum_utils.h"


VkShaderModuleCreateInfoConverter::VkShaderModuleCreateInfoConverter(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/VkShaderModuleCreateInfo");

    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    pCodeField = env->GetFieldID(clazz, "pCode", "[I");
}

VkShaderModuleCreateInfo
VkShaderModuleCreateInfoConverter::fromObject(jobject pCreateInfo) {
    if (!env->IsInstanceOf(pCreateInfo, clazz)) {
        throw std::runtime_error("Invalid object. Expected VkShaderModuleCreateInfo.");
    }
    auto sTypeEnum = env->GetObjectField(pCreateInfo, sTypeField);
    auto pNextObj = env->GetObjectField(pCreateInfo, pNextField);
    auto flagsInt = env->GetIntField(pCreateInfo, flagsField);
    auto pCodeArray = (jintArray) env->GetObjectField(pCreateInfo, pCodeField);

    std::vector<uint32_t> pCode;
    if (pCodeArray != nullptr) {
        auto elementSize = env->GetArrayLength(pCodeArray);
        for (int i = 0; i < elementSize; ++i) {
            int element;
            env->GetIntArrayRegion(pCodeArray, i, 1, &element);
            pCode.push_back(element);
        }
    }

    VkShaderModuleCreateInfo createInfo;
    createInfo.sType = static_cast<VkStructureType>(enum_utils::getEnumFromObject(env, sTypeEnum));
    createInfo.pNext = static_cast<void *>(pNextObj);
    createInfo.flags = static_cast<uint32_t>(flagsInt); // primitive type int
    if (pCodeArray == nullptr) {
        createInfo.codeSize = 0;
        createInfo.pCode = nullptr;
    } else {

        createInfo.codeSize = static_cast<uint32_t>(pCode.size() * sizeof(uint32_t));
        createInfo.pCode = pCode.data();
    }

    env->DeleteLocalRef(sTypeEnum);
    env->DeleteLocalRef(pNextObj);
    env->DeleteLocalRef(pCodeArray);
    return createInfo;
}

jobject VkShaderModuleCreateInfoConverter::toObject(VkShaderModuleCreateInfo &vulkan) {
    // TODO not yet implemented
    return nullptr;
}

VkShaderModuleCreateInfoConverter::~VkShaderModuleCreateInfoConverter() {
    // TODO not yet implemented
}