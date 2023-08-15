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

package io.github.ronjunevaldoz.awake.vulkan.enums.flags

enum class VkAccessFlagBits(val value: Int) {
    VK_ACCESS_INDIRECT_COMMAND_READ_BIT(0x00000001),
    VK_ACCESS_INDEX_READ_BIT(0x00000002),
    VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT(0x00000004),
    VK_ACCESS_UNIFORM_READ_BIT(0x00000008),
    VK_ACCESS_INPUT_ATTACHMENT_READ_BIT(0x00000010),
    VK_ACCESS_SHADER_READ_BIT(0x00000020),
    VK_ACCESS_SHADER_WRITE_BIT(0x00000040),
    VK_ACCESS_COLOR_ATTACHMENT_READ_BIT(0x00000080),
    VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT(0x00000100),
    VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT(0x00000200),
    VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT(0x00000400),
    VK_ACCESS_TRANSFER_READ_BIT(0x00000800),
    VK_ACCESS_TRANSFER_WRITE_BIT(0x00001000),
    VK_ACCESS_HOST_READ_BIT(0x00002000),
    VK_ACCESS_HOST_WRITE_BIT(0x00004000),
    VK_ACCESS_MEMORY_READ_BIT(0x00008000),
    VK_ACCESS_MEMORY_WRITE_BIT(0x00010000),
    VK_ACCESS_NONE(0),
    VK_ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT(0x02000000),
    VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT(0x04000000),
    VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT(0x08000000),
    VK_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT(0x00100000),
    VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT(0x00080000),
    VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR(0x00200000),
    VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR(0x00400000),
    VK_ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT(0x01000000),
    VK_ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR(0x00800000),
    VK_ACCESS_COMMAND_PREPROCESS_READ_BIT_NV(0x00020000),
    VK_ACCESS_COMMAND_PREPROCESS_WRITE_BIT_NV(0x00040000),
    VK_ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV(VK_ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR.value),
    VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV(VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR.value),
    VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV(VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR.value),
    VK_ACCESS_NONE_KHR(VK_ACCESS_NONE.value),
    VK_ACCESS_FLAG_BITS_MAX_ENUM(0x7FFFFFFF)
}

typealias VkAccessFlags = Int