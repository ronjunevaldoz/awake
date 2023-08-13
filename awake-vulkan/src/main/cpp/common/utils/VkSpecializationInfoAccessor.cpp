/*
 *  VkSpecializationInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkSpecializationMapEntryAccessor.cpp>

class VkSpecializationInfoAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID mapEntryCountField;
private:
    jfieldID pMapEntriesField;
private:
    jfieldID dataSizeField;
private:
    jfieldID pDataField;
public:
    VkSpecializationInfoAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        mapEntryCountField = env->GetFieldID(clazz, "mapEntryCount", "I");
        pMapEntriesField = env->GetFieldID(clazz, "pMapEntries",
                                           "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkSpecializationMapEntry;");
        dataSizeField = env->GetFieldID(clazz, "dataSize", "J");
        pDataField = env->GetFieldID(clazz, "pData", "[Ljava/lang/Object;");
    }

    uint32_t getmapEntryCount() {
        return (uint32_t) (jint) env->GetIntField(obj, mapEntryCountField); // primitive
    }

    void getpMapEntries(VkSpecializationInfo &clazzInfo) {
        auto pMapEntriesArray = (jobjectArray) env->GetObjectField(obj, pMapEntriesField);
        if (pMapEntriesArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pMapEntriesArray);
        std::vector<VkSpecializationMapEntry> pMapEntries;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pMapEntriesArray,
                                                                i); // actual type is VkSpecializationMapEntry[];
            // experimental optimize accessor
            VkSpecializationMapEntryAccessor accessor(env, element);
            VkSpecializationMapEntry ref{};
            accessor.fromObject(ref);
            pMapEntries.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkSpecializationMapEntry[size];
        std::copy(pMapEntries.begin(), pMapEntries.end(), copy);
        clazzInfo.pMapEntries = copy;
    }

    uint64_t getdataSize() {
        return (uint64_t) (jlong) env->GetLongField(obj, dataSizeField); // primitive
    }

    void getpData(VkSpecializationInfo &clazzInfo) {
        auto pDataArray = (jobjectArray) env->GetObjectField(obj, pDataField);
        if (pDataArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pDataArray);
        std::vector<void *> pData;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pDataArray,
                                                                i); // actual type is Object[];
            pData.push_back(element); // type is Any??
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new const void *[size];
        std::copy(pData.begin(), pData.end(), copy);
        clazzInfo.pData = copy;
    }

    void fromObject(VkSpecializationInfo &clazzInfo) {
        clazzInfo.mapEntryCount = getmapEntryCount(); // Object uint32_t
        getpMapEntries(clazzInfo);  // VkSpecializationMapEntry Object Array
        clazzInfo.dataSize = getdataSize(); // Object uint64_t
        getpData(clazzInfo);  // Object Object Array
    }

    ~VkSpecializationInfoAccessor() {
    }

};
