/*
 *  VkDeviceCreateInfoAccessor.cpp
 *  Vulkan accessor for VkDeviceCreateInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkDeviceCreateInfoAccessor.h>

VkDeviceCreateInfoAccessor::VkDeviceCreateInfoAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
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

VkStructureType
VkDeviceCreateInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

uint32_t
VkDeviceCreateInfoAccessor::getflags() {
    return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
}

void
VkDeviceCreateInfoAccessor::fromObject(VkDeviceCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Other void*
    clazzInfo.flags = getflags(); // Primitive uint32_t
    getpQueueCreateInfos(clazzInfo);  // VkDeviceQueueCreateInfo Object Array
    getppEnabledLayerNames(clazzInfo);  // String Object Array
    getppEnabledExtensionNames(clazzInfo);  // String Object Array
    getpEnabledFeatures(clazzInfo);  // VkPhysicalDeviceFeatures Object Array
}

void
VkDeviceCreateInfoAccessor::getpNext(VkDeviceCreateInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

void
VkDeviceCreateInfoAccessor::getppEnabledLayerNames(VkDeviceCreateInfo &clazzInfo) {
    auto ppEnabledLayerNamesArray = (jobjectArray) env->GetObjectField(obj,
                                                                       ppEnabledLayerNamesField);
    if (ppEnabledLayerNamesArray == nullptr) {
        clazzInfo.enabledLayerCount = 0;
        clazzInfo.ppEnabledLayerNames = nullptr;
        return;
    }
    auto size = env->GetArrayLength(ppEnabledLayerNamesArray);
    std::vector<const char *> ppEnabledLayerNames;
    for (int i = 0; i < size; ++i) {
        auto element = (jstring) env->GetObjectArrayElement(ppEnabledLayerNamesArray,
                                                            i); // actual type is String[];
        auto str = env->GetStringUTFChars(element, nullptr);
        auto result = strdup(str); // Allocate memory and copy the string
        env->ReleaseStringUTFChars(element, str); // Release the local string reference
        ppEnabledLayerNames.push_back(result);
    }
    // processing array data
    auto enabledLayerCount = static_cast<uint32_t>(ppEnabledLayerNames.size());
    clazzInfo.enabledLayerCount = enabledLayerCount;
    // Make a copy of the object to ensure proper memory management;
    auto copy = new const char *[size];
    std::copy(ppEnabledLayerNames.begin(), ppEnabledLayerNames.end(), copy);
    clazzInfo.ppEnabledLayerNames = copy;
}

void
VkDeviceCreateInfoAccessor::getppEnabledExtensionNames(VkDeviceCreateInfo &clazzInfo) {
    auto ppEnabledExtensionNamesArray = (jobjectArray) env->GetObjectField(obj,
                                                                           ppEnabledExtensionNamesField);
    if (ppEnabledExtensionNamesArray == nullptr) {
        clazzInfo.enabledExtensionCount = 0;
        clazzInfo.ppEnabledExtensionNames = nullptr;
        return;
    }
    auto size = env->GetArrayLength(ppEnabledExtensionNamesArray);
    std::vector<const char *> ppEnabledExtensionNames;
    for (int i = 0; i < size; ++i) {
        auto element = (jstring) env->GetObjectArrayElement(ppEnabledExtensionNamesArray,
                                                            i); // actual type is String[];
        auto str = env->GetStringUTFChars(element, nullptr);
        auto result = strdup(str); // Allocate memory and copy the string
        env->ReleaseStringUTFChars(element, str); // Release the local string reference
        ppEnabledExtensionNames.push_back(result);
    }
    // processing array data
    auto enabledExtensionCount = static_cast<uint32_t>(ppEnabledExtensionNames.size());
    clazzInfo.enabledExtensionCount = enabledExtensionCount;
    // Make a copy of the object to ensure proper memory management;
    auto copy = new const char *[size];
    std::copy(ppEnabledExtensionNames.begin(), ppEnabledExtensionNames.end(), copy);
    clazzInfo.ppEnabledExtensionNames = copy;
}

void
VkDeviceCreateInfoAccessor::getpEnabledFeatures(VkDeviceCreateInfo &clazzInfo) {
    auto pEnabledFeaturesArray = (jobjectArray) env->GetObjectField(obj, pEnabledFeaturesField);
    if (pEnabledFeaturesArray == nullptr) {
        clazzInfo.pEnabledFeatures = nullptr;
        return;
    }
    auto size = env->GetArrayLength(pEnabledFeaturesArray);
    std::vector<VkPhysicalDeviceFeatures> pEnabledFeatures;
    for (int i = 0; i < size; ++i) {
        auto element = (jobject) env->GetObjectArrayElement(pEnabledFeaturesArray,
                                                            i); // actual type is VkPhysicalDeviceFeatures[];
        // experimental optimize accessor
        VkPhysicalDeviceFeaturesAccessor accessor(env, element);
        VkPhysicalDeviceFeatures ref{};
        accessor.fromObject(ref);
        pEnabledFeatures.push_back(ref);
    }
    // processing array data
    // no array size generated
    // Make a copy of the object to ensure proper memory management;
    auto copy = new VkPhysicalDeviceFeatures[size];
    std::copy(pEnabledFeatures.begin(), pEnabledFeatures.end(), copy);
    clazzInfo.pEnabledFeatures = copy;
}

void
VkDeviceCreateInfoAccessor::getpQueueCreateInfos(VkDeviceCreateInfo &clazzInfo) {
    auto pQueueCreateInfosArray = (jobjectArray) env->GetObjectField(obj, pQueueCreateInfosField);
    if (pQueueCreateInfosArray == nullptr) {
        clazzInfo.queueCreateInfoCount = 0;
        clazzInfo.pQueueCreateInfos = nullptr;
        return;
    }
    auto size = env->GetArrayLength(pQueueCreateInfosArray);
    std::vector<VkDeviceQueueCreateInfo> pQueueCreateInfos;
    for (int i = 0; i < size; ++i) {
        auto element = (jobject) env->GetObjectArrayElement(pQueueCreateInfosArray,
                                                            i); // actual type is VkDeviceQueueCreateInfo[];
        // experimental optimize accessor
        VkDeviceQueueCreateInfoAccessor accessor(env, element);
        VkDeviceQueueCreateInfo ref{};
        accessor.fromObject(ref);
        pQueueCreateInfos.push_back(ref);
    }
    // processing array data
    auto queueCreateInfoCount = static_cast<uint32_t>(pQueueCreateInfos.size());
    clazzInfo.queueCreateInfoCount = queueCreateInfoCount;
    // Make a copy of the object to ensure proper memory management;
    auto copy = new VkDeviceQueueCreateInfo[size];
    std::copy(pQueueCreateInfos.begin(), pQueueCreateInfos.end(), copy);
    clazzInfo.pQueueCreateInfos = copy;
}

VkDeviceCreateInfoAccessor::~VkDeviceCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

