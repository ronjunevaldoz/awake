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

package io.github.ronjunevaldoz.awake.vulkan.models.info

import io.github.ronjunevaldoz.awake.vulkan.VkArray
import io.github.ronjunevaldoz.awake.vulkan.VkFlags
import io.github.ronjunevaldoz.awake.vulkan.enums.VkStructureType
import io.github.ronjunevaldoz.awake.vulkan.models.physicaldevice.VkPhysicalDeviceFeatures

class VkDeviceCreateInfo(
    val sType: VkStructureType = VkStructureType.VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    val pNext: Any? = null,
    val flags: VkDeviceCreateFlags = 0,
    @field:VkArray(sizeAlias = "queueCreateInfoCount")
    val pQueueCreateInfos: Array<VkDeviceQueueCreateInfo> = emptyArray(),
    @field:VkArray(sizeAlias = "enabledLayerCount")
    val ppEnabledLayerNames: Array<String>? = null,
    @field:VkArray(sizeAlias = "enabledExtensionCount")
    val ppEnabledExtensionNames: Array<String>? = null,
    @field:VkArray
    val pEnabledFeatures: Array<VkPhysicalDeviceFeatures> = emptyArray()
)
typealias VkDeviceCreateFlags = VkFlags