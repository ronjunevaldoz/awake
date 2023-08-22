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
import io.github.ronjunevaldoz.awake.vulkan.VkHandle
import io.github.ronjunevaldoz.awake.vulkan.VkHandleRef
import io.github.ronjunevaldoz.awake.vulkan.enums.VkStructureType
import io.github.ronjunevaldoz.awake.vulkan.models.VkClearValue
import io.github.ronjunevaldoz.awake.vulkan.models.VkRect2D

class VkRenderPassBeginInfo(
    val sType: VkStructureType = VkStructureType.VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    val pNext: Any? = null,
    @field:VkHandleRef("VkRenderPass")
    val renderPass: VkHandle = 0,
    @field:VkHandleRef("VkFramebuffer")
    val framebuffer: VkHandle = 0,
    val renderArea: VkRect2D = VkRect2D(),
    @VkArray("clearValueCount")
    val pClearValues: Array<VkClearValue>? = null
)