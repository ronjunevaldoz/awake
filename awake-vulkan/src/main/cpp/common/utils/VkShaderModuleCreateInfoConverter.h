/* 
 * VkShaderModuleCreateInfoConverter.h
 * Created by Ron June Valdoz on Mon Aug 07 11:15:30 PST 2023
 */

#ifndef AWAKE_VKSHADERMODULECREATEINFOCONVERTER_H
#define AWAKE_VKSHADERMODULECREATEINFOCONVERTER_H

#include <jni.h>
#include <vulkan/vulkan.h>

class VkShaderModuleCreateInfoConverter {
private:
    JNIEnv *env;
    jclass clazz;

    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID pCodeField;
public:
    explicit VkShaderModuleCreateInfoConverter(JNIEnv *env);

    VkShaderModuleCreateInfo fromObject(jobject createInfo);

    jobject toObject(VkShaderModuleCreateInfo &vulkan);

    ~VkShaderModuleCreateInfoConverter();
};

#endif /* AWAKE_VKSHADERMODULECREATEINFOCONVERTER_H */