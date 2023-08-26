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

package io.github.ronjunevaldoz.awake.vulkan.models

import io.github.ronjunevaldoz.awake.vulkan.VkMutator
import io.github.ronjunevaldoz.awake.vulkan.enums.VkQueueFlags

@VkMutator
data class VkQueueFamilyProperties(
    val queueFlags: VkQueueFlags = 0,
    val queueCount: UInt = 0u,
    val timestampValidBits: UInt = 0u,
    val minImageTransferGranularity: VkExtent3D = VkExtent3D()
)