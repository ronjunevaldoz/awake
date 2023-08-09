/* 
 * VkStencilOpStateConverter.cpp
 * Created by Ron June Valdoz on Wed Aug 09 09:18:59 PST 2023
 */

#include <vector>
#include "VkStencilOpStateConverter.h"
#include "enum_utils.h"


VkStencilOpStateConverter::VkStencilOpStateConverter(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass("io/github/ronjunevaldoz/awake/vulkan/models/VkStencilOpState");

    failOpField = env->GetFieldID(clazz, "failOp",
                                  "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStencilOp;");
    passOpField = env->GetFieldID(clazz, "passOp",
                                  "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStencilOp;");
    depthFailOpField = env->GetFieldID(clazz, "depthFailOp",
                                       "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStencilOp;");
    compareOpField = env->GetFieldID(clazz, "compareOp",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkCompareOp;");
    compareMaskField = env->GetFieldID(clazz, "compareMask", "I");
    writeMaskField = env->GetFieldID(clazz, "writeMask", "I");
    referenceField = env->GetFieldID(clazz, "reference", "I");
}

VkStencilOpState
VkStencilOpStateConverter::fromObject(jobject pCreateInfo) {
    if (!env->IsInstanceOf(pCreateInfo, clazz)) {
        throw std::runtime_error("Invalid object. Expected VkStencilOpState.");
    }
    auto failOpEnum = env->GetObjectField(pCreateInfo, failOpField);
    auto passOpEnum = env->GetObjectField(pCreateInfo, passOpField);
    auto depthFailOpEnum = env->GetObjectField(pCreateInfo, depthFailOpField);
    auto compareOpEnum = env->GetObjectField(pCreateInfo, compareOpField);
    auto compareMaskInt = env->GetIntField(pCreateInfo, compareMaskField);
    auto writeMaskInt = env->GetIntField(pCreateInfo, writeMaskField);
    auto referenceInt = env->GetIntField(pCreateInfo, referenceField);


    VkStencilOpState createInfo;
    createInfo.failOp = static_cast<VkStencilOp>(enum_utils::getEnumFromObject(env, failOpEnum));
    createInfo.passOp = static_cast<VkStencilOp>(enum_utils::getEnumFromObject(env, passOpEnum));
    createInfo.depthFailOp = static_cast<VkStencilOp>(enum_utils::getEnumFromObject(env,
                                                                                    depthFailOpEnum));
    createInfo.compareOp = static_cast<VkCompareOp>(enum_utils::getEnumFromObject(env,
                                                                                  compareOpEnum));
    createInfo.compareMask = static_cast<uint32_t>(compareMaskInt); // primitive type int
    createInfo.writeMask = static_cast<uint32_t>(writeMaskInt); // primitive type int
    createInfo.reference = static_cast<uint32_t>(referenceInt); // primitive type int

    env->DeleteLocalRef(failOpEnum);
    env->DeleteLocalRef(passOpEnum);
    env->DeleteLocalRef(depthFailOpEnum);
    env->DeleteLocalRef(compareOpEnum);
    return createInfo;
}

jobject VkStencilOpStateConverter::toObject(VkStencilOpState &vulkan) {
    // TODO not yet implemented
    return nullptr;
}

VkStencilOpStateConverter::~VkStencilOpStateConverter() {
    // TODO not yet implemented
    failOpField = nullptr;
    passOpField = nullptr;
    depthFailOpField = nullptr;
    compareOpField = nullptr;
    compareMaskField = nullptr;
    writeMaskField = nullptr;
    referenceField = nullptr;
}