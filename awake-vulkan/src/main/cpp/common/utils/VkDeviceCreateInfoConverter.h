/* 
 * VkDeviceCreateInfoConverter.h
 * Created by Ron June Valdoz on Mon Aug 07 23:50:29 PST 2023
 */

#ifndef AWAKE_VKDEVICECREATEINFOCONVERTER_H
#define AWAKE_VKDEVICECREATEINFOCONVERTER_H

#include <jni.h>
#include <vulkan/vulkan.h>

class VkDeviceCreateInfoConverter {
private:
    JNIEnv *env;
    jclass clazz;

    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID pQueueCreateInfosField;
    jfieldID ppEnabledLayerNamesField;
    jfieldID ppEnabledExtensionNamesField;
    jfieldID pEnabledFeaturesField;
public:
    explicit VkDeviceCreateInfoConverter(JNIEnv *env);

    VkDeviceCreateInfo fromObject(jobject createInfo);

    jobject toObject(VkDeviceCreateInfo &vulkan);

    ~VkDeviceCreateInfoConverter();
};

#endif /* AWAKE_VKDEVICECREATEINFOCONVERTER_H */