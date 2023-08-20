/*
 * Awake
 * Awake.awake-vulkan.desktopMain
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

import io.github.ronjunevaldoz.awake.vulkan.enums.VkPipelineBindPoint
import io.github.ronjunevaldoz.awake.vulkan.enums.VkPresentModeKHR
import io.github.ronjunevaldoz.awake.vulkan.models.VkExtensionProperties
import io.github.ronjunevaldoz.awake.vulkan.models.VkLayerProperties
import io.github.ronjunevaldoz.awake.vulkan.models.VkQueueFamilyProperties
import io.github.ronjunevaldoz.awake.vulkan.models.VkRect2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkSurfaceCapabilitiesKHR
import io.github.ronjunevaldoz.awake.vulkan.models.VkSurfaceFormatKHR
import io.github.ronjunevaldoz.awake.vulkan.models.VkViewport
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkAndroidSurfaceCreateInfoKHR
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkCommandBufferAllocateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkCommandBufferBeginInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkCommandPoolCreateInfo
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
import io.github.ronjunevaldoz.awake.vulkan.models.physicaldevice.VkPhysicalDeviceFeatures
import io.github.ronjunevaldoz.awake.vulkan.models.physicaldevice.VkPhysicalDeviceProperties

actual object Vulkan {
    /**
     * Creates a new Vulkan instance with the provided application information.
     *
     * @param createInfo The VkInstanceCreateInfo containing the application-specific information.
     * @return The handle to the created Vulkan instance.
     */
    @VkReturnType("VkInstance")
    actual fun vkCreateInstance(createInfo: VkInstanceCreateInfo): Long {
        TODO("Not yet implemented")
    }

    /**
     * Destroys the specified Vulkan instance.
     *
     * @param instance The handle to the Vulkan instance to be destroyed.
     */
    actual fun vkDestroyInstance(@VkHandleRef("VkInstance") instance: Long) {
    }

    /**
     * Enumerates the Vulkan extension properties available for the instance.
     *
     * @return An array of VkExtensionProperties representing the available instance extensions.
     */
    actual fun vkEnumerateInstanceLayerProperties(): Array<VkLayerProperties> {
        TODO("Not yet implemented")
    }

    /**
     * Enumerates the Vulkan extension properties available for the instance.
     *
     * @return An array of VkExtensionProperties representing the available instance extensions.
     */
    actual fun vkEnumerateInstanceExtensionProperties(layerName: String?): Array<VkExtensionProperties> {
        TODO("Not yet implemented")
    }

    /**
     * Enumerates the Vulkan extension properties available for a specific physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @return An array of VkExtensionProperties representing the available device extensions.
     */
    actual fun vkEnumerateDeviceExtensionProperties(
        @VkHandleRef("VkPhysicalDevice") physicalDevice: Long,
        layerName: String?
    ): Array<VkExtensionProperties> {
        TODO("Not yet implemented")
    }

    /**
     * Enumerates the available Vulkan physical devices for the specified instance.
     *
     * @param instance The handle to the Vulkan instance.
     * @return An array of VkPhysicalDevice handle in a form of type Long
     */
    @VkReturnType("VkPhysicalDevice")
    actual fun vkEnumeratePhysicalDevices(@VkHandleRef("VkInstance") instance: Long): LongArray {
        TODO("Not yet implemented")
    }

    /**
     * Retrieves properties of the specified physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @return The VkPhysicalDeviceProperties representing the properties of the physical device.
     */
    actual fun vkGetPhysicalDeviceProperties(@VkHandleRef("VkPhysicalDevice") physicalDevice: Long): VkPhysicalDeviceProperties {
        TODO("Not yet implemented")
    }

    /**
     * Retrieves features of the specified physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @return The VkPhysicalDeviceFeatures representing the features of the physical device.
     */
    actual fun vkGetPhysicalDeviceFeatures(@VkHandleRef("VkPhysicalDevice") physicalDevice: Long): VkPhysicalDeviceFeatures {
        TODO("Not yet implemented")
    }

    /**
     * Retrieves properties of the queue families available on the specified physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @return An array of VkQueueFamilyProperties representing the properties of queue families.
     */
    actual fun vkGetPhysicalDeviceQueueFamilyProperties(@VkHandleRef("VkPhysicalDevice") physicalDevice: Long): Array<VkQueueFamilyProperties> {
        TODO("Not yet implemented")
    }

    /**
     * Retrieves the images associated with the specified Vulkan swapchain.
     *
     * @param device The handle to the Vulkan logical device.
     * @param swapchain The handle to the Vulkan swapchain.
     * @return An array of VkImage representing the images in the swapchain.
     */
    @VkReturnType("VkImage")
    actual fun vkGetSwapchainImagesKHR(
        @VkHandleRef("VkDevice") device: Long,
        @VkHandleRef("VkSwapchainKHR") swapchain: Long
    ): LongArray {
        TODO("Not yet implemented")
    }

    /**
     * Creates a new VkDevice object associated with the given physical device and using the provided device configuration.
     *
     * @param physicalDevice The handle to the physical device for which the logical device will be created.
     * @param deviceInfo The configuration settings for the logical device, encapsulated in VkDeviceCreateInfo.
     * @return A handle to the newly created VkDevice object.
     */
    @VkReturnType("VkDevice")
    actual fun vkCreateDevice(
        @VkHandleRef("VkPhysicalDevice") physicalDevice: Long,
        deviceInfo: VkDeviceCreateInfo
    ): Long {
        TODO("Not yet implemented")
    }

    /**
     * Destroys the specified VkDevice object and releases its associated resources.
     *
     * @param device The handle to the logical device that will be destroyed.
     */
    actual fun vkDestroyDevice(@VkHandleRef("VkDevice") device: Long) {
    }

    /**
     * Returns the VkQueue associated with the given device, queue family index, and queue index.
     *
     * @param device The handle to the logical device.
     * @param queueFamilyIndex The index of the queue family.
     * @param queueIndex The index of the queue within the queue family.
     * @return The VkQueue associated with the specified parameters.
     */
    @VkReturnType("VkQueue")
    actual fun vkGetDeviceQueue(
        @VkHandleRef("VkDevice") device: Long,
        queueFamilyIndex: Int,
        queueIndex: Int
    ): Long {
        TODO("Not yet implemented")
    }

    /**
     * Creates an Android surface for Vulkan presentation.
     *
     * @param instance The handle to the Vulkan instance.
     * @param surfaceInfo Information required to create the Android surface.
     * @return The handle to the created Android surface.
     */
    @VkReturnType("VkSurfaceKHR")
    actual fun vkCreateAndroidSurfaceKHR(
        @VkHandleRef("VkInstance") instance: Long,
        surfaceInfo: VkAndroidSurfaceCreateInfoKHR
    ): Long {
        TODO("Not yet implemented")
    }

    /**
     * Checks if presentation is supported on the specified physical device and queue family.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @param queueFamilyIndex The index of the queue family to check for presentation support.
     * @param surface The handle to the surface to be presented.
     * @return `true` if presentation is supported, `false` otherwise.
     */
    actual fun vkGetPhysicalDeviceSurfaceSupportKHR(
        @VkHandleRef("VkPhysicalDevice") physicalDevice: Long,
        queueFamilyIndex: Int,
        @VkHandleRef("VkSurfaceKHR") surface: Long
    ): Boolean {
        TODO("Not yet implemented")
    }

    /**
     * Destroys the Vulkan surface.
     *
     * @param instance The handle to the Vulkan instance.
     * @param surface The handle to the surface to be destroyed.
     */
    actual fun vkDestroySurfaceKHR(
        @VkHandleRef("VkInstance") instance: Long,
        @VkHandleRef("VkSurfaceKHR") surface: Long
    ) {
    }

    /**
     * Retrieves the capabilities of the surface on the specified physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @param surface The handle to the surface to retrieve capabilities from.
     * @return The capabilities of the specified surface.
     */
    actual fun vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
        @VkHandleRef("VkPhysicalDevice") physicalDevice: Long,
        @VkHandleRef("VkSurfaceKHR") surface: Long
    ): VkSurfaceCapabilitiesKHR {
        TODO("Not yet implemented")
    }

    /**
     * Retrieves the available surface formats on the specified physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @param surface The handle to the surface to query for formats.
     * @return An array of surface formats supported by the specified surface.
     */
    actual fun vkGetPhysicalDeviceSurfaceFormatsKHR(
        @VkHandleRef("VkPhysicalDevice") physicalDevice: Long,
        @VkHandleRef("VkSurfaceKHR") surface: Long
    ): Array<VkSurfaceFormatKHR> {
        TODO("Not yet implemented")
    }

    /**
     * Retrieves the supported presentation modes for the specified surface on the physical device.
     *
     * @param physicalDevice The handle to the Vulkan physical device.
     * @param surface The handle to the surface to query for presentation modes.
     * @return An array of supported presentation modes for the specified surface.
     */
    actual fun vkGetPhysicalDeviceSurfacePresentModesKHR(
        @VkHandleRef("VkPhysicalDevice") physicalDevice: Long,
        @VkHandleRef("VkSurfaceKHR") surface: Long
    ): Array<VkPresentModeKHR> {
        TODO("Not yet implemented")
    }

    /**
     * Creates a Vulkan swapchain for the specified device.
     *
     * @param device The handle to the Vulkan logical device.
     * @param createInfoKHR The structure containing swapchain creation information.
     * @return The handle to the created Vulkan swapchain.
     */
    @VkReturnType("VkSwapchainKHR")
    actual fun vkCreateSwapchainKHR(
        @VkHandleRef("VkDevice") device: Long,
        createInfoKHR: VkSwapchainCreateInfoKHR
    ): Long {
        TODO("Not yet implemented")
    }

    /**
     * Destroys the Vulkan swapchain.
     *
     * @param device The handle to the Vulkan logical device.
     * @param swapchainKHR The handle to the swapchain to be destroyed.
     */
    actual fun vkDestroySwapchainKHR(
        @VkHandleRef("VkDevice") device: Long,
        @VkHandleRef("VkSwapchainKHR") swapchainKHR: Long
    ) {
    }

    @VkReturnType("VkImageView")
    actual fun vkCreateImageView(
        @VkHandleRef("VkDevice") device: Long,
        createInfo: VkImageViewCreateInfo
    ): Long {
        TODO("Not yet implemented")
    }

    actual fun vkDestroyImageView(
        @VkHandleRef("VkDevice") device: Long,
        @VkHandleRef("VkImageView") imageView: Long
    ) {
    }

    @VkReturnType("VkShaderModule")
    actual fun vkCreateShaderModule(
        @VkHandleRef("VkDevice") device: Long,
        createInfo: VkShaderModuleCreateInfo
    ): Long {
        TODO("Not yet implemented")
    }

    actual fun vkDestroyShaderModule(
        @VkHandleRef("VkDevice") device: Long,
        @VkHandleRef("VkShaderModule") shaderModule: Long
    ) {
    }

    @VkReturnType("VkPipelineCache")
    actual fun vkCreatePipelineCache(
        @VkHandleRef("VkDevice") device: Long,
        createInfo: VkPipelineCacheCreateInfo
    ): Long {
        TODO("Not yet implemented")
    }

    actual fun vkDestroyPipelineCache(
        @VkHandleRef("VkDevice") device: Long,
        @VkHandleRef("VkPipelineCache") pipelineCache: Long
    ) {
    }

    @VkReturnType("VkPipelineLayout")
    actual fun vkCreatePipelineLayout(
        @VkHandleRef("VkDevice") device: Long,
        createInfo: VkPipelineLayoutCreateInfo
    ): Long {
        TODO("Not yet implemented")
    }

    actual fun vkDestroyPipelineLayout(
        @VkHandleRef("VkDevice") device: Long,
        @VkHandleRef("VkPipelineLayout") pipelineLayout: Long
    ) {
    }

    @VkReturnType("VkPipeline")
    actual fun vkCreateGraphicsPipelines(
        @VkHandleRef("VkDevice") device: Long,
        @VkHandleRef("VkPipelineCache") pipelineCache: Long,
        createInfos: Array<VkGraphicsPipelineCreateInfo>
    ): LongArray {
        TODO("Not yet implemented")
    }

    actual fun vkDestroyPipeline(
        @VkHandleRef("VkDevice") device: Long,
        @VkHandleRef("VkPipeline") pipeline: Long
    ) {
    }

    @VkReturnType("VkRenderPass")
    actual fun vkCreateRenderPass(
        @VkHandleRef("VkDevice") device: Long,
        createInfo: VkRenderPassCreateInfo
    ): Long {
        TODO("Not yet implemented")
    }

    actual fun vkDestroyRenderPass(
        @VkHandleRef("VkDevice") device: Long,
        @VkHandleRef("VkRenderPass") renderPass: Long
    ) {
    }

    @VkReturnType("VkFramebuffer")
    actual fun vkCreateFramebuffer(
        @VkHandleRef("VkDevice") device: Long,
        framebufferInfo: VkFramebufferCreateInfo
    ): Long {
        TODO("Not yet implemented")
    }

    actual fun vkDestroyFramebuffer(
        @VkHandleRef("VkDevice") device: Long,
        @VkHandleRef("VkFramebuffer") framebuffer: Long
    ) {
    }

    @VkReturnType("VkCommandBuffer")
    actual fun vkAllocateCommandBuffers(
        @VkHandleRef("VkDevice") device: Long,
        createInfo: VkCommandBufferAllocateInfo
    ): Long {
        TODO("Not yet implemented")
    }

    actual fun vkBeginCommandBuffer(
        @VkHandleRef("VkCommandBuffer") commandBuffer: Long,
        beginInfo: VkCommandBufferBeginInfo
    ) {
    }

    @VkReturnType("VkCommandPool")
    actual fun vkCreateCommandPool(
        @VkHandleRef("VkDevice") device: Long,
        createInfo: VkCommandPoolCreateInfo
    ): Long {
        TODO("Not yet implemented")
    }

    actual fun vkDestroyCommandPool(
        @VkHandleRef("VkDevice") device: Long,
        @VkHandleRef("VkCommandPool") commandPool: Long
    ) {
    }

    actual fun vkCmdBindPipeline(
        @VkHandleRef("VkCommandBuffer") commandBuffer: Long,
        pipelineBindPoint: VkPipelineBindPoint,
        @VkHandleRef("VkPipeline") graphicsPipeline: Long
    ) {
    }

    actual fun vkCmdSetViewport(
        @VkHandleRef("VkCommandBuffer") commandBuffer: Long,
        firstViewport: Int,
        viewports: Array<VkViewport>
    ) {
    }

    actual fun vkCmdSetScissor(
        @VkHandleRef("VkCommandBuffer") commandBuffer: Long,
        firstScissor: Int,
        scissors: Array<VkRect2D>
    ) {
    }

    actual fun vkCmdDraw(
        @VkHandleRef("VkCommandBuffer") commandBuffer: Long,
        vertexCount: Int,
        instanceCount: Int,
        firstVertex: Int,
        firstInstance: Int
    ) {
    }

    actual fun vkCmdEndRenderPass(@VkHandleRef("VkCommandBuffer") commandBuffer: Long) {
    }

    actual fun vkEndCommandBuffer(@VkHandleRef("VkCommandBuffer") commandBuffer: Long) {
    }

    @VkReturnType("VkDebugUtilsMessengerEXT")
    @VkSingleton
    actual fun vkCreateDebugUtilsMessengerEXT(
        @VkHandleRef("VkInstance") instance: Long,
        createInfo: VkDebugUtilsMessengerCreateInfoEXT
    ): Long {
        TODO("Not yet implemented")
    }

    @VkSingleton
    actual fun vkDestroyDebugUtilsMessengerEXT(
        @VkHandleRef("VkInstance") instance: Long,
        @VkHandleRef("VkDebugUtilsMessengerEXT") debugUtilsMessenger: Long
    ) {
    }
}