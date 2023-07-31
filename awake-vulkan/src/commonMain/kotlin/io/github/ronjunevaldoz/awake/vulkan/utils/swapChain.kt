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

package io.github.ronjunevaldoz.awake.vulkan.utils

import io.github.ronjunevaldoz.awake.vulkan.Vulkan
import io.github.ronjunevaldoz.awake.vulkan.VulkanExtension
import io.github.ronjunevaldoz.awake.vulkan.enums.VkPresentModeKHR
import io.github.ronjunevaldoz.awake.vulkan.models.VkSurfaceKHR
import io.github.ronjunevaldoz.awake.vulkan.physicaldevice.VkPhysicalDevice
import io.github.ronjunevaldoz.awake.vulkan.presentation.swapchain.VkSurfaceCapabilitiesKHR
import io.github.ronjunevaldoz.awake.vulkan.presentation.swapchain.VkSurfaceFormatKHR


data class SwapChainSupportDetails(
    val capabilities: VkSurfaceCapabilitiesKHR,
    val formats: List<VkSurfaceFormatKHR>,
    val presentModes: List<VkPresentModeKHR>,
)

fun isSwapChainSupported(gpu: VkPhysicalDevice, surface: VkSurfaceKHR): Boolean {
    var swapChainAdequate = false
    // verify swap chain extension supported
    if (isDeviceExtSupported(gpu.physicalDevice, VulkanExtension.VK_KHR_SWAPCHAIN)) {
        val swapChainSupport = querySwapChainSupport(gpu, surface)
        swapChainAdequate =
            swapChainSupport.formats.isNotEmpty() && swapChainSupport.presentModes.isNotEmpty()
    }
    return swapChainAdequate
}


fun querySwapChainSupport(gpu: VkPhysicalDevice, surface: VkSurfaceKHR): SwapChainSupportDetails {
    val capabilities =
        Vulkan.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu.physicalDevice, surface.surface)
    val formats = Vulkan.vkGetPhysicalDeviceSurfaceFormatsKHR(gpu.physicalDevice, surface.surface)
    val presentModes =
        Vulkan.vkGetPhysicalDeviceSurfacePresentModesKHR(gpu.physicalDevice, surface.surface)

    return SwapChainSupportDetails(
        capabilities,
        formats.toList(),
        presentModes.toList()
    )
}