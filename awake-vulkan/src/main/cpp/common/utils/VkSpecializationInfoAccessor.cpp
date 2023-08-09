/*
 *  VkSpecializationInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
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
    VkSpecializationInfoAccessor(JNIEnv *env, jobject obj) {
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

    std::vector<VkSpecializationMapEntry> getpMapEntries() {
        auto pMapEntriesArray = (jobjectArray) env->GetObjectField(obj, pMapEntriesField);
        if (pMapEntriesArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pMapEntriesArray);
        std::vector<VkSpecializationMapEntry> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pMapEntriesArray,
                                                                i); // actual type is VkSpecializationMapEntry[];
            // experimental optimize accessor
            VkSpecializationMapEntryAccessor accessor(env, element);
            array.push_back(accessor.fromObject());
        }
        return array;
    }

    uint64_t getdataSize() {
        return (uint64_t) (jlong) env->GetLongField(obj, dataSizeField); // primitive
    }

    std::vector<void *> getpData() {
        auto pDataArray = (jobjectArray) env->GetObjectField(obj, pDataField);
        if (pDataArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pDataArray);
        std::vector<void *> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pDataArray,
                                                                i); // actual type is Object[];
            array.push_back(element); // type is Any??
        }
        return array;
    }

    VkSpecializationInfo fromObject() {
        VkSpecializationInfo clazzInfo{};
        clazzInfo.mapEntryCount = getmapEntryCount(); // Object
        clazzInfo.pMapEntries = getpMapEntries().data(); // Object Array
        clazzInfo.dataSize = getdataSize(); // Object
        clazzInfo.pData = getpData().data(); // Object Array
        return clazzInfo;
    }

    ~VkSpecializationInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
