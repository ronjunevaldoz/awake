/*
 * Awake
 * Awake.awake-core.main
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

package io.github.ronjunevaldoz.awake.core.graphics

import android.content.Context
import android.util.Log
import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView
import io.github.ronjunevaldoz.awake.vulkan.Vulkan
import io.github.ronjunevaldoz.awake.vulkan.enums.VkColorSpaceKHR
import io.github.ronjunevaldoz.awake.vulkan.enums.VkCompositeAlphaFlagBitsKHR
import io.github.ronjunevaldoz.awake.vulkan.enums.VkFormat
import io.github.ronjunevaldoz.awake.vulkan.enums.VkImageAspectFlagBits
import io.github.ronjunevaldoz.awake.vulkan.enums.VkImageUsageFlagBits
import io.github.ronjunevaldoz.awake.vulkan.enums.VkImageViewType
import io.github.ronjunevaldoz.awake.vulkan.enums.VkPhysicalDeviceType
import io.github.ronjunevaldoz.awake.vulkan.enums.VkPresentModeKHR
import io.github.ronjunevaldoz.awake.vulkan.enums.VkSharingMode
import io.github.ronjunevaldoz.awake.vulkan.enums.VkSurfaceTransformFlagBitsKHR
import io.github.ronjunevaldoz.awake.vulkan.has
import io.github.ronjunevaldoz.awake.vulkan.models.VkExtent2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkSurfaceKHR
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkApplicationInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceQueueCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkImageSubresourceRange
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkImageViewCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkShaderModuleCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkSwapchainCreateInfoKHR
import io.github.ronjunevaldoz.awake.vulkan.physicaldevice.VkPhysicalDevice
import io.github.ronjunevaldoz.awake.vulkan.physicaldevice.eq
import io.github.ronjunevaldoz.awake.vulkan.presentation.VkAndroidSurfaceCreateInfoKHR
import io.github.ronjunevaldoz.awake.vulkan.presentation.swapchain.VkSurfaceCapabilitiesKHR
import io.github.ronjunevaldoz.awake.vulkan.presentation.swapchain.VkSurfaceFormatKHR
import io.github.ronjunevaldoz.awake.vulkan.utils.findQueueFamilies
import io.github.ronjunevaldoz.awake.vulkan.utils.isSwapChainSupported
import io.github.ronjunevaldoz.awake.vulkan.utils.querySwapChainSupport
import kotlinx.coroutines.runBlocking
import org.jetbrains.compose.resources.ExperimentalResourceApi
import org.jetbrains.compose.resources.resource


class VulkanView(context: Context) : SurfaceView(context), SurfaceHolder.Callback2 {

    var instance: Long = 0
    var surface: Long = 0
    var physicalDevice: Long = 0
    var device: Long = 0
    var swapChain: Long = 0
    var imageViews: List<Long> = emptyList()
    var debugUtilsMessenger: Long = 0

    init {
        Vulkan
        holder.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        if (instance == 0L) {
            setup(holder.surface)
        } else {
            Vulkan.destroyDebugUtilsMessenger(instance, debugUtilsMessenger)
            Vulkan.vkDestroyDevice(device)
            Vulkan.vkDestroySurface(instance, surface)
            Vulkan.vkDestroyInstance(instance)
            Vulkan.vkDestroySwapchainKHR(physicalDevice, swapChain)
            imageViews.forEach { imageView ->
                Vulkan.vkDestroyImageView(device, imageView)
            }
            setup(holder.surface)
        }
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
//        TODO("Not yet implemented")
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
//        TODO("Not yet implemented")
    }

    override fun surfaceRedrawNeeded(holder: SurfaceHolder) {
//        TODO("Not yet implemented")
    }

    private fun setup(s: Surface) {
        val appInfo = VkApplicationInfo(
            pApplicationName = "Awake Vulkan - Application",
            pEngineName = "Awaken Vukan - Engine"
        )
        try {
//            check(isExtSupported(
//                VulkanExtension.VK_KHR_SURFACE,
//                VulkanExtension.VK_KHR_ANDROID_SURFACE,
//                VulkanExtension.VK_KHR_SWAPCHAIN,
//            )){"One of ext is not supported"}

            instance = Vulkan.vkCreateInstance(appInfo)
            debugUtilsMessenger = Vulkan.createDebugUtilsMessenger(instance)
            val surface = createSurface(instance, s)
            // Physical Devices
            val physicalDevices =
                Vulkan.vkEnumeratePhysicalDevices(instance).map { VkPhysicalDevice(it, instance) }
            if (physicalDevices.isNotEmpty()) {
                // find a gpu
                val gpu = physicalDevices.find { vkDevice ->
                    val properties = Vulkan.vkGetPhysicalDeviceProperties(vkDevice.physicalDevice)
                    val features = Vulkan.vkGetPhysicalDeviceFeatures(vkDevice.physicalDevice)
                    val hasGeometry = features.geometryShader
                    val isIntegratedGPU =
                        properties.deviceType eq VkPhysicalDeviceType.VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU
                    val isDiscreteGPU =
                        properties.deviceType eq VkPhysicalDeviceType.VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
                    val isVirtualGPU =
                        properties.deviceType eq VkPhysicalDeviceType.VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU
                    isIntegratedGPU || isDiscreteGPU || isVirtualGPU
                } ?: throw Exception("Cannot find suitable gpu!")
                physicalDevice = gpu.physicalDevice
                // Queue families
                val queueFamilyProperties =
                    Vulkan.vkGetPhysicalDeviceQueueFamilyProperties(gpu.physicalDevice)
                val indices = findQueueFamilies(gpu, surface)

                if (!isSwapChainSupported(gpu, surface)) {
                    Log.w("Vulkan", "SwapChain not supported")
                }

                if (!indices.isComplete()) {
                    // graphics not supported?
                    throw Exception("GPU graphics / Presentation not supported")
                }

                // Logical Device
                // to avoid duplicate queue family index use set
                val uniqueQueueFamilies = setOf(
                    indices.graphicsFamily!!,
                    indices.presentFamily!!
                )
                val queueInfos = uniqueQueueFamilies.map { uniqueQueueFamilyIndex ->
                    VkDeviceQueueCreateInfo(
                        queueFamilyIndex = uniqueQueueFamilyIndex,
                        queueCount = queueFamilyProperties[uniqueQueueFamilyIndex].queueCount.toInt(),
                        pQueuePriorities = floatArrayOf(1.0f)
                    )
                }

                val features = Vulkan.vkGetPhysicalDeviceFeatures(gpu.physicalDevice)
                val deviceInfo = VkDeviceCreateInfo().apply {
                    pQueueCreateInfos = queueInfos
//                    queueCreateInfoCount = queueInfos.size
                    pEnabledFeatures = listOf(features)
//                    enabledExtensionCount = 0u
                    // enable all device extensions
                    val deviceExtensions =
                        Vulkan.vkEnumerateDeviceExtensionProperties(gpu.physicalDevice)
                            .map { it.extensionName }.toList()
                    ppEnabledExtensionNames = deviceExtensions
                    val enableValidationLayers = false
                    if (enableValidationLayers) {
//                        enabledLayerCount = validationLayers.size
//                        ppEnabledLayerNames = validationLayers
                    } else {
                        enabledLayerCount = 0u
                    }
                }

                device = Vulkan.vkCreateDevice(gpu.physicalDevice, deviceInfo) // VkDevice
                // create swap chain
                swapChain(device, gpu, surface)
                createGraphicsPipeline()
//                val graphicsQueue = Vulkan.vkGetDeviceQueue(device, indices.graphicsFamily!!, 0)
//                graphicsQueue
            }
        } catch (e: Exception) {
            Log.e("Vulkan", e.message.toString())
        }
    }

    private fun swapChain(device: Long, gpu: VkPhysicalDevice, surface: VkSurfaceKHR) {
        val (capabilities, formats, presentModes) = querySwapChainSupport(gpu, surface)
        val (format, colorSpace) = chooseSwapSurfaceFormat(formats)
        val presentMode = chooseSwapPresentMode(presentModes)
        val extent = chooseSwapExtent(capabilities, context)

        val imageCount = (capabilities.minImageCount + 1).coerceIn(1, capabilities.maxImageCount)

        val indices = findQueueFamilies(gpu, surface)
        var queueFamilyIndices: List<Int>? =
            listOf(indices.graphicsFamily!!, indices.presentFamily!!)
        val imageSharingMode: VkSharingMode
        if (indices.graphicsFamily !== indices.presentFamily) {
            imageSharingMode = VkSharingMode.VK_SHARING_MODE_CONCURRENT
        } else {
            imageSharingMode = VkSharingMode.VK_SHARING_MODE_EXCLUSIVE
            queueFamilyIndices = null
        }
        val compositeAlpha =
            if (capabilities.supportedCompositeAlpha has VkCompositeAlphaFlagBitsKHR.VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR) {
                VkCompositeAlphaFlagBitsKHR.VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR
            } else if (capabilities.supportedCompositeAlpha has VkCompositeAlphaFlagBitsKHR.VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR) {
                VkCompositeAlphaFlagBitsKHR.VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR
            } else {
                throw Exception("No valid compositeAlpha found")
            }


        val imageUsage =
            if (capabilities.supportedUsageFlags has VkImageUsageFlagBits.VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) {
                VkImageUsageFlagBits.VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT.value
            } else {
                throw Exception("No valid usage flags found")
            }

        val preTransform =
            if (capabilities.supportedTransforms has VkSurfaceTransformFlagBitsKHR.VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR) {
                VkSurfaceTransformFlagBitsKHR.VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR
            } else {
                capabilities.currentTransform
            }

        val createInfo = VkSwapchainCreateInfoKHR(
            surface = surface,
            minImageCount = imageCount,
            imageFormat = format,
            imageColorSpace = colorSpace,
            imageExtent = extent,
            imageArrayLayers = 1,
            imageUsage = imageUsage,
            imageSharingMode = imageSharingMode,
            queueFamilyIndices = queueFamilyIndices,
            preTransform = preTransform,
            compositeAlpha = compositeAlpha,
            presentMode = presentMode,
            clipped = true,
            oldSwapchain = null
        )

        swapChain = Vulkan.vkCreateSwapchainKHR(device, createInfo)

        createImageViews(format, extent)
    }

    private fun createImageViews(swapChainImageFormat: VkFormat, swapChainExtent: VkExtent2D) {
        val swapChainImages = Vulkan.vkGetSwapchainImagesKHR(device, swapChain)
        val swapChainImageViews = swapChainImages.map { swapChainImage ->
            val createInfo = VkImageViewCreateInfo(
                image = swapChainImage.image,
                viewType = VkImageViewType.VK_IMAGE_VIEW_TYPE_2D,
                format = swapChainImageFormat,
                subresourceRange = VkImageSubresourceRange(
                    aspectMask = VkImageAspectFlagBits.VK_IMAGE_ASPECT_COLOR_BIT.value,
                    baseMipLevel = 0,
                    levelCount = 1,
                    baseArrayLayer = 0,
                    layerCount = 1
                )
            )
            Vulkan.vkCreateImageView(device, createInfo)
        }
        imageViews = swapChainImageViews
    }

    @OptIn(ExperimentalResourceApi::class)
    fun createShaderModule(path: String) = runBlocking {
        val code = resource(path).readBytes()
        val createInfo = VkShaderModuleCreateInfo(
            codeSize = 0,
            pCode = code
        )
        Vulkan.vkCreateShaderModule(device, createInfo)
    }

    private fun createGraphicsPipeline() {
        val fragShaderModule = createShaderModule("assets/shader/vulkan/shader.frag.spv")
        val vertShaderModule = createShaderModule("assets/shader/vulkan/shader.vert.spv")

        // process shader

        Vulkan.vkDestroyShaderModule(device, fragShaderModule)
        Vulkan.vkDestroyShaderModule(device, vertShaderModule)
    }

    private fun chooseSwapSurfaceFormat(availableFormats: List<VkSurfaceFormatKHR>): VkSurfaceFormatKHR {
        require(availableFormats.isNotEmpty()) { "AvailableFormats must not be empty." }
        return availableFormats.find { surfaceFormat ->
            surfaceFormat.format == VkFormat.VK_FORMAT_R8G8B8A8_SRGB && // RGBA
//            surfaceFormat.format == VkFormat.VK_FORMAT_B8G8R8A8_SRGB && // BGRA I think this format is for c++??
                    surfaceFormat.colorSpace == VkColorSpaceKHR.VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
        } ?: availableFormats.first()
    }

    private fun chooseSwapPresentMode(availablePresetModes: List<VkPresentModeKHR>): VkPresentModeKHR {
        require(availablePresetModes.isNotEmpty()) { "AvailablePresetModes must not be empty." }
        return availablePresetModes.find { presentMode ->
            presentMode == VkPresentModeKHR.VK_PRESENT_MODE_MAILBOX_KHR
        } ?: return VkPresentModeKHR.VK_PRESENT_MODE_FIFO_KHR;
    }

    private fun chooseSwapExtent(
        capabilities: VkSurfaceCapabilitiesKHR,
        context: Context
    ): VkExtent2D {
        if (capabilities.currentExtent.width != Int.MAX_VALUE) {
            return capabilities.currentExtent
        }
        val displayMetrics = context.resources.displayMetrics
        val width = displayMetrics.widthPixels
        val height = displayMetrics.heightPixels
        val actualWidth =
            width.coerceIn(capabilities.minImageExtent.width, capabilities.maxImageExtent.width)
        val actualHeight =
            height.coerceIn(capabilities.minImageExtent.height, capabilities.maxImageExtent.height)
        return VkExtent2D(actualWidth, actualHeight)
    }

    private fun createSurface(instance: Long, window: Surface): VkSurfaceKHR {
        // Presentation
        val surfaceInfo = VkAndroidSurfaceCreateInfoKHR(
            window = window
        )
        surface = Vulkan.vkCreateAndroidSurfaceKHR(instance, surfaceInfo)
        return VkSurfaceKHR(
            instance = instance,
            surface = surface
        )
    }
}