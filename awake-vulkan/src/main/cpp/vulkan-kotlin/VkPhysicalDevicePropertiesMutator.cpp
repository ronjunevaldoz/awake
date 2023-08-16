/*
 *  VkPhysicalDevicePropertiesMutator.cpp
 *  Vulkan mutator for VkPhysicalDeviceProperties
 *  Created by Ron June Valdoz */

#include  <includes/VkPhysicalDevicePropertiesMutator.h>

VkPhysicalDevicePropertiesMutator::VkPhysicalDevicePropertiesMutator(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/physicaldevice/VkPhysicalDeviceProperties");
    apiVersionField = env->GetFieldID(clazz, "apiVersion", "I");
    driverVersionField = env->GetFieldID(clazz, "driverVersion", "I");
    vendorIDField = env->GetFieldID(clazz, "vendorID", "I");
    deviceIDField = env->GetFieldID(clazz, "deviceID", "I");
    deviceTypeField = env->GetFieldID(clazz, "deviceType",
                                      "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkPhysicalDeviceType;");
    deviceNameField = env->GetFieldID(clazz, "deviceName", "[C");
    pipelineCacheUUIDField = env->GetFieldID(clazz, "pipelineCacheUUID", "[B");
    limitsField = env->GetFieldID(clazz, "limits",
                                  "Lio/github/ronjunevaldoz/awake/vulkan/physicaldevice/VkPhysicalDeviceLimits;");
    sparsePropertiesField = env->GetFieldID(clazz, "sparseProperties",
                                            "Lio/github/ronjunevaldoz/awake/vulkan/physicaldevice/VkPhysicalDeviceSparseProperties;");
}

jobject
VkPhysicalDevicePropertiesMutator::toObject(VkPhysicalDeviceProperties source) {
    auto constructor = env->GetMethodID(clazz, "<init>", "()V");
    auto newObj = env->NewObject(clazz, constructor);
    env->SetIntField(newObj, apiVersionField, static_cast<jint>(source.apiVersion));
    env->SetIntField(newObj, driverVersionField, static_cast<jint>(source.driverVersion));
    env->SetIntField(newObj, vendorIDField, static_cast<jint>(source.vendorID));
    env->SetIntField(newObj, deviceIDField, static_cast<jint>(source.deviceID));
    env->SetObjectField(newObj, deviceTypeField,
                        enum_utils::setEnumFromVulkan(env, static_cast<jint>(source.deviceType),
                                                      "io/github/ronjunevaldoz/awake/vulkan/enums/VkPhysicalDeviceType"));
    jcharArray deviceName = env->NewCharArray(VK_MAX_PHYSICAL_DEVICE_NAME_SIZE);
    env->SetCharArrayRegion(deviceName, 0, VK_MAX_PHYSICAL_DEVICE_NAME_SIZE,
                            reinterpret_cast<jchar *>(source.deviceName ));
    env->SetObjectField(newObj, deviceNameField, deviceName);
    env->DeleteLocalRef(deviceName);
    jbyteArray pipelineCacheUUID = env->NewByteArray(VK_UUID_SIZE);
    env->SetByteArrayRegion(pipelineCacheUUID, 0, VK_UUID_SIZE,
                            reinterpret_cast<jbyte *>(source.pipelineCacheUUID ));
    env->SetObjectField(newObj, pipelineCacheUUIDField, pipelineCacheUUID);
    env->DeleteLocalRef(pipelineCacheUUID);
    VkPhysicalDeviceLimitsMutator limitsMutator(env);
    env->SetObjectField(newObj, limitsField, limitsMutator.toObject(source.limits));
    VkPhysicalDeviceSparsePropertiesMutator sparsePropertiesMutator(env);
    env->SetObjectField(newObj, sparsePropertiesField,
                        sparsePropertiesMutator.toObject(source.sparseProperties));
    return newObj;
}

VkPhysicalDevicePropertiesMutator::~VkPhysicalDevicePropertiesMutator() {
    // env->DeleteGlobalRef(clazz);
}
