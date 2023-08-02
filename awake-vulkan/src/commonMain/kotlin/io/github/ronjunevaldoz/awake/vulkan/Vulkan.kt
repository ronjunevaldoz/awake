/*
 * Awake
 * Awake.awake-vulkan.commonMain
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

expect object Vulkan {
    // Instance management
    /**
     * Creates a new Vulkan instance with the provided application information.
     *
     * @param appInfo The VkApplicationInfo containing the application-specific information.
     * @return The handle to the created Vulkan instance.
     */
    fun vkCreateInstance(appInfo: VkApplicationInfo): Long

    /**
     * Destroys the specified Vulkan instance.
     *
     * @param instance The handle to the Vulkan instance to be destroyed.
     */
    fun vkDestroyInstance(instance: Long)

    // Device management
    /**
     * Enumerates the Vulkan extension properties available for the instance.
     *
     * @return An array of VkExtensionProperties representing the available instance extensions.
     */
    fun vkEnumerateInstanceExtensionProperties(): Array<VkExtensionProperties>

    /**
     * Enumerates the Vulkan extension properties available for a specific physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @return An array of VkExtensionProperties representing the available device extensions.
     */
    fun vkEnumerateDeviceExtensionProperties(physicalDevice: Long): Array<VkExtensionProperties>

    /**
     * Enumerates the available Vulkan physical devices for the specified instance.
     *
     * @param instance The handle to the Vulkan instance.
     * @return An array of VkPhysicalDevice handle in a form of type Long
     */
    fun vkEnumeratePhysicalDevices(instance: Long): List<Long>

    /**
     * Retrieves properties of the specified physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @return The VkPhysicalDeviceProperties representing the properties of the physical device.
     */
    fun vkGetPhysicalDeviceProperties(physicalDevice: Long): VkPhysicalDeviceProperties

    /**
     * Retrieves features of the specified physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @return The VkPhysicalDeviceFeatures representing the features of the physical device.
     */
    fun vkGetPhysicalDeviceFeatures(physicalDevice: Long): VkPhysicalDeviceFeatures

    /**
     * Retrieves properties of the queue families available on the specified physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @return An array of VkQueueFamilyProperties representing the properties of queue families.
     */
    fun vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice: Long): Array<VkQueueFamilyProperties>

    /**
     * Retrieves the images associated with the specified Vulkan swapchain.
     *
     * @param device The handle to the Vulkan logical device.
     * @param swapchain The handle to the Vulkan swapchain.
     * @return An array of VkImage representing the images in the swapchain.
     */
    fun vkGetSwapchainImagesKHR(device: Long, swapchain: Long): Array<VkImage>

    /**
     * Creates a new VkDevice object associated with the given physical device and using the provided device configuration.
     *
     * @param physicalDevice The handle to the physical device for which the logical device will be created.
     * @param deviceInfo The configuration settings for the logical device, encapsulated in VkDeviceCreateInfo.
     * @return A handle to the newly created VkDevice object.
     */
    fun vkCreateDevice(physicalDevice: Long, deviceInfo: VkDeviceCreateInfo): Long

    /**
     * Destroys the specified VkDevice object and releases its associated resources.
     *
     * @param device The handle to the logical device that will be destroyed.
     */
    fun vkDestroyDevice(device: Long)

    /**
     * Returns the VkQueue associated with the given device, queue family index, and queue index.
     *
     * @param device The handle to the logical device.
     * @param queueFamilyIndex The index of the queue family.
     * @param queueIndex The index of the queue within the queue family.
     * @return The VkQueue associated with the specified parameters.
     */
    fun vkGetDeviceQueue(device: Long, queueFamilyIndex: Int, queueIndex: Int): Long

    // Presentation - Window surface
    /**
     * Creates an Android surface for Vulkan presentation.
     *
     * @param instance The handle to the Vulkan instance.
     * @param surfaceInfo Information required to create the Android surface.
     * @return The handle to the created Android surface.
     */
    fun vkCreateAndroidSurfaceKHR(
        instance: Long,
        surfaceInfo: VkAndroidSurfaceCreateInfoKHR
    ): Long

    /**
     * Checks if presentation is supported on the specified physical device and queue family.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @param queueFamilyIndex The index of the queue family to check for presentation support.
     * @param surface The handle to the surface to be presented.
     * @return `true` if presentation is supported, `false` otherwise.
     */
    fun vkGetPhysicalDeviceSurfaceSupportKHR(
        physicalDevice: Long,
        queueFamilyIndex: Int,
        surface: Long
    ): Boolean

    /**
     * Destroys the Vulkan surface.
     *
     * @param instance The handle to the Vulkan instance.
     * @param surface The handle to the surface to be destroyed.
     */
    fun vkDestroySurface(instance: Long, surface: Long)

    // Presentation - Swap chain
    /**
     * Retrieves the capabilities of the surface on the specified physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @param surface The handle to the surface to retrieve capabilities from.
     * @return The capabilities of the specified surface.
     */
    fun vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
        physicalDevice: Long,
        surface: Long
    ): VkSurfaceCapabilitiesKHR

    /**
     * Retrieves the available surface formats on the specified physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @param surface The handle to the surface to query for formats.
     * @return An array of surface formats supported by the specified surface.
     */
    fun vkGetPhysicalDeviceSurfaceFormatsKHR(
        physicalDevice: Long,
        surface: Long
    ): Array<VkSurfaceFormatKHR>

    /**
     * Retrieves the supported presentation modes for the specified surface on the physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @param surface The handle to the surface to query for presentation modes.
     * @return An array of supported presentation modes for the specified surface.
     */
    fun vkGetPhysicalDeviceSurfacePresentModesKHR(
        physicalDevice: Long,
        surface: Long
    ): Array<VkPresentModeKHR>

    /**
     * Creates a Vulkan swapchain for the specified device.
     *
     * @param device The handle to the Vulkan logical device.
     * @param createInfoKHR The structure containing swapchain creation information.
     * @return The handle to the created Vulkan swapchain.
     */
    fun vkCreateSwapchainKHR(
        device: Long,
        createInfoKHR: VkSwapchainCreateInfoKHR
    ): Long

    /**
     * Destroys the Vulkan swapchain.
     *
     * @param device The handle to the Vulkan logical device.
     * @param swapchainKHR The handle to the swapchain to be destroyed.
     */
    fun vkDestroySwapchainKHR(
        device: Long,
        swapchainKHR: Long
    )

    fun vkCreateImageView(device: Long, createInfo: VkImageViewCreateInfo): Long
    fun vkDestroyImageView(device: Long, imageView: Long)

    fun vkCreateShaderModule(device: Long, createInfo: VkShaderModuleCreateInfo): Long
    fun vkDestroyShaderModule(device: Long, shaderModule: Long)

    // Debug messenger
    fun createDebugUtilsMessenger(instance: Long): Long
    fun destroyDebugUtilsMessenger(instance: Long, debugUtilsMessenger: Long)
}