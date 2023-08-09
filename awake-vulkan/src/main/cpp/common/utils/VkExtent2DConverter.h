/* 
 * VkExtent2DConverter.h
 * Created by Ron June Valdoz on Mon Aug 07 23:50:29 PST 2023
 */

#ifndef AWAKE_VKEXTENT2DCONVERTER_H
#define AWAKE_VKEXTENT2DCONVERTER_H

#include <jni.h>
#include <vulkan/vulkan.h>

class VkExtent2DConverter {
private:
    JNIEnv *env;
    jclass clazz;

    jfieldID widthField;
    jfieldID heightField;
public:
    explicit VkExtent2DConverter(JNIEnv *env);

    VkExtent2D fromObject(jobject createInfo);

    jobject toObject(VkExtent2D &vulkan);

    ~VkExtent2DConverter();
};

#endif /* AWAKE_VKEXTENT2DCONVERTER_H */