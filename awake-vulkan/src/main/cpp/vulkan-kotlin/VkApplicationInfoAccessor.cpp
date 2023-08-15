/*
 *  VkApplicationInfoAccessor.cpp
 *  Vulkan accessor for VkApplicationInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkApplicationInfoAccessor.h>

VkApplicationInfoAccessor::VkApplicationInfoAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    pApplicationNameField = env->GetFieldID(clazz, "pApplicationName", "Ljava/lang/String;");
    applicationVersionField = env->GetFieldID(clazz, "applicationVersion", "I");
    pEngineNameField = env->GetFieldID(clazz, "pEngineName", "Ljava/lang/String;");
    engineVersionField = env->GetFieldID(clazz, "engineVersion", "I");
    apiVersionField = env->GetFieldID(clazz, "apiVersion", "I");
}

VkStructureType
VkApplicationInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

uint32_t
VkApplicationInfoAccessor::getapplicationVersion() {
    return (uint32_t)(jint)
    env->GetIntField(obj, applicationVersionField); // primitive
}

void
VkApplicationInfoAccessor::fromObject(VkApplicationInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Object void*
    getpApplicationName(clazzInfo); // Object const char*
    clazzInfo.applicationVersion = getapplicationVersion(); // Object uint32_t
    getpEngineName(clazzInfo); // Object const char*
    clazzInfo.engineVersion = getengineVersion(); // Object uint32_t
    clazzInfo.apiVersion = getapiVersion(); // Object uint32_t
}

void
VkApplicationInfoAccessor::getpNext(VkApplicationInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

void
VkApplicationInfoAccessor::getpApplicationName(VkApplicationInfo &clazzInfo) {
    auto pApplicationNameObj = (jstring) env->GetObjectField(obj, pApplicationNameField);
    auto str = (const char *) env->GetStringUTFChars(pApplicationNameObj, nullptr);
    auto result = strdup(str); // Allocate memory and copy the string
    env->ReleaseStringUTFChars(pApplicationNameObj, str); // Release the local string reference
    clazzInfo.pApplicationName = result;
}

uint32_t
VkApplicationInfoAccessor::getapiVersion() {
    return (uint32_t)(jint)
    env->GetIntField(obj, apiVersionField); // primitive
}

uint32_t
VkApplicationInfoAccessor::getengineVersion() {
    return (uint32_t)(jint)
    env->GetIntField(obj, engineVersionField); // primitive
}

void
VkApplicationInfoAccessor::getpEngineName(VkApplicationInfo &clazzInfo) {
    auto pEngineNameObj = (jstring) env->GetObjectField(obj, pEngineNameField);
    auto str = (const char *) env->GetStringUTFChars(pEngineNameObj, nullptr);
    auto result = strdup(str); // Allocate memory and copy the string
    env->ReleaseStringUTFChars(pEngineNameObj, str); // Release the local string reference
    clazzInfo.pEngineName = result;
}

VkApplicationInfoAccessor::~VkApplicationInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

