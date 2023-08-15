/*
 *  VkPipelineCacheCreateInfoAccessor.cpp
 *  Vulkan accessor for VkPipelineCacheCreateInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkPipelineCacheCreateInfoAccessor.h>

VkPipelineCacheCreateInfoAccessor::VkPipelineCacheCreateInfoAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    pInitialDataField = env->GetFieldID(clazz, "pInitialData", "[Ljava/lang/Object;");
}

VkStructureType
VkPipelineCacheCreateInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

uint32_t
VkPipelineCacheCreateInfoAccessor::getflags() {
    return (uint32_t)(jint)
    env->GetIntField(obj, flagsField); // primitive
}

void
VkPipelineCacheCreateInfoAccessor::fromObject(VkPipelineCacheCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Object void*
    clazzInfo.flags = getflags(); // Object uint32_t
    getpInitialData(clazzInfo);  // Object Object Array
}

void
VkPipelineCacheCreateInfoAccessor::getpInitialData(VkPipelineCacheCreateInfo &clazzInfo) {
    auto pInitialDataArray = (jobjectArray) env->GetObjectField(obj, pInitialDataField);
    if (pInitialDataArray == nullptr) {
        clazzInfo.initialDataSize = 0;
        clazzInfo.pInitialData = nullptr;
        return;
    }
    auto size = env->GetArrayLength(pInitialDataArray);
    std::vector<void *> pInitialData;
    for (int i = 0; i < size; ++i) {
        auto element = (jobject) env->GetObjectArrayElement(pInitialDataArray,
                                                            i); // actual type is Object[];
        pInitialData.push_back(element); // type is Any??
    }
    // processing array data
    auto initialDataSize = static_cast<uint32_t>(pInitialData.size());
    clazzInfo.initialDataSize = initialDataSize;
    // Make a copy of the object to ensure proper memory management;
    auto copy = new const void *[size];
    std::copy(pInitialData.begin(), pInitialData.end(), copy);
    clazzInfo.pInitialData = copy;
}

void
VkPipelineCacheCreateInfoAccessor::getpNext(VkPipelineCacheCreateInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

VkPipelineCacheCreateInfoAccessor::~VkPipelineCacheCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

