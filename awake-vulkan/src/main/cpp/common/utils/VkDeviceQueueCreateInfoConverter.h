//
// Created by Ron June Valdoz on 8/2/23.
//

#ifndef AWAKE_VKDEVICEQUEUECREATEINFOCONVERTER_H
#define AWAKE_VKDEVICEQUEUECREATEINFOCONVERTER_H

#include <vulkan/vulkan.h>
#include <jni.h>

class VkDeviceQueueCreateInfoConverter {
private:
    jclass clazz;
    jfieldID sTypeFieldID;
    jfieldID pNextFieldID;
    jfieldID flagsFieldID;
    jfieldID queueFamilyIndexFieldID;
    jfieldID queueCountFieldID;
    jfieldID pQueuePrioritiesFieldID;
    JNIEnv *env;
public:
    explicit VkDeviceQueueCreateInfoConverter(JNIEnv *env);

    VkDeviceQueueCreateInfo fromObject(jobject vkQueueCreateInfoObject);

    ~VkDeviceQueueCreateInfoConverter();
};


#endif //AWAKE_VKDEVICEQUEUECREATEINFOCONVERTER_H
