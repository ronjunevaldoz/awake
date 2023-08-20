/*
 *  VulkanUtils.h
 *  Vulkan utils for Vulkan
 *  Created by Ron June Valdoz */

#ifndef VULKANUTILS_H
#define VULKANUTILS_H

#include <jni.h>
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <enum_utils.h>
#include <includes/VkInstanceCreateInfoAccessor.h>
#include <includes/VkDeviceCreateInfoAccessor.h>
#include <includes/VkAndroidSurfaceCreateInfoKHRAccessor.h>
#include <includes/VkSwapchainCreateInfoKHRAccessor.h>
#include <includes/VkImageViewCreateInfoAccessor.h>
#include <includes/VkShaderModuleCreateInfoAccessor.h>
#include <includes/VkPipelineCacheCreateInfoAccessor.h>
#include <includes/VkPipelineLayoutCreateInfoAccessor.h>
#include <includes/VkGraphicsPipelineCreateInfoAccessor.h>
#include <includes/VkRenderPassCreateInfoAccessor.h>
#include <includes/VkFramebufferCreateInfoAccessor.h>
#include <includes/VkCommandBufferAllocateInfoAccessor.h>
#include <includes/VkCommandBufferBeginInfoAccessor.h>
#include <includes/VkCommandPoolCreateInfoAccessor.h>
#include <includes/VkViewportAccessor.h>
#include <includes/VkRect2DAccessor.h>
#include <includes/VkLayerPropertiesMutator.h>
#include <includes/VkExtensionPropertiesMutator.h>
#include <includes/VkPhysicalDevicePropertiesMutator.h>
#include <includes/VkPhysicalDeviceFeaturesMutator.h>
#include <includes/VkQueueFamilyPropertiesMutator.h>
#include <includes/VkSurfaceCapabilitiesKHRMutator.h>
#include <includes/VkSurfaceFormatKHRMutator.h>
#include <includes/VkDebugUtilsMessengerCreateInfoEXTAccessor.h>

namespace awake {
    jobjectArray getPhysicalDeviceQueueFamilyProperties(JNIEnv *env, jlong arg0);

    void destroyFramebuffer(jlong arg0, jlong arg1);

    void destroySurfaceKHR(jlong arg0, jlong arg1);

    jlongArray createGraphicsPipelines(JNIEnv *env, jlong arg0, jlong arg1, jobjectArray arg2);

    jlong createDebugUtilsMessengerEXT(JNIEnv *env, jlong arg0, jobject arg1);

    void cmdEndRenderPass(JNIEnv *env, jlong arg0);

    jlongArray getSwapchainImagesKHR(JNIEnv *env, jlong arg0, jlong arg1);

    void destroyShaderModule(jlong arg0, jlong arg1);

    jlong createPipelineLayout(JNIEnv *env, jlong arg0, jobject arg1);

    jlong allocateCommandBuffers(JNIEnv *env, jlong arg0, jobject arg1);

    jlong getDeviceQueue(JNIEnv *env, jlong arg0, jint arg1, jint arg2);

    jlong createAndroidSurfaceKHR(JNIEnv *env, jlong arg0, jobject arg1);

    jobject getPhysicalDeviceSurfaceCapabilitiesKHR(JNIEnv *env, jlong arg0, jlong arg1);

    jlong createInstance(JNIEnv *env, jobject arg0);

    jobjectArray enumerateInstanceLayerProperties(JNIEnv *env);

    jobject getPhysicalDeviceProperties(JNIEnv *env, jlong arg0);

    void destroyPipelineCache(jlong arg0, jlong arg1);

    void cmdBindPipeline(JNIEnv *env, jlong arg0, jobject arg1, jlong arg2);

    void cmdSetScissor(JNIEnv *env, jlong arg0, jint arg1, jobjectArray arg2);

    void destroyPipelineLayout(jlong arg0, jlong arg1);

    void beginCommandBuffer(JNIEnv *env, jlong arg0, jobject arg1);

    jobjectArray enumerateDeviceExtensionProperties(JNIEnv *env, jlong arg0, jstring arg1);

    jobject getPhysicalDeviceFeatures(JNIEnv *env, jlong arg0);

    void destroyRenderPass(jlong arg0, jlong arg1);

    void destroyImageView(jlong arg0, jlong arg1);

    jlong createFramebuffer(JNIEnv *env, jlong arg0, jobject arg1);

    jlong createRenderPass(JNIEnv *env, jlong arg0, jobject arg1);

    jlongArray enumeratePhysicalDevices(JNIEnv *env, jlong arg0);

    jlong createShaderModule(JNIEnv *env, jlong arg0, jobject arg1);

    jboolean getPhysicalDeviceSurfaceSupportKHR(JNIEnv *env, jlong arg0, jint arg1, jlong arg2);

    jlong createDevice(JNIEnv *env, jlong arg0, jobject arg1);

    jlong createPipelineCache(JNIEnv *env, jlong arg0, jobject arg1);

    void destroySwapchainKHR(jlong arg0, jlong arg1);

    jobjectArray getPhysicalDeviceSurfacePresentModesKHR(JNIEnv *env, jlong arg0, jlong arg1);

    jobjectArray enumerateInstanceExtensionProperties(JNIEnv *env, jstring arg0);

    void destroyCommandPool(jlong arg0, jlong arg1);

    void cmdDraw(JNIEnv *env, jlong arg0, jint arg1, jint arg2, jint arg3, jint arg4);

    void destroyPipeline(jlong arg0, jlong arg1);

    jlong createSwapchainKHR(JNIEnv *env, jlong arg0, jobject arg1);

    void endCommandBuffer(JNIEnv *env, jlong arg0);

    void destroyDebugUtilsMessengerEXT(jlong arg0, jlong arg1);

    void destroyDevice(jlong arg0);

    void cmdSetViewport(JNIEnv *env, jlong arg0, jint arg1, jobjectArray arg2);

    void destroyInstance(jlong arg0);

    jlong createImageView(JNIEnv *env, jlong arg0, jobject arg1);

    jlong createCommandPool(JNIEnv *env, jlong arg0, jobject arg1);

    jobjectArray getPhysicalDeviceSurfaceFormatsKHR(JNIEnv *env, jlong arg0, jlong arg1);
}
#endif // VULKANUTILS_H