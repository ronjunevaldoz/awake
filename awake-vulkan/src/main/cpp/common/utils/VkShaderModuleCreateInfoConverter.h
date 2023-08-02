//
// Created by Ron June Valdoz on 8/2/23.
//

#ifndef AWAKE_VKSHADERMODULECREATEINFOCONVERTER_H
#define AWAKE_VKSHADERMODULECREATEINFOCONVERTER_H


#include <jni.h>
#include <vulkan/vulkan.h>

class VkShaderModuleCreateInfoConverter {
private:
    jclass clazz;
    jmethodID constructor;
    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID codeSizeField;
    jfieldID pCodeField;
    JNIEnv *env;
public:
    explicit VkShaderModuleCreateInfoConverter(JNIEnv *env);

    VkShaderModuleCreateInfo fromObject(jobject createInfo);

    ~VkShaderModuleCreateInfoConverter();
};


#endif //AWAKE_VKSHADERMODULECREATEINFOCONVERTER_H
