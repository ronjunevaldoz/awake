/*
 *  VkRenderPassCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkAttachmentDescriptionAccessor.cpp>
#include <VkSubpassDescriptionAccessor.cpp>
#include <VkSubpassDependencyAccessor.cpp>

class VkRenderPassCreateInfoAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID sTypeField;
private:
    jfieldID pNextField;
private:
    jfieldID flagsField;
private:
    jfieldID pAttachmentsField;
private:
    jfieldID pSubpassesField;
private:
    jfieldID pDependenciesField;
public:
    VkRenderPassCreateInfoAccessor(JNIEnv *env, jobject &obj) {
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

    VkStructureType getsType() {
        auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
        return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    }

    void getpNext(VkRenderPassCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    void getpAttachments(VkRenderPassCreateInfo &clazzInfo) {
        auto pAttachmentsArray = (jobjectArray) env->GetObjectField(obj, pAttachmentsField);
        if (pAttachmentsArray == nullptr) {
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
        // processing
        auto attachmentCount = static_cast<uint32_t>(pAttachments.size());
        clazzInfo.attachmentCount = attachmentCount;
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkAttachmentDescription[size];
        std::copy(pAttachments.begin(), pAttachments.end(), copy);
        clazzInfo.pAttachments = copy;
    }

    void getpSubpasses(VkRenderPassCreateInfo &clazzInfo) {
        auto pSubpassesArray = (jobjectArray) env->GetObjectField(obj, pSubpassesField);
        if (pSubpassesArray == nullptr) {
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
        // processing
        auto subpassCount = static_cast<uint32_t>(pSubpasses.size());
        clazzInfo.subpassCount = subpassCount;
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkSubpassDescription[size];
        std::copy(pSubpasses.begin(), pSubpasses.end(), copy);
        clazzInfo.pSubpasses = copy;
    }

    void getpDependencies(VkRenderPassCreateInfo &clazzInfo) {
        auto pDependenciesArray = (jobjectArray) env->GetObjectField(obj, pDependenciesField);
        if (pDependenciesArray == nullptr) {
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
        // processing
        auto dependencyCount = static_cast<uint32_t>(pDependencies.size());
        clazzInfo.dependencyCount = dependencyCount;
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkSubpassDependency[size];
        std::copy(pDependencies.begin(), pDependencies.end(), copy);
        clazzInfo.pDependencies = copy;
    }

    void fromObject(VkRenderPassCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        getpAttachments(clazzInfo);  // VkAttachmentDescription Object Array
        getpSubpasses(clazzInfo);  // VkSubpassDescription Object Array
        getpDependencies(clazzInfo);  // VkSubpassDependency Object Array
    }

    ~VkRenderPassCreateInfoAccessor() {
    }

};
