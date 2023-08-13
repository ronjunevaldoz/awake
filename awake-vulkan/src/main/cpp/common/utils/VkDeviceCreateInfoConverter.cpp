/* 
 * VkDeviceCreateInfoConverter.cpp
 * Created by Ron June Valdoz on Mon Aug 07 23:50:29 PST 2023
 */

#include <vector>
#include "VkDeviceCreateInfoConverter.h"
#include "enum_utils.h"
#include "VkDeviceQueueCreateInfoConverter.h"
#include "VkPhysicalDeviceFeaturesConverter.h"


VkDeviceCreateInfoConverter::VkDeviceCreateInfoConverter(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass("io/github/ronjunevaldoz/awake/vulkan/models/info/VkDeviceCreateInfo");

    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    pQueueCreateInfosField = env->GetFieldID(clazz, "pQueueCreateInfos",
                                             "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/VkDeviceQueueCreateInfo;");
    ppEnabledLayerNamesField = env->GetFieldID(clazz, "ppEnabledLayerNames", "[Ljava/lang/String;");
    ppEnabledExtensionNamesField = env->GetFieldID(clazz, "ppEnabledExtensionNames",
                                                   "[Ljava/lang/String;");
    pEnabledFeaturesField = env->GetFieldID(clazz, "pEnabledFeatures",
                                            "[Lio/github/ronjunevaldoz/awake/vulkan/physicaldevice/VkPhysicalDeviceFeatures;");
}

VkDeviceCreateInfo
VkDeviceCreateInfoConverter::fromObject(jobject pCreateInfo) {
    if (!env->IsInstanceOf(pCreateInfo, clazz)) {
        throw std::runtime_error("Invalid object. Expected VkDeviceCreateInfo.");
    }
    auto sTypeEnum = env->GetObjectField(pCreateInfo, sTypeField);
    auto pNextObj = env->GetObjectField(pCreateInfo, pNextField);
    auto flagsInt = env->GetIntField(pCreateInfo, flagsField);
    auto pQueueCreateInfosArray = (jobjectArray) env->GetObjectField(pCreateInfo,
                                                                     pQueueCreateInfosField);
    auto ppEnabledLayerNamesArray = (jobjectArray) env->GetObjectField(pCreateInfo,
                                                                       ppEnabledLayerNamesField);
    auto ppEnabledExtensionNamesArray = (jobjectArray) env->GetObjectField(pCreateInfo,
                                                                           ppEnabledExtensionNamesField);
    auto pEnabledFeaturesArray = (jobjectArray) env->GetObjectField(pCreateInfo,
                                                                    pEnabledFeaturesField);
    VkDeviceQueueCreateInfoConverter pQueueCreateInfoConverter(env);
    VkPhysicalDeviceFeaturesConverter pEnabledFeatureConverter(env);
    std::vector<VkDeviceQueueCreateInfo> pQueueCreateInfos;
    if (pQueueCreateInfosArray != nullptr) {
        auto elementSize = env->GetArrayLength(pQueueCreateInfosArray);
        for (int i = 0; i < elementSize; ++i) {
            auto pQueueCreateInfoElement = env->GetObjectArrayElement(pQueueCreateInfosArray,
                                                                      i); // actual type is VkDeviceQueueCreateInfo[]
            auto value = pQueueCreateInfoConverter.fromObject(pQueueCreateInfoElement);;
            pQueueCreateInfos.push_back(value);
            env->DeleteLocalRef(pQueueCreateInfoElement);
        }
    }

    std::vector<const char *> ppEnabledLayerNames;
    if (ppEnabledLayerNamesArray != nullptr) {
        auto elementSize = env->GetArrayLength(ppEnabledLayerNamesArray);
        for (int i = 0; i < elementSize; ++i) {
            jstring element;
            element = (jstring) env->GetObjectArrayElement(ppEnabledLayerNamesArray,
                                                           i); // actual type is String[]
            const char *utfChars = env->GetStringUTFChars(element, nullptr);
            ppEnabledLayerNames.push_back(utfChars);
            env->ReleaseStringUTFChars(element, utfChars);
            env->DeleteLocalRef(element);
        }
    }

    std::vector<const char *> ppEnabledExtensionNames;
    if (ppEnabledExtensionNamesArray != nullptr) {
        auto elementSize = env->GetArrayLength(ppEnabledExtensionNamesArray);
        for (int i = 0; i < elementSize; ++i) {
            jstring element;
            element = (jstring) env->GetObjectArrayElement(ppEnabledExtensionNamesArray,
                                                           i); // actual type is String[]
            const char *utfChars = env->GetStringUTFChars(element, nullptr);
            ppEnabledExtensionNames.push_back(utfChars);
            env->ReleaseStringUTFChars(element, utfChars);
            env->DeleteLocalRef(element);
        }
    }

    std::vector<VkPhysicalDeviceFeatures> pEnabledFeatures;
    if (pEnabledFeaturesArray != nullptr) {
        auto elementSize = env->GetArrayLength(pEnabledFeaturesArray);
        for (int i = 0; i < elementSize; ++i) {
            auto pEnabledFeatureElement = env->GetObjectArrayElement(pEnabledFeaturesArray,
                                                                     i); // actual type is VkPhysicalDeviceFeatures[]
            auto value = pEnabledFeatureConverter.fromObject(pEnabledFeatureElement);;
            pEnabledFeatures.push_back(value);
            env->DeleteLocalRef(pEnabledFeatureElement);
        }
    }

    VkDeviceCreateInfo createInfo;
    createInfo.sType = static_cast<VkStructureType>(enum_utils::getEnumFromObject(env, sTypeEnum));
    createInfo.pNext = static_cast<void *>(pNextObj);
    createInfo.flags = static_cast<uint32_t>(flagsInt); // primitive type int

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(pQueueCreateInfos.size());
    createInfo.pQueueCreateInfos = pQueueCreateInfos.data();

    createInfo.enabledLayerCount = static_cast<uint32_t>(ppEnabledLayerNames.size());
    createInfo.ppEnabledLayerNames = ppEnabledLayerNames.data();

    createInfo.enabledExtensionCount = static_cast<uint32_t>(ppEnabledExtensionNames.size());
    createInfo.ppEnabledExtensionNames = ppEnabledExtensionNames.data();
    createInfo.pEnabledFeatures = pEnabledFeatures.data();

    env->DeleteLocalRef(sTypeEnum);
    env->DeleteLocalRef(pNextObj);
    env->DeleteLocalRef(pQueueCreateInfosArray);
    env->DeleteLocalRef(ppEnabledLayerNamesArray);
    env->DeleteLocalRef(ppEnabledExtensionNamesArray);
    env->DeleteLocalRef(pEnabledFeaturesArray);
    return createInfo;
}

jobject VkDeviceCreateInfoConverter::toObject(VkDeviceCreateInfo &vulkan) {
    // TODO not yet implemented
    return nullptr;
}

VkDeviceCreateInfoConverter::~VkDeviceCreateInfoConverter() {
    // TODO not yet implemented
    sTypeField = nullptr;
    pNextField = nullptr;
    flagsField = nullptr;
    pQueueCreateInfosField = nullptr;
    ppEnabledLayerNamesField = nullptr;
    ppEnabledExtensionNamesField = nullptr;
    pEnabledFeaturesField = nullptr;
}