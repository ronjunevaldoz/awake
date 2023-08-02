//
// Created by Ron June Valdoz on 8/2/23.
//

#include "VkDeviceQueueCreateInfoConverter.h"

VkDeviceQueueCreateInfoConverter::VkDeviceQueueCreateInfoConverter(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/VkDeviceQueueCreateInfo");
    sTypeFieldID = env->GetFieldID(clazz, "sType", "I");
    pNextFieldID = env->GetFieldID(clazz, "pNext", "J");
    flagsFieldID = env->GetFieldID(clazz, "flags", "I");
    queueFamilyIndexFieldID = env->GetFieldID(clazz, "queueFamilyIndex", "I");
    queueCountFieldID = env->GetFieldID(clazz, "queueCount", "I");
    pQueuePrioritiesFieldID = env->GetFieldID(clazz, "pQueuePriorities", "[F");
}

VkDeviceQueueCreateInfo
VkDeviceQueueCreateInfoConverter::fromObject(jobject vkQueueCreateInfoObject) {
    // Extract the field values from the Java object
    jint sType = env->GetIntField(vkQueueCreateInfoObject, sTypeFieldID);
    jlong pNext = env->GetLongField(vkQueueCreateInfoObject, pNextFieldID);
    jint flags = env->GetIntField(vkQueueCreateInfoObject, flagsFieldID);
    jint queueFamilyIndex = env->GetIntField(vkQueueCreateInfoObject,
                                             queueFamilyIndexFieldID);
    jint queueCount = env->GetIntField(vkQueueCreateInfoObject, queueCountFieldID);

    auto pQueuePrioritiesObj = (jfloatArray) (env->GetObjectField(
            vkQueueCreateInfoObject, pQueuePrioritiesFieldID));
    auto numQueuePriorities = env->GetArrayLength(pQueuePrioritiesObj);
    float pQueuePriorities[numQueuePriorities];
    // Use GetFloatArrayRegion to directly copy the elements
    env->GetFloatArrayRegion(pQueuePrioritiesObj, 0, numQueuePriorities, pQueuePriorities);

    // Create a VkDeviceQueueCreateInfo object and add it to the vector
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO; // sType;
    queueCreateInfo.pNext = nullptr;
    queueCreateInfo.flags = flags; //VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT;//VkDeviceQueueCreateFlagBits// flags;
    queueCreateInfo.queueFamilyIndex = static_cast<uint32_t>(queueFamilyIndex);
    queueCreateInfo.queueCount = static_cast<uint32_t>(queueCount);
    queueCreateInfo.pQueuePriorities = pQueuePriorities;

    env->DeleteLocalRef(pQueuePrioritiesObj);

    return queueCreateInfo;
}

VkDeviceQueueCreateInfoConverter::~VkDeviceQueueCreateInfoConverter() {
    sTypeFieldID = nullptr;
    pNextFieldID = nullptr;
    flagsFieldID = nullptr;
    queueFamilyIndexFieldID = nullptr;
    queueCountFieldID = nullptr;
    pQueuePrioritiesFieldID = nullptr;
    env->DeleteLocalRef(clazz);
}
