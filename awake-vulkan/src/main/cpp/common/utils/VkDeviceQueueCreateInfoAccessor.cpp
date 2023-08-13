/*
 *  VkDeviceQueueCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
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
    VkDeviceQueueCreateInfoAccessor(JNIEnv *env, jobject &obj) {
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

    void getpNext(VkDeviceQueueCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
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

    void getpQueuePriorities(VkDeviceQueueCreateInfo &clazzInfo) {
        auto pQueuePrioritiesArray = (jfloatArray) env->GetObjectField(obj, pQueuePrioritiesField);
        if (pQueuePrioritiesArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pQueuePrioritiesArray);
        // primitive array?
        std::vector<float> pQueuePriorities(size);
        env->GetFloatArrayRegion(pQueuePrioritiesArray, 0, size,
                                 reinterpret_cast<jfloat *>(pQueuePriorities.data()));
        // processing
        // no array size generated
        // Make a copy of the data to ensure proper memory management;
        auto copy = new float[size];
        std::copy(pQueuePriorities.begin(), pQueuePriorities.end(), copy);
        clazzInfo.pQueuePriorities = copy;
    }

    void fromObject(VkDeviceQueueCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        clazzInfo.queueFamilyIndex = getqueueFamilyIndex(); // Object int32_t
        clazzInfo.queueCount = getqueueCount(); // Object uint32_t
        getpQueuePriorities(clazzInfo);  // float Object Array
    }

    ~VkDeviceQueueCreateInfoAccessor() {
    }

};
