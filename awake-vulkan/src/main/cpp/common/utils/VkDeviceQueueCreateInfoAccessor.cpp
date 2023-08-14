/*
 *  VkDeviceQueueCreateInfoAccessor.cpp
 *  Vulkan accessor for VkDeviceQueueCreateInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkDeviceQueueCreateInfoAccessor.h>

VkDeviceQueueCreateInfoAccessor::VkDeviceQueueCreateInfoAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    queueFamilyIndexField = env->GetFieldID(clazz, "queueFamilyIndex", "I");
    queueCountField = env->GetFieldID(clazz, "queueCount", "I");
    pQueuePrioritiesField = env->GetFieldID(clazz, "pQueuePriorities", "[F");
}

VkStructureType
VkDeviceQueueCreateInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

uint32_t
VkDeviceQueueCreateInfoAccessor::getflags() {
    return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
}

int32_t
VkDeviceQueueCreateInfoAccessor::getqueueFamilyIndex() {
    return (int32_t) (jint) env->GetIntField(obj, queueFamilyIndexField); // primitive
}

void
VkDeviceQueueCreateInfoAccessor::getpQueuePriorities(VkDeviceQueueCreateInfo &clazzInfo) {
    auto pQueuePrioritiesArray = (jfloatArray) env->GetObjectField(obj, pQueuePrioritiesField);
    if (pQueuePrioritiesArray == nullptr) {
        clazzInfo.pQueuePriorities = nullptr;
        return;
    }
    auto size = env->GetArrayLength(pQueuePrioritiesArray);
    // primitive array?
    std::vector<float> pQueuePriorities(size);
    env->GetFloatArrayRegion(pQueuePrioritiesArray, 0, size,
                             reinterpret_cast<jfloat *>(pQueuePriorities.data()));
    // processing array data
    // no array size generated
    // Make a copy of the data to ensure proper memory management;
    auto copy = new float[size];
    std::copy(pQueuePriorities.begin(), pQueuePriorities.end(), copy);
    clazzInfo.pQueuePriorities = copy;
}

uint32_t
VkDeviceQueueCreateInfoAccessor::getqueueCount() {
    return (uint32_t) (jint) env->GetIntField(obj, queueCountField); // primitive
}

void
VkDeviceQueueCreateInfoAccessor::fromObject(VkDeviceQueueCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Object void*
    clazzInfo.flags = getflags(); // Object uint32_t
    clazzInfo.queueFamilyIndex = getqueueFamilyIndex(); // Object int32_t
    clazzInfo.queueCount = getqueueCount(); // Object uint32_t
    getpQueuePriorities(clazzInfo);  // float Object Array
}

void
VkDeviceQueueCreateInfoAccessor::getpNext(VkDeviceQueueCreateInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

VkDeviceQueueCreateInfoAccessor::~VkDeviceQueueCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

