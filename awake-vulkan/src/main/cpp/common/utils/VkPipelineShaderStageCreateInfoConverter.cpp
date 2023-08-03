//
// Created by Ron June Valdoz on 8/2/23.
//

#include <vector>
#include "VkPipelineShaderStageCreateInfoConverter.h"
#include "enum_utils.h"

VkPipelineShaderStageCreateInfoConverter::VkPipelineShaderStageCreateInfoConverter(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/VkPipelineShaderStageCreateInfo");

    sTypeField = env->GetFieldID(clazz, "sType",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    flagsField = env->GetFieldID(clazz, "flags", "I");
    stageField = env->GetFieldID(clazz, "stage",
                                 "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkShaderStageFlagBits;");
    moduleField = env->GetFieldID(clazz, "module", "J");
    pNameField = env->GetFieldID(clazz, "pName", "Ljava/lang/String;");
    pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
    pSpecializationInfoField = env->GetFieldID(clazz, "pSpecializationInfo",
                                               "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/VkSpecializationInfo;");

}

VkPipelineShaderStageCreateInfo
VkPipelineShaderStageCreateInfoConverter::fromObject(jobject createInfo) {
    jobject sTypeObj = env->GetObjectField(createInfo, sTypeField);
    jobject stageObj = env->GetObjectField(createInfo, stageField);
    auto specializationInfoListObj = (jobjectArray) env->GetObjectField(createInfo,
                                                                        pSpecializationInfoField);

    auto sType = static_cast<VkStructureType>(enum_utils::getEnumFromObject(env, sTypeObj));
    auto pNext = env->GetObjectField(createInfo,
                                     pNextField);
    VkPipelineShaderStageCreateFlags flags = env->GetIntField(createInfo, flagsField);

    auto stage = static_cast<VkShaderStageFlagBits>(enum_utils::getEnumFromObject(env, stageObj));

    auto module = reinterpret_cast<VkShaderModule>(env->GetLongField(createInfo, moduleField));
    auto pNameString = (jstring) env->GetObjectField(createInfo, pNameField);
    const char *pName = env->GetStringUTFChars(pNameString, nullptr);
    std::vector<VkSpecializationInfo> specializationInfos = fromSpecializationInfoList(
            specializationInfoListObj);

    // Prepare VkPipelineShaderStageCreateInfo
    VkPipelineShaderStageCreateInfo info{};
    info.sType = sType;
    info.pNext = pNext;
    info.flags = flags;
    info.stage = stage;
    info.module = module;
    info.pName = pName; // Replace this with actual code to read pName field if needed
    if (!specializationInfos.empty()) {
        // optional??
        info.pSpecializationInfo = specializationInfos.data();
    }
    env->DeleteLocalRef(sTypeObj);
    env->DeleteLocalRef(stageObj);
//    env->DeleteLocalRef(pNameString);
//    env->DeleteLocalRef(specializationInfoListObj);

    return info;
}

// Helper function to read VkSpecializationInfo from a List<VkSpecializationInfo> object
std::vector<VkSpecializationInfo>
VkPipelineShaderStageCreateInfoConverter::fromSpecializationInfoList(
        jobjectArray specializationInfoListObj) {
    std::vector<VkSpecializationInfo> specializationInfos;

    // Get the class and method IDs for VkSpecializationInfo class
    jclass specializationInfoClass = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/info/VkSpecializationInfo");
    jfieldID mapEntryCountField = env->GetFieldID(specializationInfoClass, "mapEntryCount",
                                                  "I");
    jfieldID pMapEntriesField = env->GetFieldID(specializationInfoClass, "pMapEntries",
                                                "Ljava/util/List;");
    jfieldID dataSizeField = env->GetFieldID(specializationInfoClass, "dataSize", "J");
    jfieldID pDataField = env->GetFieldID(specializationInfoClass, "pData",
                                          "[Ljava/lang/Object;");

    // Iterate through the List and populate specializationInfos vector
    jsize size = env->GetArrayLength(specializationInfoListObj);
    for (int i = 0; i < size; i++) {
        jobject specializationInfoObj = env->GetObjectArrayElement(specializationInfoListObj, i);

        // copy mapEntry
        auto mapEntriesObj = (jobjectArray) env->GetObjectField(specializationInfoObj,
                                                                pMapEntriesField);
        int mapEntriesCount = env->GetArrayLength(mapEntriesObj);
        std::vector<VkSpecializationMapEntry> mapEntries(mapEntriesCount);
        for (int j = 0; j < mapEntriesCount; j++) {
            jobject mapEntryObj = env->GetObjectArrayElement(mapEntriesObj, j);

        }
        // copy pData
        // TODO check what should be the type is it object or byte array??
        auto pDataObj = (jobjectArray) env->GetObjectField(specializationInfoObj, pDataField);
//        jbyte *pData = nullptr;
//        jsize dataSize = env->GetArrayLength(pDataObj);
//        env->GetByteArrayRegion(pDataObj, 0, dataSize, pData);

        VkSpecializationInfo specializationInfo;
        specializationInfo.mapEntryCount = 0;//static_cast<size_t>(mapEntries.size());
        specializationInfo.pMapEntries = nullptr;//mapEntries.data();
        specializationInfo.dataSize = 0;//static_cast<size_t>(dataSize);
        specializationInfo.pData = nullptr;//reinterpret_cast<const void *>(pData);
        // Add the populated specializationInfo to the specializationInfos vector
        specializationInfos.push_back(specializationInfo);

        // Release local references
        env->DeleteLocalRef(specializationInfoObj);
        env->DeleteLocalRef(mapEntriesObj);
        env->DeleteLocalRef(pDataObj);
    }

    // Release class references
    env->DeleteLocalRef(specializationInfoListObj);
    env->DeleteLocalRef(specializationInfoClass);

    return specializationInfos;
}

VkPipelineShaderStageCreateInfoConverter::~VkPipelineShaderStageCreateInfoConverter() {
    env->DeleteLocalRef(clazz);
    clazz = nullptr;
    sTypeField = nullptr;
    flagsField = nullptr;
    stageField = nullptr;
    moduleField = nullptr;
    pNextField = nullptr;
    pSpecializationInfoField = nullptr;
}
