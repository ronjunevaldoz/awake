//
// Created by Ron June Valdoz on 8/2/23.
//

#ifndef AWAKE_VKPIPELINESHADERSTAGECREATEINFOCONVERTER_H
#define AWAKE_VKPIPELINESHADERSTAGECREATEINFOCONVERTER_H


#include <jni.h>
#include <vulkan/vulkan.h>

class VkPipelineShaderStageCreateInfoConverter {
private:
    jclass clazz;
    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID stageField;
    jfieldID moduleField;
    jfieldID pNameField;
    jfieldID pSpecializationInfoField;
    JNIEnv *env;
public:
    explicit VkPipelineShaderStageCreateInfoConverter(JNIEnv *env);

    VkPipelineShaderStageCreateInfo fromObject(jobject createInfo);

    std::vector<VkSpecializationInfo>
    fromSpecializationInfoList(jobjectArray specializationInfoListObj);

    ~VkPipelineShaderStageCreateInfoConverter();
};


#endif //AWAKE_VKPIPELINESHADERSTAGECREATEINFOCONVERTER_H
