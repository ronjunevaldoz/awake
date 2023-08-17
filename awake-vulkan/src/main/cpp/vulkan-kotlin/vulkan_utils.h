//
// Created by Ron June Valdoz on 7/23/23.
//

#ifndef AWAKE_VULKAN_UTILS_H
#define AWAKE_VULKAN_UTILS_H

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <jni.h>

namespace vulkan_utils {
    jobject
    physicalDevicePropertiesObj_fromVkPhysicalDeviceProperties(JNIEnv *env, jlong pPhysicalDevice);

    jobject
    physicalDeviceFeaturesObj_fromVkPhysicalDeviceFeatures(JNIEnv *env, jlong pPhysicalDevice);

    jobjectArray queueFamilyPropertiesObj_fromVkQueueFamilyProperties(JNIEnv *pEnv, jlong device);


    bool enumeratePhysicalDevices(JNIEnv *env,
                                  jlong vkInstance,
                                  jobject pDeviceCountDirectBufferObj,
                                  jobject pPhysicalDevicesDirectBufferObj);

    // Function to create a Vulkan instance
    jlong createInstance(JNIEnv *env, jobject app_info);

    // Checking available extensions
    bool checkDebugUtilsExtAvailable();

    // Checking available extensions from layers
    bool checkDebugUtilsExtFromAvailableLayers();

    // Check if validation layer is supported
    bool checkValidationLayerSupported(const std::vector<const char *> &layers);

    // Create debug utils messenger
    VkDebugUtilsMessengerEXT
    createDebugUtilsMessenger(JNIEnv *env, VkInstance instance, jobject pCreateInfo);

    // Destroy debug utils messenger
    void
    destroyDebugUtilsMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugUtilsMessenger);

    jlong createDevice(JNIEnv *pEnv, jlong device, jobject pDeviceInfo);

    jlong createAndroidSurfaceKHR(JNIEnv *env,
                                  jlong pInstance,
                                  jobject surface_info);

    void destroySurface(JNIEnv *env,
                        jlong pInstance, jlong pSurface);

    jboolean getPhysicalDeviceSurfaceSupportKHR(JNIEnv *env,
                                                jlong pDevice,
                                                jint queueFamilyIndex,
                                                jlong pSurface);

    jobject getPhysicalDeviceSurfaceCapabilitiesKHR(
            JNIEnv *env, jlong pPhysicalDevice, jlong pSurface);

    jobjectArray getPhysicalDeviceSurfaceFormatsKHR(JNIEnv *env,
                                                    jlong pPhysicalDevice,
                                                    jlong pSurface);

    jobjectArray getPhysicalDeviceSurfacePresentModesKHR(
            JNIEnv *env, jlong pPhysicalDevice, jlong pSurface);

    jlong createSwapchainKHR(JNIEnv *env,
                             jlong pDevice,
                             jobject create_info_khr);

    void destroySwapchainKHR(JNIEnv *env,
                             jlong pDevice,
                             jlong swapchain_khr);

    jlong getDeviceQueue(JNIEnv *env,
                         jlong device,
                         jint queue_family_index,
                         jint queue_index);

    jlong createImageView(JNIEnv *env,
                          jlong device,
                          jobject create_nfo
    );

    void destroyImageView(JNIEnv *env,
                          jlong device,
                          jlong image_view
    );

    jlong createShaderModule(JNIEnv *env, jlong device, jobject createInfo);

    void destroyShaderModule(jlong device, jlong shaderModule);

    jlong createPipelineCache(JNIEnv *env, jlong pDevice, jobject createInfo);

    void destroyPipelineCache(jlong device, jlong pipelineCache);

    jlongArray createGraphicsPipeline(JNIEnv *env, jlong pDevice, jlong pPipelineCache,
                                      jobjectArray createInfosObj
    );

    void destroyPipeline(jlong device, jlong graphicsPipeline);

    _jobjectArray *enumerateInstanceExtensionProperties(JNIEnv *env);

    _jobjectArray *enumerateDeviceExtensionProperties(JNIEnv *env, jlong pPhysicalDevice);

    _jobjectArray *getSwapchainImagesKHR(JNIEnv *env, jlong pDevice, jlong pSwapchain);

    jlong createPipelineLayout(JNIEnv *env, jlong device, jobject pCreateInfo);

    void destroyPipelineLayout(jlong device, jlong piplineLayout);

    jlong createRenderPass(JNIEnv *env, jlong device, jobject pCreateInfo);

    void destroyRenderPass(jlong device, jlong renderPass);
}

#endif //AWAKE_VULKAN_UTILS_H
