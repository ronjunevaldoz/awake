#include "jni.h"
#include "common/utils/vulkan_utils.h"


extern "C" {
JNIEXPORT jlong JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkCreateInstance(JNIEnv *env, jobject thiz,
                                                                  jobject app_info) {
    return vulkan_utils::createInstance(env, app_info);
}

JNIEXPORT jlong JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_createDebugUtilsMessenger(JNIEnv *env,
                                                                           jobject thiz,
                                                                           jlong instance) {
    auto instanceHandle = reinterpret_cast<VkInstance>(instance);
    VkDebugUtilsMessengerEXT debugUtilsMessenger = vulkan_utils::createDebugUtilsMessenger(
            instanceHandle);
    return reinterpret_cast<jlong>(debugUtilsMessenger);
}
JNIEXPORT void JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_destroyDebugUtilsMessenger(JNIEnv *env,
                                                                            jobject thiz,
                                                                            jlong instance,
                                                                            jlong debug_utils_messenger) {
    auto instanceHandle = reinterpret_cast<VkInstance>(instance);
    auto messengerHandle = reinterpret_cast<VkDebugUtilsMessengerEXT>(debug_utils_messenger);
    vulkan_utils::destroyDebugUtilsMessenger(instanceHandle, messengerHandle);
}
JNIEXPORT void JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkDestroyInstance(JNIEnv *env, jobject thiz,
                                                                   jlong instance) {
    auto instanceHandle = reinterpret_cast<VkInstance>(instance);
    vkDestroyInstance(instanceHandle, nullptr);
}

JNIEXPORT void JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkDestroyDevice(JNIEnv *env, jobject thiz,
                                                                 jlong device) {
    auto deviceHandle = reinterpret_cast<VkDevice>(device);
    vkDestroyDevice(deviceHandle, nullptr);
}
JNIEXPORT jlong JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkGetDeviceQueue(JNIEnv *env, jobject thiz,
                                                                  jlong device,
                                                                  jint queue_family_index,
                                                                  jint queue_index) {
    return vulkan_utils::getDeviceQueue(env, device, queue_family_index, queue_index);
}
// Vulkan wrapper

JNIEXPORT jboolean JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkEnumeratePhysicalDevices(JNIEnv *env,
                                                                            jobject thiz,
                                                                            jlong vkInstance,
                                                                            jobject
                                                                            p_physical_device_count,
                                                                            jobject p_physical_devices) {
    return vulkan_utils::enumeratePhysicalDevices(env, vkInstance, p_physical_device_count,
                                                  p_physical_devices);
}

JNIEXPORT jobject JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkGetPhysicalDeviceProperties(JNIEnv *env,
                                                                               jobject thiz,
                                                                               jlong physical_device) {


    return vulkan_utils::physicalDevicePropertiesObj_fromVkPhysicalDeviceProperties(env,
                                                                                    physical_device);
}

JNIEXPORT jobject JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkGetPhysicalDeviceFeatures(JNIEnv *env,
                                                                             jobject thiz,
                                                                             jlong physical_device) {

    return vulkan_utils::physicalDeviceFeaturesObj_fromVkPhysicalDeviceFeatures(env,
                                                                                physical_device);
}

JNIEXPORT jobjectArray JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkGetPhysicalDeviceQueueFamilyProperties(
        JNIEnv *env, jobject thiz, jlong physical_device) {
    return vulkan_utils::queueFamilyPropertiesObj_fromVkQueueFamilyProperties(env, physical_device);
}
JNIEXPORT jlong JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkCreateDevice(JNIEnv *env, jobject thiz,
                                                                jlong physical_device,
                                                                jobject device_info) {
    return vulkan_utils::createDevice(env, physical_device, device_info);
}

JNIEXPORT jlong JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkCreateAndroidSurfaceKHR(JNIEnv *env,
                                                                           jobject thiz,
                                                                           jlong pInstance,
                                                                           jobject surface_info) {
    return vulkan_utils::createAndroidSurfaceKHR(env, pInstance, surface_info);
}

JNIEXPORT jboolean JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkGetPhysicalDeviceSurfaceSupportKHR(JNIEnv *env,
                                                                                      jobject thiz,
                                                                                      jlong pDevice,
                                                                                      jint queueFamilyIndex,
                                                                                      jlong pSurface) {
    return vulkan_utils::getPhysicalDeviceSurfaceSupportKHR(env, pDevice, queueFamilyIndex,
                                                            pSurface);
}
JNIEXPORT void JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkDestroySurface(JNIEnv *env, jobject thiz,
                                                                  jlong pInstance, jlong pSurface) {
    vulkan_utils::destroySurface(env, pInstance, pSurface);
}

JNIEXPORT jobject JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
        JNIEnv *env, jobject thiz, jlong pPhysicalDevice, jlong pSurface) {
    return vulkan_utils::getPhysicalDeviceSurfaceCapabilitiesKHR(env, pPhysicalDevice, pSurface);
}
JNIEXPORT jobjectArray JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkGetPhysicalDeviceSurfaceFormatsKHR(JNIEnv *env,
                                                                                      jobject thiz,
                                                                                      jlong pPhysicalDevice,
                                                                                      jlong pSurface) {
    return vulkan_utils::getPhysicalDeviceSurfaceFormatsKHR(env, pPhysicalDevice, pSurface);
}
JNIEXPORT jobjectArray JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkGetPhysicalDeviceSurfacePresentModesKHR(
        JNIEnv *env, jobject thiz, jlong pPhysicalDevice, jlong pSurface) {
    return vulkan_utils::getPhysicalDeviceSurfacePresentModesKHR(env, pPhysicalDevice, pSurface);
}

JNIEXPORT jlong JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkCreateSwapchainKHR(JNIEnv *env, jobject thiz,
                                                                      jlong pDevice,
                                                                      jobject create_info_khr) {
    return vulkan_utils::createSwapchainKHR(env, pDevice, create_info_khr);
}
JNIEXPORT void JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkDestroySwapchainKHR(JNIEnv *env, jobject thiz,
                                                                       jlong pDevice,
                                                                       jlong swapchain_khr) {
    vulkan_utils::destroySwapchainKHR(env, pDevice, swapchain_khr);
}

JNIEXPORT jobjectArray JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkEnumerateInstanceExtensionProperties(JNIEnv *env,
                                                                                        jobject thiz) {
    return vulkan_utils::enumerateInstanceExtensionProperties(env);
}

JNIEXPORT jobjectArray JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkEnumerateDeviceExtensionProperties(JNIEnv *env,
                                                                                      jobject thiz,
                                                                                      jlong physical_device) {
    return vulkan_utils::enumerateDeviceExtensionProperties(env, physical_device);
}
JNIEXPORT jobjectArray JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkGetSwapchainImagesKHR(JNIEnv *env,
                                                                         jobject thiz,
                                                                         jlong device,
                                                                         jlong swapchain) {
    return vulkan_utils::getSwapchainImagesKHR(env, device, swapchain);
}

JNIEXPORT jlong JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkCreateImageView(
        JNIEnv *env, jobject thiz, jlong pDevice, jobject pCreateInfo) {
    return vulkan_utils::createImageView(env, pDevice, pCreateInfo);
}

JNIEXPORT void JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkDestroyImageView(JNIEnv *env, jobject thiz,
                                                                    jlong pDevice,
                                                                    jlong pImageView) {
    vulkan_utils::destroyImageView(env, pDevice, pImageView);
}

JNIEXPORT jlong JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkCreateShaderModule(JNIEnv *env, jobject thiz,
                                                                      jlong device,
                                                                      jobject create_info) {
    return vulkan_utils::createShaderModule(env, device, create_info);
}
JNIEXPORT void JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkDestroyShaderModule(JNIEnv *env, jobject thiz,
                                                                       jlong device,
                                                                       jlong shader_module) {
    return vulkan_utils::destroyShaderModule(device, shader_module);
}
}
extern "C"
JNIEXPORT jlong JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkCreatePipelineCache(JNIEnv *env, jobject thiz,
                                                                       jlong device,
                                                                       jobject create_info) {
    return vulkan_utils::createPipelineCache(env, device, create_info);
}
extern "C"
JNIEXPORT void JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkDestroyPipelineCache(JNIEnv *env, jobject thiz,
                                                                        jlong device,
                                                                        jlong pipeline_cache) {
    vulkan_utils::destroyPipelineCache(device, pipeline_cache);
}
extern "C"
JNIEXPORT jlongArray JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkCreateGraphicsPipeline(JNIEnv *env, jobject thiz,
                                                                          jlong device,
                                                                          jlong pipeline_cache,
                                                                          jobjectArray create_infos) {
    return vulkan_utils::createGraphicsPipeline(env, device, pipeline_cache, create_infos);
}
extern "C"
JNIEXPORT void JNICALL
Java_io_github_ronjunevaldoz_awake_vulkan_Vulkan_vkDestroyPipeline(JNIEnv *env, jobject thiz,
                                                                   jlong device, jlong pipeline) {
    vulkan_utils::destroyPipeline(device, pipeline);
}