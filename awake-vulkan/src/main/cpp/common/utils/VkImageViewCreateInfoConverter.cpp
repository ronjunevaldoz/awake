//
// Created by Ron June Valdoz on 8/1/23.
//

#include "VkImageViewCreateInfoConverter.h"
#include "enum_utils.h"

VkImageViewCreateInfoConverter::VkImageViewCreateInfoConverter(JNIEnv *env) {
    this->env = env;
    createInfoClazz = (jclass) (env->NewGlobalRef(
            env->FindClass(
                    "io/github/ronjunevaldoz/awake/vulkan/models/info/VkImageViewCreateInfo")));

    sTypeField = env->GetFieldID(createInfoClazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(createInfoClazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(createInfoClazz, "flags", "I");
    formatField = env->GetFieldID(createInfoClazz, "format",
                                  "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFormat;");
    imageField = env->GetFieldID(createInfoClazz, "image", "J");
    viewTypeField = env->GetFieldID(createInfoClazz, "viewType",
                                    "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkImageViewType;");
    componentsField = env->GetFieldID(createInfoClazz, "components",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/models/info/VkComponentMapping;");
    subresourceRangeField = env->GetFieldID(createInfoClazz, "subresourceRange",
                                            "Lio/github/ronjunevaldoz/awake/vulkan/models/info/VkImageSubresourceRange;");

    componentsClass = (jclass) (env->NewGlobalRef(
            env->FindClass("io/github/ronjunevaldoz/awake/vulkan/models/info/VkComponentMapping")));
    getRMethod = env->GetMethodID(componentsClass, "getR", componentSwizzleSig);
    getGMethod = env->GetMethodID(componentsClass, "getG", componentSwizzleSig);
    getBMethod = env->GetMethodID(componentsClass, "getB", componentSwizzleSig);
    getAMethod = env->GetMethodID(componentsClass, "getA", componentSwizzleSig);

    subresourceRangeClass = (jclass) (env->NewGlobalRef(env->FindClass(subresourceRangeSig)));
    getAspectMask = env->GetMethodID(subresourceRangeClass, "getAspectMask", "()I");
    getBaseMipLevel = env->GetMethodID(subresourceRangeClass, "getBaseMipLevel", "()I");
    getLevelCount = env->GetMethodID(subresourceRangeClass, "getLevelCount", "()I");
    getBaseArrayLayer = env->GetMethodID(subresourceRangeClass, "getBaseArrayLayer", "()I");
    getLayerCount = env->GetMethodID(subresourceRangeClass, "getLayerCount", "()I");
}

VkImageViewCreateInfo VkImageViewCreateInfoConverter::fromObject(jobject pCreateInfo) {
    jobject sTypeObj = env->GetObjectField(pCreateInfo, sTypeField);
    jobject formatObj = env->GetObjectField(pCreateInfo, formatField);
    jlong imageLong = env->GetLongField(pCreateInfo, imageField);
    jobject viewTypeObj = env->GetObjectField(pCreateInfo, viewTypeField);
    jobject componentsObj = env->GetObjectField(pCreateInfo, componentsField);
    jobject subresourceRangeObj = env->GetObjectField(pCreateInfo, subresourceRangeField);
    jobject comRObj = env->CallObjectMethod(componentsObj, getRMethod);
    jobject comGObj = env->CallObjectMethod(componentsObj, getGMethod);
    jobject comBObj = env->CallObjectMethod(componentsObj, getBMethod);
    jobject comAObj = env->CallObjectMethod(componentsObj, getAMethod);

    auto type = enum_utils::getEnumFromObject(env, sTypeObj);
    auto format = enum_utils::getEnumFromObject(env, formatObj);
    auto image = imageLong;
    auto viewType = enum_utils::getEnumFromObject(env, viewTypeObj);
    auto r = enum_utils::getEnumFromObject(env, comRObj);
    auto g = enum_utils::getEnumFromObject(env, comGObj);
    auto b = enum_utils::getEnumFromObject(env, comBObj);
    auto a = enum_utils::getEnumFromObject(env, comAObj);
    auto aspectMask = (VkImageAspectFlags) env->CallIntMethod(subresourceRangeObj, getAspectMask);
    auto baseMipLevel = (uint32_t) env->CallIntMethod(subresourceRangeObj, getBaseMipLevel);
    auto levelCount = (uint32_t) env->CallIntMethod(subresourceRangeObj, getLevelCount);
    auto baseArrayLayer = (uint32_t) env->CallIntMethod(subresourceRangeObj, getBaseArrayLayer);
    auto layerCount = (uint32_t) env->CallIntMethod(subresourceRangeObj, getLayerCount);

    VkImageViewCreateInfo createInfo;
    createInfo.sType = static_cast<VkStructureType>(type);
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.format = static_cast<VkFormat>(format);
    createInfo.image = reinterpret_cast<VkImage>(image);
    createInfo.viewType = static_cast<VkImageViewType>(viewType);
    createInfo.components.r = static_cast<VkComponentSwizzle>(r);
    createInfo.components.g = static_cast<VkComponentSwizzle>(g);
    createInfo.components.b = static_cast<VkComponentSwizzle>(b);
    createInfo.components.a = static_cast<VkComponentSwizzle>(a);
    createInfo.subresourceRange.aspectMask = aspectMask;
    createInfo.subresourceRange.baseMipLevel = baseMipLevel;
    createInfo.subresourceRange.levelCount = levelCount;
    createInfo.subresourceRange.baseArrayLayer = baseArrayLayer;
    createInfo.subresourceRange.layerCount = layerCount;

    env->DeleteLocalRef(componentsObj);
    env->DeleteLocalRef(sTypeObj);
    env->DeleteLocalRef(formatObj);
    env->DeleteLocalRef(comRObj);
    env->DeleteLocalRef(comGObj);
    env->DeleteLocalRef(comBObj);
    env->DeleteLocalRef(comAObj);

    return createInfo;
}

VkImageViewCreateInfoConverter::~VkImageViewCreateInfoConverter() {
    env->DeleteGlobalRef(createInfoClazz);
    env->DeleteGlobalRef(componentsClass);
    env->DeleteGlobalRef(subresourceRangeClass);
}