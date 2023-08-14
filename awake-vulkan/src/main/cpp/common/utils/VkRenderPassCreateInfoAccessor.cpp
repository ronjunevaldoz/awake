/*
 *  VkRenderPassCreateInfoAccessor.cpp
 *  Vulkan accessor for VkRenderPassCreateInfo
 *  Created by Ron June Valdoz */

#include  <includes/VkRenderPassCreateInfoAccessor.h>

VkRenderPassCreateInfoAccessor::VkRenderPassCreateInfoAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    pAttachmentsField = env->GetFieldID(clazz, "pAttachments",
                                        "[Lio/github/ronjunevaldoz/awake/vulkan/models/VkAttachmentDescription;");
    pSubpassesField = env->GetFieldID(clazz, "pSubpasses",
                                      "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/VkSubpassDescription;");
    pDependenciesField = env->GetFieldID(clazz, "pDependencies",
                                         "[Lio/github/ronjunevaldoz/awake/vulkan/models/VkSubpassDependency;");
}

VkStructureType
VkRenderPassCreateInfoAccessor::getsType() {
    auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
    return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
}

uint32_t
VkRenderPassCreateInfoAccessor::getflags() {
    return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
}

void
VkRenderPassCreateInfoAccessor::getpNext(VkRenderPassCreateInfo &clazzInfo) {
    auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
    clazzInfo.pNext = ref;
}

void
VkRenderPassCreateInfoAccessor::getpAttachments(VkRenderPassCreateInfo &clazzInfo) {
    auto pAttachmentsArray = (jobjectArray) env->GetObjectField(obj, pAttachmentsField);
    if (pAttachmentsArray == nullptr) {
        clazzInfo.attachmentCount = 0;
        clazzInfo.pAttachments = nullptr;
        return;
    }
    auto size = env->GetArrayLength(pAttachmentsArray);
    std::vector<VkAttachmentDescription> pAttachments;
    for (int i = 0; i < size; ++i) {
        auto element = (jobject) env->GetObjectArrayElement(pAttachmentsArray,
                                                            i); // actual type is VkAttachmentDescription[];
        // experimental optimize accessor
        VkAttachmentDescriptionAccessor accessor(env, element);
        VkAttachmentDescription ref{};
        accessor.fromObject(ref);
        pAttachments.push_back(ref);
    }
    // processing array data
    auto attachmentCount = static_cast<uint32_t>(pAttachments.size());
    clazzInfo.attachmentCount = attachmentCount;
    // Make a copy of the object to ensure proper memory management;
    auto copy = new VkAttachmentDescription[size];
    std::copy(pAttachments.begin(), pAttachments.end(), copy);
    clazzInfo.pAttachments = copy;
}

void
VkRenderPassCreateInfoAccessor::getpDependencies(VkRenderPassCreateInfo &clazzInfo) {
    auto pDependenciesArray = (jobjectArray) env->GetObjectField(obj, pDependenciesField);
    if (pDependenciesArray == nullptr) {
        clazzInfo.dependencyCount = 0;
        clazzInfo.pDependencies = nullptr;
        return;
    }
    auto size = env->GetArrayLength(pDependenciesArray);
    std::vector<VkSubpassDependency> pDependencies;
    for (int i = 0; i < size; ++i) {
        auto element = (jobject) env->GetObjectArrayElement(pDependenciesArray,
                                                            i); // actual type is VkSubpassDependency[];
        // experimental optimize accessor
        VkSubpassDependencyAccessor accessor(env, element);
        VkSubpassDependency ref{};
        accessor.fromObject(ref);
        pDependencies.push_back(ref);
    }
    // processing array data
    auto dependencyCount = static_cast<uint32_t>(pDependencies.size());
    clazzInfo.dependencyCount = dependencyCount;
    // Make a copy of the object to ensure proper memory management;
    auto copy = new VkSubpassDependency[size];
    std::copy(pDependencies.begin(), pDependencies.end(), copy);
    clazzInfo.pDependencies = copy;
}

void
VkRenderPassCreateInfoAccessor::fromObject(VkRenderPassCreateInfo &clazzInfo) {
    clazzInfo.sType = getsType(); // Enum VkStructureType
    getpNext(clazzInfo); // Object void*
    clazzInfo.flags = getflags(); // Object uint32_t
    getpAttachments(clazzInfo);  // VkAttachmentDescription Object Array
    getpSubpasses(clazzInfo);  // VkSubpassDescription Object Array
    getpDependencies(clazzInfo);  // VkSubpassDependency Object Array
}

void
VkRenderPassCreateInfoAccessor::getpSubpasses(VkRenderPassCreateInfo &clazzInfo) {
    auto pSubpassesArray = (jobjectArray) env->GetObjectField(obj, pSubpassesField);
    if (pSubpassesArray == nullptr) {
        clazzInfo.subpassCount = 0;
        clazzInfo.pSubpasses = nullptr;
        return;
    }
    auto size = env->GetArrayLength(pSubpassesArray);
    std::vector<VkSubpassDescription> pSubpasses;
    for (int i = 0; i < size; ++i) {
        auto element = (jobject) env->GetObjectArrayElement(pSubpassesArray,
                                                            i); // actual type is VkSubpassDescription[];
        // experimental optimize accessor
        VkSubpassDescriptionAccessor accessor(env, element);
        VkSubpassDescription ref{};
        accessor.fromObject(ref);
        pSubpasses.push_back(ref);
    }
    // processing array data
    auto subpassCount = static_cast<uint32_t>(pSubpasses.size());
    clazzInfo.subpassCount = subpassCount;
    // Make a copy of the object to ensure proper memory management;
    auto copy = new VkSubpassDescription[size];
    std::copy(pSubpasses.begin(), pSubpasses.end(), copy);
    clazzInfo.pSubpasses = copy;
}

VkRenderPassCreateInfoAccessor::~VkRenderPassCreateInfoAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

