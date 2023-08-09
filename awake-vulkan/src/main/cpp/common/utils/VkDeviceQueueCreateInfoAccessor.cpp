/*
 *  VkDeviceQueueCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkDeviceQueueCreateInfoAccessor {
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
    jfieldID queueFamilyIndexField;
private:
    jfieldID queueCountField;
private:
    jfieldID pQueuePrioritiesField;
public:
    VkDeviceQueueCreateInfoAccessor(JNIEnv *env, jobject obj) {
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

    int32_t getqueueFamilyIndex() {
        return (int32_t) (jint) env->GetIntField(obj, queueFamilyIndexField); // primitive
    }

    uint32_t getqueueCount() {
        return (uint32_t) (jint) env->GetIntField(obj, queueCountField); // primitive
    }

    std::vector<float> getpQueuePriorities() {
        auto pQueuePrioritiesArray = (jfloatArray) env->GetObjectField(obj, pQueuePrioritiesField);
        if (pQueuePrioritiesArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pQueuePrioritiesArray);
        std::vector<float> array(size);
        env->GetFloatArrayRegion(pQueuePrioritiesArray, 0, size,
                                 reinterpret_cast<jfloat *>(array.data()));
        return array;
    }

    VkDeviceQueueCreateInfo fromObject() {
        VkDeviceQueueCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.queueFamilyIndex = getqueueFamilyIndex(); // Object
        clazzInfo.queueCount = getqueueCount(); // Object
        auto pQueuePriorities = getpQueuePriorities();  // float Primitive Array
        std::copy(pQueuePriorities.begin(), pQueuePriorities.end(), clazzInfo.pQueuePriorities);
        return clazzInfo;
    }

    ~VkDeviceQueueCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
