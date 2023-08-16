/*
 *  VkDebugUtilsMessengerCreateInfoEXTAccessor.cpp
 *  Vulkan accessor for VkDebugUtilsMessengerCreateInfoEXT
 *  Created by Ron June Valdoz */

#include  <includes/VkDebugUtilsMessengerCreateInfoEXTAccessor.h>
#include <android/log.h>
#include "VkDebugUtilsMessengerCallbackDataEXTAccessor.h"
#include "VkDebugUtilsMessengerCallbackDataEXTMutator.h"

VkDebugUtilsMessengerCreateInfoEXTAccessor *VkDebugUtilsMessengerCreateInfoEXTAccessor::sInstance = nullptr;


VkStructureType
VkDebugUtilsMessengerCreateInfoEXTAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    auto enumValue = (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    env->DeleteLocalRef(sTypeEnum); // release enum reference
    return enumValue;
}

uint32_t
VkDebugUtilsMessengerCreateInfoEXTAccessor::getflags() {
    return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
}

uint32_t
VkDebugUtilsMessengerCreateInfoEXTAccessor::getmessageType() {
    return (uint32_t) (jint) env->GetIntField(obj, messageTypeField); // primitive
}


VkBool32 VkDebugUtilsMessengerCreateInfoEXTAccessor::onDebugUtilsMessage(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageTypes,
        const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
        void *userData) {
    const char validation[] = "Validation";
    const char performance[] = "Performance";
    const char error[] = "ERROR";
    const char warning[] = "WARNING";
    const char unknownType[] = "UNKNOWN_TYPE";
    const char unknownSeverity[] = "UNKNOWN_SEVERITY";
    const char *typeString = unknownType;
    const char *severityString = unknownSeverity;
    const char *messageIdName = callbackData->pMessageIdName;
    int32_t messageIdNumber = callbackData->messageIdNumber;
    const char *message = callbackData->pMessage;


    android_LogPriority priority = ANDROID_LOG_UNKNOWN;
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        severityString = error;
        priority = ANDROID_LOG_ERROR;
    } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        severityString = warning;
        priority = ANDROID_LOG_WARN;
    }
    if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
        typeString = validation;
    } else if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
        typeString = performance;
    }

    // how to acces callbackOBj here?

    jclass callbackInterface = env->GetObjectClass(callbackObj);
//
//    // Get the method ID of the onDebugUtilsMessage method
// Assuming you have a reference to the callback interface class and the method name is "messageSeverity"
    jmethodID invokeMethod = env->GetMethodID(callbackInterface, "invoke",
                                              "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    jint jSeverity = static_cast<jint>(messageSeverity);
    jint jTypes = static_cast<jint>(messageTypes);

    auto jData = VkDebugUtilsMessengerCallbackDataEXTMutator(env).toObject(*callbackData);
//    auto jData = reinterpret_cast<jlong>(callbackData);
    auto jUserData = reinterpret_cast<jlong>(userData);

    jclass integerClass = env->FindClass("java/lang/Integer");
    jmethodID integerConstructor = env->GetMethodID(integerClass, "<init>", "(I)V");

    jobject arg1 = enum_utils::setEnumFromVulkan(env, jSeverity,
                                                 "io/github/ronjunevaldoz/awake/vulkan/enums/flags/VkDebugUtilsMessageSeverityFlagBitsEXT");
    jobject arg2 = env->NewObject(integerClass, integerConstructor,
                                  static_cast<jint>(messageTypes));

    jobject result = env->CallObjectMethod(callbackObj, invokeMethod, arg1, arg2, jData, nullptr);

    auto r = static_cast<VkBool32>((bool) result);
    env->DeleteLocalRef(arg1);
    env->DeleteLocalRef(arg2);
    env->DeleteLocalRef(result);
    env->DeleteLocalRef(integerClass);
    env->DeleteLocalRef(callbackInterface);
    // Returning false tells the layer not to stop when the event occurs, so
    // they see the same behavior with and without validation layers enabled.
    return r;
}


void VkDebugUtilsMessengerCreateInfoEXTAccessor::getpfnUserCallback(
        VkDebugUtilsMessengerCreateInfoEXT &clazzInfo) {
//    auto callbackObj = (jobject) env->GetObjectField(obj, pfnUserCallbackField); // Any Object
    clazzInfo.pfnUserCallback = &StaticOnDebugUtilsMessage;
}

void
VkDebugUtilsMessengerCreateInfoEXTAccessor::getpUserData(
        VkDebugUtilsMessengerCreateInfoEXT &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pUserDataField); // Any Object
    clazzInfo.pUserData = ref;
}

void
VkDebugUtilsMessengerCreateInfoEXTAccessor::fromObject(
        VkDebugUtilsMessengerCreateInfoEXT &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Other void*
    clazzInfo.flags = getflags(); // Primitive uint32_t
    clazzInfo.messageSeverity = getmessageSeverity(); // Primitive uint32_t
    clazzInfo.messageType = getmessageType(); // Primitive uint32_t
    getpfnUserCallback(clazzInfo); // Other Function4
    getpUserData(clazzInfo); // Other void*
}

void
VkDebugUtilsMessengerCreateInfoEXTAccessor::getpNext(
        VkDebugUtilsMessengerCreateInfoEXT &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

uint32_t
VkDebugUtilsMessengerCreateInfoEXTAccessor::getmessageSeverity() {
    return (uint32_t) (jint) env->GetIntField(obj, messageSeverityField); // primitive
}

VkDebugUtilsMessengerCreateInfoEXTAccessor::~VkDebugUtilsMessengerCreateInfoEXTAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}