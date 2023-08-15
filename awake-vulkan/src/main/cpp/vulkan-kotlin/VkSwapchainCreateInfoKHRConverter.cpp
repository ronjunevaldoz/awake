/* 
 * VkSwapchainCreateInfoKHRConverter.cpp
 * Created by Ron June Valdoz on Mon Aug 07 23:50:29 PST 2023
 */

#include <vector>
#include "VkSwapchainCreateInfoKHRConverter.h"
#include "enum_utils.h"
#include "VkExtent2DConverter.h"


VkSwapchainCreateInfoKHRConverter::VkSwapchainCreateInfoKHRConverter(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/VkSwapchainCreateInfoKHR");

    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    surfaceField = env->GetFieldID(clazz, "surface", "J");
    minImageCountField = env->GetFieldID(clazz, "minImageCount", "I");
    imageFormatField = env->GetFieldID(clazz, "imageFormat",
                                       "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFormat;");
    imageColorSpaceField = env->GetFieldID(clazz, "imageColorSpace",
                                           "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkColorSpaceKHR;");
    imageExtentField = env->GetFieldID(clazz, "imageExtent",
                                       "Lio/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D;");
    imageArrayLayersField = env->GetFieldID(clazz, "imageArrayLayers", "I");
    imageUsageField = env->GetFieldID(clazz, "imageUsage", "I");
    imageSharingModeField = env->GetFieldID(clazz, "imageSharingMode",
                                            "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkSharingMode;");
    pQueueFamilyIndicesField = env->GetFieldID(clazz, "pQueueFamilyIndices",
                                               "[Ljava/lang/Integer;");
    preTransformField = env->GetFieldID(clazz, "preTransform",
                                        "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkSurfaceTransformFlagBitsKHR;");
    compositeAlphaField = env->GetFieldID(clazz, "compositeAlpha",
                                          "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkCompositeAlphaFlagBitsKHR;");
    presentModeField = env->GetFieldID(clazz, "presentMode",
                                       "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkPresentModeKHR;");
    clippedField = env->GetFieldID(clazz, "clipped", "Z");
    oldSwapchainField = env->GetFieldID(clazz, "oldSwapchain", "Ljava/lang/Long;");
}

VkSwapchainCreateInfoKHR
VkSwapchainCreateInfoKHRConverter::fromObject(jobject pCreateInfo) {
    if (!env->IsInstanceOf(pCreateInfo, clazz)) {
        throw std::runtime_error("Invalid object. Expected VkSwapchainCreateInfoKHR.");
    }
    auto sTypeEnum = env->GetObjectField(pCreateInfo, sTypeField);
    auto pNextObj = env->GetObjectField(pCreateInfo, pNextField);
    auto flagsInt = env->GetIntField(pCreateInfo, flagsField);
    auto surfaceLong = env->GetLongField(pCreateInfo, surfaceField);
    auto minImageCountInt = env->GetIntField(pCreateInfo, minImageCountField);
    auto imageFormatEnum = env->GetObjectField(pCreateInfo, imageFormatField);
    auto imageColorSpaceEnum = env->GetObjectField(pCreateInfo, imageColorSpaceField);
    auto imageExtentObj = env->GetObjectField(pCreateInfo, imageExtentField);
    auto imageArrayLayersInt = env->GetIntField(pCreateInfo, imageArrayLayersField);
    auto imageUsageInt = env->GetIntField(pCreateInfo, imageUsageField);
    auto imageSharingModeEnum = env->GetObjectField(pCreateInfo, imageSharingModeField);
    auto pQueueFamilyIndicesArray = (jintArray) env->GetObjectField(pCreateInfo,
                                                                    pQueueFamilyIndicesField);
    auto preTransformEnum = env->GetObjectField(pCreateInfo, preTransformField);
    auto compositeAlphaEnum = env->GetObjectField(pCreateInfo, compositeAlphaField);
    auto presentModeEnum = env->GetObjectField(pCreateInfo, presentModeField);
    auto clippedBoolean = env->GetBooleanField(pCreateInfo, clippedField);
    auto oldSwapchainObj = env->GetObjectField(pCreateInfo, oldSwapchainField);

    std::vector<uint32_t> pQueueFamilyIndices;
    if (pQueueFamilyIndicesArray != nullptr) {
        auto elementSize = env->GetArrayLength(pQueueFamilyIndicesArray);
        for (int i = 0; i < elementSize; ++i) {
            jint element;
            env->GetIntArrayRegion(pQueueFamilyIndicesArray, i, 1, &element);
            pQueueFamilyIndices.push_back(element);
        }
    }

    VkSwapchainCreateInfoKHR createInfo;
    createInfo.sType = static_cast<VkStructureType>(enum_utils::getEnumFromObject(env, sTypeEnum));
    createInfo.pNext = static_cast<void *>(pNextObj);
    createInfo.flags = static_cast<uint32_t>(flagsInt); // primitive type int
    createInfo.surface = reinterpret_cast<VkSurfaceKHR>(surfaceLong); // primitive type long
    createInfo.minImageCount = static_cast<uint32_t>(minImageCountInt); // primitive type int
    createInfo.imageFormat = static_cast<VkFormat>(enum_utils::getEnumFromObject(env,
                                                                                 imageFormatEnum));
    createInfo.imageColorSpace = static_cast<VkColorSpaceKHR>(enum_utils::getEnumFromObject(env,
                                                                                            imageColorSpaceEnum));
    VkExtent2D imageExtentCreateInfo;
    imageExtentCreateInfo = VkExtent2DConverter(env).fromObject(imageExtentObj);
    createInfo.imageExtent = imageExtentCreateInfo;
    createInfo.imageArrayLayers = static_cast<uint32_t>(imageArrayLayersInt); // primitive type int
    createInfo.imageUsage = static_cast<uint32_t>(imageUsageInt); // primitive type int
    createInfo.imageSharingMode = static_cast<VkSharingMode>(enum_utils::getEnumFromObject(env,
                                                                                           imageSharingModeEnum));
    if (pQueueFamilyIndicesArray == nullptr) {
        createInfo.pQueueFamilyIndices = nullptr;
    } else {
        createInfo.pQueueFamilyIndices = pQueueFamilyIndices.data();
    }
    createInfo.preTransform = static_cast<VkSurfaceTransformFlagBitsKHR>(enum_utils::getEnumFromObject(
            env, preTransformEnum));
    createInfo.compositeAlpha = static_cast<VkCompositeAlphaFlagBitsKHR>(enum_utils::getEnumFromObject(
            env, compositeAlphaEnum));
    createInfo.presentMode = static_cast<VkPresentModeKHR>(enum_utils::getEnumFromObject(env,
                                                                                         presentModeEnum));
    createInfo.clipped = static_cast<VkBool32>(clippedBoolean); // primitive type boolean
    if (oldSwapchainObj == nullptr) {
        createInfo.oldSwapchain = nullptr;
    } else {
        createInfo.oldSwapchain = reinterpret_cast<VkSwapchainKHR>(oldSwapchainObj); // primitive type Long
    }

    env->DeleteLocalRef(sTypeEnum);
    env->DeleteLocalRef(pNextObj);
    env->DeleteLocalRef(imageFormatEnum);
    env->DeleteLocalRef(imageColorSpaceEnum);
    env->DeleteLocalRef(imageExtentObj);
    env->DeleteLocalRef(imageSharingModeEnum);
    env->DeleteLocalRef(pQueueFamilyIndicesArray);
    env->DeleteLocalRef(preTransformEnum);
    env->DeleteLocalRef(compositeAlphaEnum);
    env->DeleteLocalRef(presentModeEnum);
    env->DeleteLocalRef(oldSwapchainObj);
    return createInfo;
}

jobject VkSwapchainCreateInfoKHRConverter::toObject(VkSwapchainCreateInfoKHR &vulkan) {
    // TODO not yet implemented
    return nullptr;
}

VkSwapchainCreateInfoKHRConverter::~VkSwapchainCreateInfoKHRConverter() {
    // TODO not yet implemented
    sTypeField = nullptr;
    pNextField = nullptr;
    flagsField = nullptr;
    surfaceField = nullptr;
    minImageCountField = nullptr;
    imageFormatField = nullptr;
    imageColorSpaceField = nullptr;
    imageExtentField = nullptr;
    imageArrayLayersField = nullptr;
    imageUsageField = nullptr;
    imageSharingModeField = nullptr;
    pQueueFamilyIndicesField = nullptr;
    preTransformField = nullptr;
    compositeAlphaField = nullptr;
    presentModeField = nullptr;
    clippedField = nullptr;
    oldSwapchainField = nullptr;
}