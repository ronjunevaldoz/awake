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


/**
 * Check all possible extension from app etc..
 */
fun isAppExtSupported(vararg extensions: VulkanExtension): Boolean {
    val extensionProperties = Vulkan.vkEnumerateInstanceExtensionProperties()
//    Log.i("App Extensions", extensionProperties.joinToString("\n"))
    val supportedExtensions: Set<String> = extensionProperties.map { it.extensionName }.toSet()
    for (extension in extensions) {
        if (extension.extensionName in supportedExtensions) {
            return true
        }
    }
    return false
}

/**
 * Check all possible extension from device etc..
 */
fun isDeviceExtSupported(physicalDevice: Long, vararg extensions: VulkanExtension): Boolean {
    val extensionProperties = Vulkan.vkEnumerateDeviceExtensionProperties(physicalDevice)
//    Log.i("Device Extensions", extensionProperties.joinToString("\n"))
    val supportedExtensions: Set<String> = extensionProperties.map { it.extensionName }.toSet()
    for (extension in extensions) {
        if (extension.extensionName in supportedExtensions) {
            return true
        }
    }
    return false
}