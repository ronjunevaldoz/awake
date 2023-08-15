//
// Created by Ron June Valdoz on 8/1/23.
//

#ifndef AWAKE_VKIMAGEVIEWCREATEINFOCONVERTER_H
#define AWAKE_VKIMAGEVIEWCREATEINFOCONVERTER_H

#include <vulkan/vulkan.h>
#include <jni.h>

class VkImageViewCreateInfoConverter {
private:
    jclass createInfoClazz;
    jfieldID sTypeField;
    jfieldID pNextField;
    jfieldID flagsField;
    jfieldID imageField;
    jfieldID viewTypeField;
    jfieldID formatField;
    jfieldID componentsField;
    jfieldID subresourceRangeField;
    jclass componentsClass;
    jclass subresourceRangeClass;
    jmethodID getRMethod;
    jmethodID getGMethod;
    jmethodID getBMethod;
    jmethodID getAMethod;
    jmethodID getAspectMask;
    jmethodID getBaseMipLevel;
    jmethodID getLevelCount;
    jmethodID getBaseArrayLayer;
    jmethodID getLayerCount;

    JNIEnv *env;
    const char *componentSwizzleSig = "()Lio/github/ronjunevaldoz/awake/vulkan/enums/VkComponentSwizzle;";
    const char *subresourceRangeSig = "io/github/ronjunevaldoz/awake/vulkan/models/info/VkImageSubresourceRange";
public:
    explicit VkImageViewCreateInfoConverter(JNIEnv *env);

    VkImageViewCreateInfo fromObject(jobject createInfo);

    // Destructor
    ~VkImageViewCreateInfoConverter();
};

#endif //AWAKE_VKIMAGEVIEWCREATEINFOCONVERTER_H
