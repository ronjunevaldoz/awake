/* 
 * VkStencilOpStateConverter.h
 * Created by Ron June Valdoz on Wed Aug 09 09:18:59 PST 2023
 */

#ifndef AWAKE_VKSTENCILOPSTATECONVERTER_H
#define AWAKE_VKSTENCILOPSTATECONVERTER_H

#include <jni.h>
#include <vulkan/vulkan.h>

class VkStencilOpStateConverter {
private:
    JNIEnv *env;
    jclass clazz;

    jfieldID failOpField;
    jfieldID passOpField;
    jfieldID depthFailOpField;
    jfieldID compareOpField;
    jfieldID compareMaskField;
    jfieldID writeMaskField;
    jfieldID referenceField;
public:
    explicit VkStencilOpStateConverter(JNIEnv *env);

    VkStencilOpState fromObject(jobject createInfo);

    jobject toObject(VkStencilOpState &vulkan);

    ~VkStencilOpStateConverter();
};

#endif /* AWAKE_VKSTENCILOPSTATECONVERTER_H */