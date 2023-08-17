/*
 *  VkDebugUtilsMessengerCallbackDataEXTMutator.cpp
 *  Vulkan mutator for VkDebugUtilsMessengerCallbackDataEXT
 *  Created by Ron June Valdoz */

#include <includes/VkDebugUtilsMessengerCallbackDataEXTMutator.h>

VkDebugUtilsMessengerCallbackDataEXTMutator::VkDebugUtilsMessengerCallbackDataEXTMutator(
        JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/debug/VkDebugUtilsMessengerCallbackDataEXT");
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    pMessageIdNameField = env->GetFieldID(clazz, "pMessageIdName", "Ljava/lang/String;");
    messageIdNumberField = env->GetFieldID(clazz, "messageIdNumber", "I");
    pMessageField = env->GetFieldID(clazz, "pMessage", "Ljava/lang/String;");
    pQueueLabelsField = env->GetFieldID(clazz, "pQueueLabels",
                                        "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/debug/VkDebugUtilsLabelEXT;");
    pCmdBufLabelsField = env->GetFieldID(clazz, "pCmdBufLabels",
                                         "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/debug/VkDebugUtilsLabelEXT;");
    pObjectsField = env->GetFieldID(clazz, "pObjects",
                                    "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/debug/VkDebugUtilsObjectNameInfoEXT;");
}

jobject
VkDebugUtilsMessengerCallbackDataEXTMutator::toObject(VkDebugUtilsMessengerCallbackDataEXT source) {
    auto constructor = env->GetMethodID(clazz, "<init>", "()V");
    auto newObj = env->NewObject(clazz, constructor);
    env->SetObjectField(newObj, sTypeField,
                        enum_utils::setEnumFromVulkan(env, static_cast<jint>(source.sType),
                                                      "io/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType"));
    // processing Any, Void, Null, Object
    env->SetObjectField(newObj, pNextField, (jobject) source.pNext);
    env->SetIntField(newObj, flagsField, static_cast<jint>(source.flags));
    // process string
    auto pMessageIdName = env->NewStringUTF(source.pMessageIdName);
    env->SetObjectField(newObj, pMessageIdNameField, pMessageIdName);
    env->SetIntField(newObj, messageIdNumberField, static_cast<jint>(source.messageIdNumber));
    // process string
    auto pMessage = env->NewStringUTF(source.pMessage);
    env->SetObjectField(newObj, pMessageField, pMessage);
    // processing non-primitive array
    // array data not yet implemented
    // pQueueLabels
    jclass pQueueLabelsClazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/debug/VkDebugUtilsLabelEXT");
    jobjectArray pQueueLabelsArray = env->NewObjectArray(source.queueLabelCount, pQueueLabelsClazz,
                                                         nullptr);
    for (int i = 0; i < source.queueLabelCount; ++i) {
        auto element = source.pQueueLabels[i];
        auto obj = VkDebugUtilsLabelEXTMutator(env).toObject(element);
        env->SetObjectArrayElement(pQueueLabelsArray, i, obj);
    }
    env->SetObjectField(newObj, pQueueLabelsField, pQueueLabelsArray);
    // processing non-primitive array
    // array data not yet implemented
    // pCmdBufLabels
    jclass pCmdBufLabelsClazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/debug/VkDebugUtilsLabelEXT");
    jobjectArray pCmdBufLabelsArray = env->NewObjectArray(source.cmdBufLabelCount,
                                                          pCmdBufLabelsClazz, nullptr);
    for (int i = 0; i < source.cmdBufLabelCount; ++i) {
        auto element = source.pCmdBufLabels[i];
        auto obj = VkDebugUtilsLabelEXTMutator(env).toObject(element);
        env->SetObjectArrayElement(pCmdBufLabelsArray, i, obj);
    }
    env->SetObjectField(newObj, pCmdBufLabelsField, pCmdBufLabelsArray);
    // processing non-primitive array
    // array data not yet implemented
    // pObjects
    jclass pObjectsClazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/debug/VkDebugUtilsObjectNameInfoEXT");
    jobjectArray pObjectsArray = env->NewObjectArray(source.objectCount, pObjectsClazz, nullptr);
    for (int i = 0; i < source.objectCount; ++i) {
        auto element = source.pObjects[i];
        auto obj = VkDebugUtilsObjectNameInfoEXTMutator(env).toObject(element);
        env->SetObjectArrayElement(pObjectsArray, i, obj);
    }
    env->SetObjectField(newObj, pObjectsField, pObjectsArray);
    return newObj;
}

VkDebugUtilsMessengerCallbackDataEXTMutator::~VkDebugUtilsMessengerCallbackDataEXTMutator() {
    // env->DeleteGlobalRef(clazz);
}

