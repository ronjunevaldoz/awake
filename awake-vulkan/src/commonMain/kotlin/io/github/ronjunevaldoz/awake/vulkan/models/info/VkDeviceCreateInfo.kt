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

import io.github.ronjunevaldoz.awake.vulkan.VkFlags
import io.github.ronjunevaldoz.awake.vulkan.physicaldevice.VkPhysicalDeviceFeatures

class VkDeviceCreateInfo(
    var sType: Int = 0,
    var pNext: Long = 0,
    var flags: VkDeviceCreateFlags = 0,
    var queueCreateInfoCount: UInt = 0u,
    var pQueueCreateInfos: List<VkDeviceQueueCreateInfo> = emptyList(),
    var enabledLayerCount: UInt = 0u,
    var ppEnabledLayerNames: List<String>? = null,
//    var enabledExtensionCount: UInt = 0u, not needed sinze we have a list
    var ppEnabledExtensionNames: List<String>? = null,
    var pEnabledFeatures: List<VkPhysicalDeviceFeatures> = emptyList()
)
typealias VkDeviceCreateFlags = VkFlags