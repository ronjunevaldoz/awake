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

package io.github.ronjunevaldoz.awake.vulkan.physicaldevice

import io.github.ronjunevaldoz.awake.vulkan.VK_UUID_SIZE
import io.github.ronjunevaldoz.awake.vulkan.enums.VkPhysicalDeviceType

class VkPhysicalDeviceProperties(
    val apiVersion: UInt = 0u,
    val driverVersion: UInt = 0u,
    val vendorID: UInt = 0u,
    val deviceID: UInt = 0u,
    val deviceType: UInt = 0u,
    val deviceName: String = "",
    val pipelineCacheUUID: ByteArray = ByteArray(VK_UUID_SIZE.toInt()),
    val limits: VkPhysicalDeviceLimits = VkPhysicalDeviceLimits(),
    val sparseProperties: VkPhysicalDeviceSparseProperties = VkPhysicalDeviceSparseProperties()
)

fun VkPhysicalDeviceType.eq(deviceType: UInt): Boolean {
    return this.value == deviceType.toInt()
}

infix fun UInt.eq(type: VkPhysicalDeviceType): Boolean {
    return type.eq(this)
}