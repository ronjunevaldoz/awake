/*
 *  VkPipelineCacheCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkPipelineCacheCreateInfoAccessor {
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
    jfieldID pInitialDataField;
public:
    VkPipelineCacheCreateInfoAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        pInitialDataField = env->GetFieldID(clazz, "pInitialData", "[Ljava/lang/Object;");
    }

    VkStructureType getsType() {
        auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
        return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    }

    void getpNext(VkPipelineCacheCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    void getpInitialData(VkPipelineCacheCreateInfo &clazzInfo) {
        auto pInitialDataArray = (jobjectArray) env->GetObjectField(obj, pInitialDataField);
        if (pInitialDataArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pInitialDataArray);
        std::vector<void *> pInitialData;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pInitialDataArray,
                                                                i); // actual type is Object[];
            pInitialData.push_back(element); // type is Any??
        }
        // processing
        auto initialDataSize = static_cast<uint32_t>(pInitialData.size());
        clazzInfo.initialDataSize = initialDataSize;
        // Make a copy of the object to ensure proper memory management;
        auto copy = new const void *[size];
        std::copy(pInitialData.begin(), pInitialData.end(), copy);
        clazzInfo.pInitialData = copy;
    }

    void fromObject(VkPipelineCacheCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        getpInitialData(clazzInfo);  // Object Object Array
    }

    ~VkPipelineCacheCreateInfoAccessor() {
    }

};
