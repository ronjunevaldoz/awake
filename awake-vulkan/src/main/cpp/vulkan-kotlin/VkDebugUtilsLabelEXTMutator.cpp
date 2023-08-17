/*
 *  VkDebugUtilsLabelEXTMutator.cpp
 *  Vulkan mutator for VkDebugUtilsLabelEXT
 *  Created by Ron June Valdoz */

#include <includes/VkDebugUtilsLabelEXTMutator.h>

VkDebugUtilsLabelEXTMutator::VkDebugUtilsLabelEXTMutator(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/debug/VkDebugUtilsLabelEXT");
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    pLabelNameField = env->GetFieldID(clazz, "pLabelName", "Ljava/lang/String;");
    colorField = env->GetFieldID(clazz, "color", "[F");
}

jobject
VkDebugUtilsLabelEXTMutator::toObject(VkDebugUtilsLabelEXT source) {
    auto constructor = env->GetMethodID(clazz, "<init>", "()V");
    auto newObj = env->NewObject(clazz, constructor);
    env->SetObjectField(newObj, sTypeField,
                        enum_utils::setEnumFromVulkan(env, static_cast<jint>(source.sType),
                                                      "io/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType"));
    // processing Any, Void, Null, Object
    env->SetObjectField(newObj, pNextField, (jobject) source.pNext);
    // process string
    auto pLabelName = env->NewStringUTF(source.pLabelName);
    env->SetObjectField(newObj, pLabelNameField, pLabelName);
    // processing primitive array
    jfloatArray color = env->NewFloatArray(4);
    env->SetFloatArrayRegion(color, 0, 4, reinterpret_cast<jfloat *>(source.color ));
    env->SetObjectField(newObj, colorField, color);
    env->DeleteLocalRef(color);
    return newObj;
}

VkDebugUtilsLabelEXTMutator::~VkDebugUtilsLabelEXTMutator() {
    // env->DeleteGlobalRef(clazz);
}

