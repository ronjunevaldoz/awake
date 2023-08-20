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
import io.github.ronjunevaldoz.awake.vulkan.models.VkRect2D

sealed class VkClearValue

sealed class VkClearColorValue : VkClearValue() {
    class Float32(val values: FloatArray = FloatArray(4)) : VkClearColorValue() {

        init {
            require(values.size == 4) { "float32 array must have a size of 4" }
        }
    }

    class Int32(val values: IntArray = IntArray(4)) : VkClearColorValue() {
        init {
            require(values.size == 4) { "int32 array must have a size of 4" }
        }
    }

    @OptIn(ExperimentalUnsignedTypes::class)
    class UInt32(val values: UIntArray = UIntArray(4)) : VkClearColorValue() {
        init {
            require(values.size == 4) { "uint32 array must have a size of 4" }
        }
    }

    companion object {
        fun rgba(r: Float, g: Float, b: Float, a: Float) = Float32().apply {
            values[0] = r
            values[1] = g
            values[2] = b
            values[3] = a
        }

        fun rgba(r: Int, g: Int, b: Int, a: Int) = Int32().apply {
            values[0] = r
            values[1] = g
            values[2] = b
            values[3] = a
        }
    }
}

data class VkClearDepthStencilValue(
    val depth: Float,
    val stencil: Int
) : VkClearValue()

class VkRenderPassBeginInfo(
    val sType: VkStructureType = VkStructureType.VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
    val pNext: Any? = null,
    @VkHandleRef("VkRenderPass")
    val renderPass: VkHandle = 0,
    @VkHandleRef("VkFramebuffer")
    val framebuffer: VkHandle = 0,
    val renderArea: VkRect2D = VkRect2D(),
    @VkArray("clearValueCount")
    val pClearValues: Array<VkClearValue>? = null
)