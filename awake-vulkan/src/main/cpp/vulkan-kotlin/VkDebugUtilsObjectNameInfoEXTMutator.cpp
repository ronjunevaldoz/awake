/*
 *  VkDebugUtilsObjectNameInfoEXTMutator.cpp
 *  Vulkan mutator for VkDebugUtilsObjectNameInfoEXT
 *  Created by Ron June Valdoz */

#include <includes/VkDebugUtilsObjectNameInfoEXTMutator.h>

VkDebugUtilsObjectNameInfoEXTMutator::VkDebugUtilsObjectNameInfoEXTMutator(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/debug/VkDebugUtilsObjectNameInfoEXT");
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    objectTypeField = env->GetFieldID(clazz, "objectType",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkObjectType;");
    objectHandleField = env->GetFieldID(clazz, "objectHandle", "J");
    pObjectNameField = env->GetFieldID(clazz, "pObjectName", "Ljava/lang/String;");
}

jobject
VkDebugUtilsObjectNameInfoEXTMutator::toObject(VkDebugUtilsObjectNameInfoEXT source) {
    auto constructor = env->GetMethodID(clazz, "<init>", "()V");
    auto newObj = env->NewObject(clazz, constructor);
    env->SetObjectField(newObj, sTypeField,
                        enum_utils::setEnumFromVulkan(env, static_cast<jint>(source.sType),
                                                      "io/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType"));
    // processing Any, Void, Null, Object
    env->SetObjectField(newObj, pNextField, (jobject) source.pNext);
    env->SetObjectField(newObj, objectTypeField,
                        enum_utils::setEnumFromVulkan(env, static_cast<jint>(source.objectType),
                                                      "io/github/ronjunevaldoz/awake/vulkan/enums/VkObjectType"));
    env->SetLongField(newObj, objectHandleField, static_cast<jlong>(source.objectHandle));
    // process string
    auto pObjectName = env->NewStringUTF(source.pObjectName);
    env->SetObjectField(newObj, pObjectNameField, pObjectName);
    return newObj;
}

VkDebugUtilsObjectNameInfoEXTMutator::~VkDebugUtilsObjectNameInfoEXTMutator() {
    // env->DeleteGlobalRef(clazz);
}

