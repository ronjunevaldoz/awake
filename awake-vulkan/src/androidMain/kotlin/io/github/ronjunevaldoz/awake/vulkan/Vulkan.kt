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
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkApplicationInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkImageViewCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkShaderModuleCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkSwapchainCreateInfoKHR
import io.github.ronjunevaldoz.awake.vulkan.physicaldevice.VkPhysicalDeviceFeatures
import io.github.ronjunevaldoz.awake.vulkan.physicaldevice.VkPhysicalDeviceProperties
import io.github.ronjunevaldoz.awake.vulkan.presentation.VkAndroidSurfaceCreateInfoKHR
import io.github.ronjunevaldoz.awake.vulkan.presentation.swapchain.VkSurfaceCapabilitiesKHR
import io.github.ronjunevaldoz.awake.vulkan.presentation.swapchain.VkSurfaceFormatKHR
import io.github.ronjunevaldoz.awake.vulkan.queuefamily.VkQueueFamilyProperties
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.IntBuffer
import java.nio.LongBuffer

actual object Vulkan {
    init {
        System.loadLibrary("awake-vulkan")
    }

    actual external fun vkCreateInstance(appInfo: VkApplicationInfo): Long
    actual external fun vkDestroyInstance(instance: Long)

    actual external fun vkEnumerateInstanceExtensionProperties(): Array<VkExtensionProperties>
    actual external fun vkEnumerateDeviceExtensionProperties(physicalDevice: Long): Array<VkExtensionProperties>

    external fun vkEnumeratePhysicalDevices(
        instance: Long,
        pPhysicalDeviceCount: IntBuffer,
        pPhysicalDevices: LongBuffer? = null
    ): Boolean

    actual fun vkEnumeratePhysicalDevices(instance: Long): List<Long> {
        val countBuffer =
            ByteBuffer.allocateDirect(1 * Int.SIZE_BYTES).order(ByteOrder.nativeOrder())
                .asIntBuffer()
        val physicalDevicesBuffer =
            ByteBuffer.allocateDirect(1 * Long.SIZE_BYTES).order(ByteOrder.nativeOrder())
                .asLongBuffer()
        vkEnumeratePhysicalDevices(instance, countBuffer)
        return if (countBuffer[0] > 0) {
            vkEnumeratePhysicalDevices(instance, countBuffer, physicalDevicesBuffer)
            val data = LongArray(countBuffer[0])
            physicalDevicesBuffer.get(data)
            data.toList()
        } else {
            emptyList()
        }
    }

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

    actual external fun createDebugUtilsMessenger(instance: Long): Long
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
}