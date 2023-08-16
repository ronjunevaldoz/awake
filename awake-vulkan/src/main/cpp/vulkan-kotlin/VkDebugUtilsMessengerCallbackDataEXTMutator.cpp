/*
 *  VkDebugUtilsMessengerCallbackDataEXTMutator.cpp
 *  Vulkan mutator for VkDebugUtilsMessengerCallbackDataEXT
 *  Created by Ron June Valdoz */

#include  <includes/VkDebugUtilsMessengerCallbackDataEXTMutator.h>

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
//    ObjectMutator pNextMutator(env);
//    env->SetObjectField(newObj, pNextField, pNextMutator.toObject(source.pNext));
    env->SetIntField(newObj, flagsField, static_cast<jint>(source.flags));
//    env->SetObjectField(newObj, pMessageIdNameField, static_cast<jstring>(source.pMessageIdName));
    env->SetIntField(newObj, messageIdNumberField, static_cast<jint>(source.messageIdNumber));
//    env->SetObjectField(newObj, pMessageField, static_cast<jstring>(source.pMessage));
//    VkDebugUtilsLabelEXT[]Mutator pQueueLabelsMutator(env);
//    env->SetObjectField(newObj, pQueueLabelsField, pQueueLabelsMutator.toObject(source.pQueueLabels));
//    VkDebugUtilsLabelEXT[]Mutator pCmdBufLabelsMutator(env);
//    env->SetObjectField(newObj, pCmdBufLabelsField, pCmdBufLabelsMutator.toObject(source.pCmdBufLabels));
//    VkDebugUtilsObjectNameInfoEXT[]Mutator pObjectsMutator(env);
//    env->SetObjectField(newObj, pObjectsField, pObjectsMutator.toObject(source.pObjects));
    return newObj;
}

VkDebugUtilsMessengerCallbackDataEXTMutator::~VkDebugUtilsMessengerCallbackDataEXTMutator() {
    // env->DeleteGlobalRef(clazz);
}

