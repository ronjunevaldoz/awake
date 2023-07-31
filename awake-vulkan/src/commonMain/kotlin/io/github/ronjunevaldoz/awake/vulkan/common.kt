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


val VK_UUID_SIZE = 16U


//typedef uint32_t VkBool32;
//typedef uint64_t VkDeviceAddress;
//typedef uint64_t VkDeviceSize;
//typedef uint32_t VkFlags;
//typedef uint32_t VkSampleMask;
typealias VkBool32 = Boolean
typealias VkDeviceAddress = Long
typealias VkDeviceSize = Long
typealias VkFlags = Int
typealias VkSampleMask = Int

enum class VulkanExtension(val extensionName: String) {
    VK_KHR_SWAPCHAIN("VK_KHR_swapchain"),
    VK_KHR_MAINTENANCE1("VK_KHR_maintenance1"),
    VK_KHR_SHADER_DRAW_PARAMETERS("VK_KHR_shader_draw_parameters"),
    VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES2("VK_KHR_get_physical_device_properties2"),
    VK_KHR_EXTERNAL_MEMORY_CAPABILITIES("VK_KHR_external_memory_capabilities"),
    VK_KHR_EXTERNAL_MEMORY("VK_KHR_external_memory"),
    VK_KHR_EXTERNAL_MEMORY_FD("VK_KHR_external_memory_fd"),
    VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES("VK_KHR_external_semaphore_capabilities"),
    VK_KHR_EXTERNAL_SEMAPHORE("VK_KHR_external_semaphore"),
    VK_KHR_EXTERNAL_SEMAPHORE_FD("VK_KHR_external_semaphore_fd"),
    VK_KHR_SURFACE("VK_KHR_surface"),
    VK_KHR_ANDROID_SURFACE("VK_KHR_android_surface"),
    VK_KHR_XCB_SURFACE("VK_KHR_xcb_surface"),
    VK_KHR_XLIB_SURFACE("VK_KHR_xlib_surface"),
    VK_KHR_WIN32_SURFACE("VK_KHR_win32_surface");

    companion object {
        fun fromString(name: String): VulkanExtension? =
            values().find { it.extensionName == name }
    }
}