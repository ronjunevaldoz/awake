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
import io.github.ronjunevaldoz.awake.vulkan.VK_SUBPASS_EXTERNAL
import io.github.ronjunevaldoz.awake.vulkan.Version
import io.github.ronjunevaldoz.awake.vulkan.Version.Companion.vkVersion
import io.github.ronjunevaldoz.awake.vulkan.Vulkan
import io.github.ronjunevaldoz.awake.vulkan.enums.VkColorSpaceKHR
import io.github.ronjunevaldoz.awake.vulkan.enums.VkCommandBufferLevel
import io.github.ronjunevaldoz.awake.vulkan.enums.VkCompositeAlphaFlagBitsKHR
import io.github.ronjunevaldoz.awake.vulkan.enums.VkDynamicState
import io.github.ronjunevaldoz.awake.vulkan.enums.VkFormat
import io.github.ronjunevaldoz.awake.vulkan.enums.VkImageAspectFlagBits
import io.github.ronjunevaldoz.awake.vulkan.enums.VkImageLayout
import io.github.ronjunevaldoz.awake.vulkan.enums.VkImageUsageFlagBits
import io.github.ronjunevaldoz.awake.vulkan.enums.VkImageViewType
import io.github.ronjunevaldoz.awake.vulkan.enums.VkPhysicalDeviceType
import io.github.ronjunevaldoz.awake.vulkan.enums.VkPipelineBindPoint
import io.github.ronjunevaldoz.awake.vulkan.enums.VkPresentModeKHR
import io.github.ronjunevaldoz.awake.vulkan.enums.VkPrimitiveTopology
import io.github.ronjunevaldoz.awake.vulkan.enums.VkResult
import io.github.ronjunevaldoz.awake.vulkan.enums.VkShaderStageFlagBits
import io.github.ronjunevaldoz.awake.vulkan.enums.VkSharingMode
import io.github.ronjunevaldoz.awake.vulkan.enums.VkSubpassContents
import io.github.ronjunevaldoz.awake.vulkan.enums.VkSurfaceTransformFlagBitsKHR
import io.github.ronjunevaldoz.awake.vulkan.enums.flags.VkAccessFlagBits
import io.github.ronjunevaldoz.awake.vulkan.enums.flags.VkCommandPoolCreateFlagBits
import io.github.ronjunevaldoz.awake.vulkan.enums.flags.VkFenceCreateFlagBits
import io.github.ronjunevaldoz.awake.vulkan.enums.flags.VkPipelineStageFlagBits
import io.github.ronjunevaldoz.awake.vulkan.has
import io.github.ronjunevaldoz.awake.vulkan.models.VkAttachmentDescription
import io.github.ronjunevaldoz.awake.vulkan.models.VkAttachmentReference
import io.github.ronjunevaldoz.awake.vulkan.models.VkClearColorValue
import io.github.ronjunevaldoz.awake.vulkan.models.VkExtent2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkOffset2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkRect2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkSubpassDependency
import io.github.ronjunevaldoz.awake.vulkan.models.VkSurfaceCapabilitiesKHR
import io.github.ronjunevaldoz.awake.vulkan.models.VkSurfaceFormatKHR
import io.github.ronjunevaldoz.awake.vulkan.models.VkSurfaceKHR
import io.github.ronjunevaldoz.awake.vulkan.models.VkViewport
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkAndroidSurfaceCreateInfoKHR
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkApplicationInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkCommandBufferAllocateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkCommandBufferBeginInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkCommandPoolCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceQueueCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkFenceCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkFramebufferCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkGraphicsPipelineCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkImageSubresourceRange
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkImageViewCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkInstanceCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkPresentInfoKHR
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkRenderPassBeginInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkRenderPassCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkSemaphoreCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkShaderModuleCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkSubmitInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkSubpassDescription
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkSwapchainCreateInfoKHR
import io.github.ronjunevaldoz.awake.vulkan.models.info.debug.DebugUtilsFormattedCallback
import io.github.ronjunevaldoz.awake.vulkan.models.info.debug.VkDebugUtilsMessengerCreateInfoEXT
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineCacheCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineColorBlendAttachmentState
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineColorBlendStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineDynamicStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineInputAssemblyStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineLayoutCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineShaderStageCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineViewportStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.physicaldevice.VkPhysicalDevice
import io.github.ronjunevaldoz.awake.vulkan.utils.VkResultException
import io.github.ronjunevaldoz.awake.vulkan.utils.findQueueFamilies
import io.github.ronjunevaldoz.awake.vulkan.utils.getAppExtProps
import io.github.ronjunevaldoz.awake.vulkan.utils.getAppLayerProps
import io.github.ronjunevaldoz.awake.vulkan.utils.isSwapChainSupported
import io.github.ronjunevaldoz.awake.vulkan.utils.querySwapChainSupport
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import org.jetbrains.compose.resources.ExperimentalResourceApi
import org.jetbrains.compose.resources.resource
import java.nio.ByteBuffer
import java.nio.ByteOrder


class VulkanView(context: Context) : SurfaceView(context), SurfaceHolder.Callback2 {

    var debugUtilsMessenger: Long = 0
    var instance: Long = 0
    var surface: Long = 0
    var physicalDevice: Long = 0
    var device: Long = 0
    var graphicsQueue: Long = 0
    var presentQueue: Long = 0
    var swapChain: Long = 0
    var swapChainExtent: VkExtent2D = VkExtent2D()
    var swapChainImageViews: List<Long> = emptyList()
    var swapChainImageFormat = VkFormat.VK_FORMAT_UNDEFINED
    var renderPass: Long = 0
    var pipelineCache: Long = 0
    var pipelineLayout: Long = 0
    var graphicsPipeline: LongArray = longArrayOf()
    var swapChainFrameBuffers: List<Long> = emptyList()
    var commandPool: Long = 0
    var commandBuffer: Long = 0

    var imageAvailableSemaphore: Long = 0//  VkSemaphore? = null
    var renderFinishedSemaphore: Long = 0//VkSemaphore? = null
    var inFlightFence: Long = 0 ////VkFence? = null


    private val mainScope = CoroutineScope(Dispatchers.Main)

    init {
        Vulkan
        holder.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        if (instance == 0L) {
            setupVulkan(holder.surface)
        } else {
            destroy()
            setupVulkan(holder.surface)
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

    private fun setupVulkan(window: Surface) {
        createInstance()
        setupDebugMessenger()
        createSurface(window)
        // Physical Devices
        pickPhysicalDevice()
        // Logical Device
        createLogicalDevice()
        // create swap chain
        swapChain()
        createRenderPass()
        createGraphicsPipeline()
        createFramebuffers()
        createCommandPool()
        createCommandBuffer()
        createSyncObjects()

        mainScope.launch {
            try {
                while (true) {
                    drawFrame()
                    delay(16)
                }
            } catch (e: Exception) {
                Log.e("draw error", e.message.toString())
            }
        }
    }

    private fun drawFrame() {
        Vulkan.vkWaitForFences(device, longArrayOf(inFlightFence), true, Long.MAX_VALUE)
        Vulkan.vkResetFences(device, longArrayOf(inFlightFence))

        val imageIndex = Vulkan.vkAcquireNextImageKHR(
            device,
            swapChain,
            Int.MAX_VALUE.toLong(),
            imageAvailableSemaphore,
            0
        )

        Vulkan.vkResetCommandBuffer(commandBuffer, 0)
        recordCommandBuffer(commandBuffer, imageIndex)

        val waitSemaphores = arrayOf(imageAvailableSemaphore)
        val waitStages =
            intArrayOf(VkPipelineStageFlagBits.VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT.value)
        val signalSemaphores = arrayOf(renderFinishedSemaphore)

        val submitInfo = VkSubmitInfo(
            pWaitSemaphores = waitSemaphores,
            pWaitDstStageMask = waitStages,
            pCommandBuffers = arrayOf(commandBuffer),
            pSignalSemaphores = signalSemaphores
        )

        Vulkan.vkQueueSubmit(graphicsQueue, arrayOf(submitInfo), inFlightFence)

        val presentInfo = VkPresentInfoKHR(
            pWaitSemaphores = signalSemaphores,
            pSwapchains = arrayOf(swapChain),
            pImageIndices = intArrayOf(imageIndex),
            pResults = null
        )

        try {
            Vulkan.vkQueuePresentKHR(presentQueue, presentInfo)
        } catch (e: VkResultException) {
            when (e.result) {
                VkResult.VK_SUBOPTIMAL_KHR, VkResult.VK_ERROR_OUT_OF_DATE_KHR -> recreateSwapChain()
                else -> throw e
            }
        }
    }

    private fun recreateSwapChain() {
        // TODO process recreation of swapchain here
//        Vulkan.vkDeviceWaitIdle(device)
    }

    private fun createSyncObjects() {
        val semaphoreInfo = VkSemaphoreCreateInfo()
        val fenceInfo = VkFenceCreateInfo(
            flags = VkFenceCreateFlagBits.VK_FENCE_CREATE_SIGNALED_BIT.value
        )

        imageAvailableSemaphore = Vulkan.vkCreateSemaphore(device, semaphoreInfo)
        renderFinishedSemaphore = Vulkan.vkCreateSemaphore(device, semaphoreInfo)
        inFlightFence = Vulkan.vkCreateFence(device, fenceInfo)
    }

    private fun recordCommandBuffer(commandBuffer: Long, aquiredImageIndex: Int) {
        val beginInfo = VkCommandBufferBeginInfo(
            flags = 0 // VkCommandBufferUsageFlagBits.VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT.value
        )
        Vulkan.vkBeginCommandBuffer(commandBuffer, beginInfo)

        // start render pass
        val renderPassInfo = VkRenderPassBeginInfo(
            renderPass = renderPass,
            framebuffer = swapChainFrameBuffers[aquiredImageIndex],
            renderArea = VkRect2D(
                extent = swapChainExtent
            ),
            pClearValues = arrayOf(VkClearColorValue.rgba(0f, 1f, 0f, 1f))
        )
        Vulkan.vkCmdBeginRenderPass(
            commandBuffer,
            renderPassInfo,
            VkSubpassContents.VK_SUBPASS_CONTENTS_INLINE
        )

        // basic drawing
        Vulkan.vkCmdBindPipeline(
            commandBuffer,
            VkPipelineBindPoint.VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline[0]
        )
        val viewport = VkViewport(
            width = swapChainExtent.width.toFloat(),
            height = swapChainExtent.height.toFloat(),
        )
        Vulkan.vkCmdSetViewport(commandBuffer, 0, arrayOf(viewport))
        val scissor = VkRect2D(
            extent = swapChainExtent
        )
        Vulkan.vkCmdSetScissor(commandBuffer, 0, arrayOf(scissor))
        Vulkan.vkCmdDraw(commandBuffer, 3, 1, 0, 0)
        Vulkan.vkCmdEndRenderPass(commandBuffer)
        Vulkan.vkEndCommandBuffer(commandBuffer)
    }

    private fun createCommandBuffer() {
        val allocInfo = VkCommandBufferAllocateInfo(
            commandPool = commandPool,
            level = VkCommandBufferLevel.VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            commandBufferCount = 1
        )

        commandBuffer = Vulkan.vkAllocateCommandBuffers(device, allocInfo)
    }

    private fun createCommandPool() {
        val (graphicsFamily, presentFamily) = findQueueFamilies(physicalDevice, surface)

        val poolInfo = VkCommandPoolCreateInfo(
            flags = VkCommandPoolCreateFlagBits.VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT.value,
            queueFamilyIndex = graphicsFamily!!
        )

        commandPool = Vulkan.vkCreateCommandPool(device, poolInfo)
    }

    private fun createFramebuffers() {
        swapChainFrameBuffers = swapChainImageViews.map { imageView ->
            val frameBufferInfo = VkFramebufferCreateInfo(
                renderPass = renderPass,
                pAttachments = arrayOf(imageView),
                width = swapChainExtent.width,
                height = swapChainExtent.height,
                layers = 1
            )
            Vulkan.vkCreateFramebuffer(device, frameBufferInfo)
        }.toList()
    }

    private fun createRenderPass() {
        renderPass = Vulkan.vkCreateRenderPass(
            device, VkRenderPassCreateInfo(
                pAttachments = arrayOf(
                    VkAttachmentDescription(
                        format = swapChainImageFormat,
                        initialLayout = VkImageLayout.VK_IMAGE_LAYOUT_UNDEFINED,
                        finalLayout = VkImageLayout.VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
                    )
                ),
                pSubpasses = arrayOf(
                    VkSubpassDescription(
                        pipelineBindPoint = VkPipelineBindPoint.VK_PIPELINE_BIND_POINT_GRAPHICS,
                        pColorAttachments = arrayOf(
                            VkAttachmentReference(
                                attachment = 0,
                                layout = VkImageLayout.VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
                            )
                        )
                    )
                ),
                pDependencies = arrayOf(
                    VkSubpassDependency(
                        srcSubpass = VK_SUBPASS_EXTERNAL,
                        dstSubpass = 0,
                        srcStageMask = VkPipelineStageFlagBits.VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT.value,
                        srcAccessMask = 0,
                        dstStageMask = VkPipelineStageFlagBits.VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT.value,
                        dstAccessMask = VkAccessFlagBits.VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT.value,
                    )
                )
            )
        )
    }

    private fun createInstance() {
        val appInfo = VkApplicationInfo(
            pApplicationName = "Awake Vulkan - Application",
            pEngineName = "Awake Vulkan - Engine",
            apiVersion = Version(1, 3, 0).vkVersion
        )
        val layerProperties = getAppLayerProps()
        val layerExtProps = layerProperties.map { layer ->
            getAppExtProps(layer)
        }.flatten()

        val extProperties = (getAppExtProps() + layerExtProps).distinct()

        val createInfo = VkInstanceCreateInfo(
            pApplicationInfo = arrayOf(appInfo),
            ppEnabledLayerNames = layerProperties.toTypedArray(),
            ppEnabledExtensionNames = extProperties.toTypedArray()
        )
        instance = Vulkan.vkCreateInstance(createInfo)
    }

    private fun pickPhysicalDevice() {
        val physicalDevices =
            Vulkan.vkEnumeratePhysicalDevices(instance).map { VkPhysicalDevice(it, instance) }
        if (physicalDevices.isNotEmpty()) {
            // find a gpu
            val gpu = physicalDevices.find { vkDevice ->
                val properties = Vulkan.vkGetPhysicalDeviceProperties(vkDevice.physicalDevice)
                val features = Vulkan.vkGetPhysicalDeviceFeatures(vkDevice.physicalDevice)
                val hasGeometry = features.geometryShader
                val isIntegratedGPU =
                    properties.deviceType == VkPhysicalDeviceType.VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU
                val isDiscreteGPU =
                    properties.deviceType == VkPhysicalDeviceType.VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
                val isVirtualGPU =
                    properties.deviceType == VkPhysicalDeviceType.VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU
                isIntegratedGPU || isDiscreteGPU || isVirtualGPU
            } ?: throw Exception("Cannot find suitable gpu!")
            physicalDevice = gpu.physicalDevice
        }
    }

    private fun createLogicalDevice() {
        // Queue families
        val queueFamilyProperties =
            Vulkan.vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice)
        val indices = findQueueFamilies(physicalDevice, surface)

        if (!isSwapChainSupported(physicalDevice, surface)) {
            Log.w("Vulkan", "SwapChain not supported")
        }

        if (!indices.isComplete()) {
            // graphics not supported?
            throw Exception("GPU graphics / Presentation not supported")
        }

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

        val features = Vulkan.vkGetPhysicalDeviceFeatures(physicalDevice)
        val deviceExtensions =
            Vulkan.vkEnumerateDeviceExtensionProperties(physicalDevice)
                .map { it.extensionName }.toList()
        val deviceInfo = VkDeviceCreateInfo(
            pQueueCreateInfos = queueInfos.toTypedArray(),
            pEnabledFeatures = arrayOf(features),
            ppEnabledExtensionNames = deviceExtensions.toTypedArray()
        )
        device = Vulkan.vkCreateDevice(physicalDevice, deviceInfo) // VkDevice


        graphicsQueue = Vulkan.vkGetDeviceQueue(
            device,
            indices.graphicsFamily!!,
            0
        ) // TODO where to get queueIndex??
        presentQueue = Vulkan.vkGetDeviceQueue(
            device,
            indices.presentFamily!!,
            0
        ) // TODO where to get queueIndex??
    }


    private fun setupDebugMessenger() {
        val androidLogCallback: (String, String) -> Unit = { severity, message ->
            when (severity) {
                "Warning" -> Log.w("AwakeVk", message)
                "Info" -> Log.i("AwakeVk", message)
                "Error" -> Log.e("AwakeVk", message)
                "Verbose" -> Log.v("AwakeVk", message)
                else -> Log.d("AwakeVk", message)
            }
        }
        val createInfo = VkDebugUtilsMessengerCreateInfoEXT(
            pfnUserCallback = { severity, messageType, callbackData, userData ->
                DebugUtilsFormattedCallback(androidLogCallback).invoke(
                    severity,
                    messageType,
                    callbackData,
                    userData
                )
            },
            pUserData = null
        )
        debugUtilsMessenger = Vulkan.vkCreateDebugUtilsMessengerEXT(instance, createInfo)
    }

    private fun swapChain() {
        val (capabilities, formats, presentModes) = querySwapChainSupport(physicalDevice, surface)
        val (format, colorSpace) = chooseSwapSurfaceFormat(formats)
        val presentMode = chooseSwapPresentMode(presentModes)
        val extent = chooseSwapExtent(capabilities, context)

        val imageCount = (capabilities.minImageCount + 1).coerceIn(1, capabilities.maxImageCount)

        val indices = findQueueFamilies(physicalDevice, surface)
        var queueFamilyIndices: Array<Int>? =
            arrayOf(indices.graphicsFamily!!, indices.presentFamily!!)
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
            pQueueFamilyIndices = queueFamilyIndices,
            preTransform = preTransform,
            compositeAlpha = compositeAlpha,
            presentMode = presentMode,
            clipped = true,
            oldSwapchain = 0
        )
        swapChainImageFormat = format
        swapChain = Vulkan.vkCreateSwapchainKHR(device, createInfo)
        swapChainExtent = extent
        createImageViews()
    }

    private fun createImageViews() {
        val swapChainImages = Vulkan.vkGetSwapchainImagesKHR(device, swapChain)
        swapChainImageViews = swapChainImages.map { swapChainImage ->
            val createInfo = VkImageViewCreateInfo(
                image = swapChainImage,
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
    }

    fun createShaderModule(code: IntArray): Long {
        val createInfo = VkShaderModuleCreateInfo(
            pCode = code
        )
        return Vulkan.vkCreateShaderModule(device, createInfo)
    }

    fun ByteArray.toIntArray(): IntArray {
        val byteBuffer = ByteBuffer.wrap(this).order(ByteOrder.nativeOrder()).asIntBuffer()
        val unsignedByteArray = IntArray(byteBuffer.remaining())
        byteBuffer.get(unsignedByteArray)
        return unsignedByteArray
    }

    @OptIn(ExperimentalResourceApi::class)
    private fun createGraphicsPipeline() {
        runBlocking {
            // WARNING: make sure the .spv vulkan version match, this might cause out of memory
            val fragShaderCode = resource("assets/shader/vulkan/triangle.frag.spv").readBytes()
            val vertShaderCode = resource("assets/shader/vulkan/triangle.vert.spv").readBytes()

            val fragShaderModule = createShaderModule(fragShaderCode.toIntArray())
            val vertShaderModule = createShaderModule(vertShaderCode.toIntArray())

            // process shader
            val fragShaderStageInfo = VkPipelineShaderStageCreateInfo(
                stage = VkShaderStageFlagBits.FRAGMENT,
                module = fragShaderModule,
                pName = "main"
            )
            val vertShaderStageInfo = VkPipelineShaderStageCreateInfo(
                stage = VkShaderStageFlagBits.VERTEX,
                module = vertShaderModule,
                pName = "main"
            )
            val shaderStages = arrayOf(fragShaderStageInfo, vertShaderStageInfo)

            pipelineLayout = Vulkan.vkCreatePipelineLayout(device, VkPipelineLayoutCreateInfo())
            val createInfos = arrayOf(
                VkGraphicsPipelineCreateInfo(
                    pStages = shaderStages,
//                    pVertexInputState = arrayOf(
//                        VkPipelineVertexInputStateCreateInfo(
//                            pVertexBindingDescriptions = arrayOf(
//                                VkVertexInputBindingDescription(
//                                    0,  // Index of the binding
//                                    4, // Size of each vertex data element
//                                    VkVertexInputRate.VK_VERTEX_INPUT_RATE_VERTEX // Input rate (per vertex)
//                                )
//                            ),
//                            pVertexAttributeDescriptions = arrayOf(
//                                VkVertexInputAttributeDescription(
//                                    0, // Which binding this attribute (position) is associated with
//                                    0, // Corresponds to layout (location = 0) in the shader
//                                    VkFormat.VK_FORMAT_R32G32B32A32_SFLOAT, // Format of the attribute data
//                                    0
//                                )
//                            )
//                        )
//                    ),
                    pDynamicState = arrayOf(
                        VkPipelineDynamicStateCreateInfo(
                            pDynamicStates = arrayOf(
                                VkDynamicState.VK_DYNAMIC_STATE_VIEWPORT,
                                VkDynamicState.VK_DYNAMIC_STATE_SCISSOR,
                            )
                        )
                    ),
                    pInputAssemblyState = arrayOf(
                        VkPipelineInputAssemblyStateCreateInfo(
                            topology = VkPrimitiveTopology.VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
                            primitiveRestartEnable = false
                        )
                    ),
                    pViewportState = arrayOf(
                        VkPipelineViewportStateCreateInfo(
                            pViewports = arrayOf(
                                VkViewport(
                                    width = swapChainExtent.width.toFloat(),
                                    height = swapChainExtent.height.toFloat(),
                                )
                            ),
                            pScissors = arrayOf(
                                VkRect2D(
                                    offset = VkOffset2D(),
                                    extent = swapChainExtent
                                )
                            )
                        )
                    ),
                    pColorBlendState = arrayOf(
                        VkPipelineColorBlendStateCreateInfo(
                            pAttachments = arrayOf(VkPipelineColorBlendAttachmentState())
                        )
                    ),
                    layout = pipelineLayout,
                    renderPass = renderPass,
                    subpass = 0,
                    basePipelineHandle = 0, // Optional
                    basePipelineIndex = -1 // Optional
                )
            )
            pipelineCache = Vulkan.vkCreatePipelineCache(device, VkPipelineCacheCreateInfo())
            graphicsPipeline = Vulkan.vkCreateGraphicsPipelines(
                device, pipelineCache, createInfos
            )

            Vulkan.vkDestroyShaderModule(device, fragShaderModule)
            Vulkan.vkDestroyShaderModule(device, vertShaderModule)
        }
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

    private fun createSurface(window: Surface): VkSurfaceKHR {
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

    private fun cleanSwapChain() {
        swapChainImageViews.forEach { imageView ->
            Vulkan.vkDestroyImageView(device, imageView)
        }
        swapChainFrameBuffers.forEach { frameBuffer ->
            Vulkan.vkDestroyFramebuffer(device, frameBuffer)
        }
        Vulkan.vkDestroySwapchainKHR(device, swapChain)
    }

    private fun destroy() {
        cleanSwapChain()

//        for (var MAX_FRAMES_IN_FLIGHT) {
        Vulkan.vkDestroySemaphore(device, imageAvailableSemaphore)
        Vulkan.vkDestroySemaphore(device, renderFinishedSemaphore)
        Vulkan.vkDestroyFence(device, inFlightFence)
//        }
//      Vulkan.vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
        Vulkan.vkDestroyCommandPool(device, commandPool)

        graphicsPipeline.forEach { pipeline ->
            Vulkan.vkDestroyPipeline(device, pipeline)
        }

        Vulkan.vkDestroyPipelineLayout(device, pipelineLayout)
        Vulkan.vkDestroyRenderPass(device, renderPass)
        Vulkan.vkDestroyPipelineCache(device, pipelineCache)

        Vulkan.vkDestroySurfaceKHR(instance, surface)
        Vulkan.vkDestroyDevice(device)
        Vulkan.vkDestroyDebugUtilsMessengerEXT(instance, debugUtilsMessenger)
        Vulkan.vkDestroyInstance(instance)
    }
}