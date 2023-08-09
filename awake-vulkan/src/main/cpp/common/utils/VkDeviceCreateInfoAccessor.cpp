/*
 *  VkDeviceCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkDeviceQueueCreateInfoAccessor.cpp>
#include <VkPhysicalDeviceFeaturesAccessor.cpp>

class VkDeviceCreateInfoAccessor {
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
    jfieldID pQueueCreateInfosField;
private:
    jfieldID ppEnabledLayerNamesField;
private:
    jfieldID ppEnabledExtensionNamesField;
private:
    jfieldID pEnabledFeaturesField;
public:
    VkDeviceCreateInfoAccessor(JNIEnv *env, jobject obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        pQueueCreateInfosField = env->GetFieldID(clazz, "pQueueCreateInfos",
                                                 "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/VkDeviceQueueCreateInfo;");
        ppEnabledLayerNamesField = env->GetFieldID(clazz, "ppEnabledLayerNames",
                                                   "[Ljava/lang/String;");
        ppEnabledExtensionNamesField = env->GetFieldID(clazz, "ppEnabledExtensionNames",
                                                       "[Ljava/lang/String;");
        pEnabledFeaturesField = env->GetFieldID(clazz, "pEnabledFeatures",
                                                "[Lio/github/ronjunevaldoz/awake/vulkan/physicaldevice/VkPhysicalDeviceFeatures;");
    }

    VkStructureType getsType() {
        auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
        return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    }

    void *getpNext() {
        return (void *) (jobject) env->GetObjectField(obj, pNextField); // Object??
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    std::vector<VkDeviceQueueCreateInfo> getpQueueCreateInfos() {
        auto pQueueCreateInfosArray = (jobjectArray) env->GetObjectField(obj,
                                                                         pQueueCreateInfosField);
        if (pQueueCreateInfosArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pQueueCreateInfosArray);
        std::vector<VkDeviceQueueCreateInfo> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pQueueCreateInfosArray,
                                                                i); // actual type is VkDeviceQueueCreateInfo[];
            // experimental optimize accessor
            VkDeviceQueueCreateInfoAccessor accessor(env, element);
            array.push_back(accessor.fromObject());
        }
        return array;
    }

    std::vector<const char *> getppEnabledLayerNames() {
        auto ppEnabledLayerNamesArray = (jobjectArray) env->GetObjectField(obj,
                                                                           ppEnabledLayerNamesField);
        if (ppEnabledLayerNamesArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(ppEnabledLayerNamesArray);
        std::vector<const char *> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jstring) env->GetObjectArrayElement(ppEnabledLayerNamesArray,
                                                                i); // actual type is String[](ppEnabledLayerNamesArray, i);
            auto str = env->GetStringUTFChars(element, nullptr);
            auto result = strdup(str); // Allocate memory and copy the string
            env->ReleaseStringUTFChars(element, str); // Release the local string reference
            array.push_back(result);
        }
        return array;
    }

    std::vector<const char *> getppEnabledExtensionNames() {
        auto ppEnabledExtensionNamesArray = (jobjectArray) env->GetObjectField(obj,
                                                                               ppEnabledExtensionNamesField);
        if (ppEnabledExtensionNamesArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(ppEnabledExtensionNamesArray);
        std::vector<const char *> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jstring) env->GetObjectArrayElement(ppEnabledExtensionNamesArray,
                                                                i); // actual type is String[](ppEnabledLayerNamesArray, i);
            auto str = env->GetStringUTFChars(element, nullptr);
            auto result = strdup(str); // Allocate memory and copy the string
            env->ReleaseStringUTFChars(element, str); // Release the local string reference
            array.push_back(result);
        }
        return array;
    }

    std::vector<VkPhysicalDeviceFeatures> getpEnabledFeatures() {
        auto pEnabledFeaturesArray = (jobjectArray) env->GetObjectField(obj, pEnabledFeaturesField);
        if (pEnabledFeaturesArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pEnabledFeaturesArray);
        std::vector<VkPhysicalDeviceFeatures> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pEnabledFeaturesArray,
                                                                i); // actual type is VkPhysicalDeviceFeatures[];
            // experimental optimize accessor
            VkPhysicalDeviceFeaturesAccessor accessor(env, element);
            array.push_back(accessor.fromObject());
        }
        return array;
    }

    VkDeviceCreateInfo fromObject() {
        VkDeviceCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.pQueueCreateInfos = getpQueueCreateInfos().data(); // Object Array
        clazzInfo.ppEnabledLayerNames = getppEnabledLayerNames().data(); // Object Array
        clazzInfo.ppEnabledExtensionNames = getppEnabledExtensionNames().data(); // Object Array
        clazzInfo.pEnabledFeatures = getpEnabledFeatures().data(); // Object Array
        return clazzInfo;
    }

    ~VkDeviceCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
