/*
 * Awake
 * Awake.awake-vulkan.main
 *
 * Copyright (c) ronjunevaldoz 2023.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package io.github.ronjunevaldoz.awake.vulkan

import io.github.ronjunevaldoz.awake.vulkan.enums.VkPresentModeKHR
import io.github.ronjunevaldoz.awake.vulkan.models.VkExtensionProperties
import io.github.ronjunevaldoz.awake.vulkan.models.VkImage
import io.github.ronjunevaldoz.awake.vulkan.models.VkLayerProperties
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkFramebufferCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkGraphicsPipelineCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkImageViewCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkInstanceCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkRenderPassCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkShaderModuleCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkSwapchainCreateInfoKHR
import io.github.ronjunevaldoz.awake.vulkan.models.info.debug.VkDebugUtilsMessengerCreateInfoEXT
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineCacheCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineLayoutCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.physicaldevice.VkPhysicalDeviceFeatures
import io.github.ronjunevaldoz.awake.vulkan.physicaldevice.VkPhysicalDeviceProperties
import io.github.ronjunevaldoz.awake.vulkan.presentation.VkAndroidSurfaceCreateInfoKHR
import io.github.ronjunevaldoz.awake.vulkan.presentation.swapchain.VkSurfaceCapabilitiesKHR
import io.github.ronjunevaldoz.awake.vulkan.presentation.swapchain.VkSurfaceFormatKHR
import io.github.ronjunevaldoz.awake.vulkan.queuefamily.VkQueueFamilyProperties

actual object Vulkan {
    init {
        System.loadLibrary("awake-vulkan")
    }

    actual external fun vkCreateInstance(createInfo: VkInstanceCreateInfo): Long
    actual external fun vkDestroyInstance(instance: Long)


    /**
     * Enumerates the Vulkan extension properties available for the instance.
     *
     * @return An array of VkExtensionProperties representing the available instance extensions.
     */
    actual external fun vkEnumerateInstanceLayerProperties(): Array<VkLayerProperties>
    actual external fun vkEnumerateInstanceExtensionProperties(layerName: String?): Array<VkExtensionProperties>
    actual external fun vkEnumerateDeviceExtensionProperties(
        physicalDevice: Long,
        layerName: String?
    ): Array<VkExtensionProperties>

    actual external fun vkEnumeratePhysicalDevices(instance: Long): LongArray

    actual external fun vkGetPhysicalDeviceProperties(physicalDevice: Long): VkPhysicalDeviceProperties
    actual external fun vkGetPhysicalDeviceFeatures(physicalDevice: Long): VkPhysicalDeviceFeatures
    actual external fun vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice: Long): Array<VkQueueFamilyProperties>
    actual external fun vkGetSwapchainImagesKHR(device: Long, swapchain: Long): Array<VkImage>

    actual external fun vkCreateDevice(physicalDevice: Long, deviceInfo: VkDeviceCreateInfo): Long
    actual external fun vkDestroyDevice(device: Long)

    actual external fun vkGetDeviceQueue(device: Long, queueFamilyIndex: Int, queueIndex: Int): Long

    actual external fun vkCreateAndroidSurfaceKHR(
        instance: Long,
        surfaceInfo: VkAndroidSurfaceCreateInfoKHR
    ): Long

    actual external fun vkGetPhysicalDeviceSurfaceSupportKHR(
        physicalDevice: Long,
        queueFamilyIndex: Int,
        surface: Long
    ): Boolean

    actual external fun vkDestroySurface(instance: Long, surface: Long)

    actual external fun vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
        physicalDevice: Long,
        surface: Long
    ): VkSurfaceCapabilitiesKHR

    actual external fun vkGetPhysicalDeviceSurfaceFormatsKHR(
        physicalDevice: Long,
        surface: Long
    ): Array<VkSurfaceFormatKHR>

    actual external fun vkGetPhysicalDeviceSurfacePresentModesKHR(
        physicalDevice: Long,
        surface: Long
    ): Array<VkPresentModeKHR>

    actual external fun vkCreateSwapchainKHR(
        device: Long,
        createInfoKHR: VkSwapchainCreateInfoKHR
    ): Long

    actual external fun vkDestroySwapchainKHR(
        device: Long,
        swapchainKHR: Long
    )

    actual external fun createDebugUtilsMessenger(
        instance: Long,
        createInfo: VkDebugUtilsMessengerCreateInfoEXT
    ): Long

    actual external fun destroyDebugUtilsMessenger(instance: Long, debugUtilsMessenger: Long)
    actual external fun vkCreateImageView(
        device: Long,
        createInfo: VkImageViewCreateInfo
    ): Long

    actual external fun vkDestroyImageView(device: Long, imageView: Long)
    actual external fun vkCreateShaderModule(
        device: Long,
        createInfo: VkShaderModuleCreateInfo
    ): Long

    actual external fun vkDestroyShaderModule(device: Long, shaderModule: Long)
    actual external fun vkCreatePipelineCache(
        device: Long,
        createInfo: VkPipelineCacheCreateInfo
    ): Long

    actual external fun vkDestroyPipelineCache(
        device: Long,
        pipelineCache: Long
    )

    actual external fun vkCreateGraphicsPipeline(
        device: Long,
        pipelineCache: Long,
        createInfos: Array<VkGraphicsPipelineCreateInfo>
    ): LongArray

    actual external fun vkDestroyPipeline(device: Long, pipeline: Long)
    actual external fun vkCreatePipelineLayout(
        device: Long,
        createInfo: VkPipelineLayoutCreateInfo
    ): Long

    actual external fun vkDestroyPipelineLayout(device: Long, pipelineLayout: Long)
    actual external fun vkCreateRenderPass(
        device: Long,
        createInfo: VkRenderPassCreateInfo
    ): Long

    actual external fun vkDestroyRenderPass(device: Long, renderPass: Long)
    actual external fun vkCreateFramebuffer(
        device: Long,
        framebufferInfo: VkFramebufferCreateInfo
    ): Long

    actual external fun vkDestroyFramebuffer(device: Long, framebuffer: Long)
}