/* 
 * VkSwapchainCreateInfoKHRConverter.h
 * Created by Ron June Valdoz on Mon Aug 07 23:50:29 PST 2023
 */

#ifndef AWAKE_VKSWAPCHAINCREATEINFOKHRCONVERTER_H
#define AWAKE_VKSWAPCHAINCREATEINFOKHRCONVERTER_H

#include <jni.h>
#include <vulkan/vulkan.h>

class VkSwapchainCreateInfoKHRConverter {
private:
    JNIEnv *env;
    jclass clazz;

    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID surfaceField;
    jfieldID minImageCountField;
    jfieldID imageFormatField;
    jfieldID imageColorSpaceField;
    jfieldID imageExtentField;
    jfieldID imageArrayLayersField;
    jfieldID imageUsageField;
    jfieldID imageSharingModeField;
    jfieldID pQueueFamilyIndicesField;
    jfieldID preTransformField;
    jfieldID compositeAlphaField;
    jfieldID presentModeField;
    jfieldID clippedField;
    jfieldID oldSwapchainField;
public:
    explicit VkSwapchainCreateInfoKHRConverter(JNIEnv *env);

    VkSwapchainCreateInfoKHR fromObject(jobject createInfo);

    jobject toObject(VkSwapchainCreateInfoKHR &vulkan);

    ~VkSwapchainCreateInfoKHRConverter();
};

#endif /* AWAKE_VKSWAPCHAINCREATEINFOKHRCONVERTER_H */