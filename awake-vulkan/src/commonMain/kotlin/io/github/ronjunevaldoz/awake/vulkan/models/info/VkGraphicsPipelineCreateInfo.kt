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

import io.github.ronjunevaldoz.awake.vulkan.enums.VkPipelineCreateFlags
import io.github.ronjunevaldoz.awake.vulkan.enums.VkStructureType

class VkGraphicsPipelineCreateInfo(
    val sType: VkStructureType = VkStructureType.VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
    val pNext: Any? = null,
    val flags: VkPipelineCreateFlags = 0,
    val pStages: Array<VkPipelineShaderStageCreateInfo> = emptyArray(),
    val pVertexInputState: Long = 0,
    val pInputAssemblyState: Long = 0,
    val pTessellationState: Long = 0,
    val pViewportState: Long = 0,
    val pRasterizationState: Long = 0,
    val pMultisampleState: Long = 0,
    val pDepthStencilState: Long = 0,
    val pColorBlendState: Long = 0,
    val pDynamicState: Long = 0,
    val layout: Long = 0, // VkPipelineLayout handle
    val renderPass: Long = 0, // VkRenderPass handle
    val subpass: Int = 0,
    val basePipelineHandle: Long = 0, // VkPipeline handle
    val basePipelineIndex: Int = 0
) {
    val stageCount: Int = pStages.size
}