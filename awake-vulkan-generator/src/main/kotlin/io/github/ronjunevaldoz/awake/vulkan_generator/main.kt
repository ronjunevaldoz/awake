/*
 * Awake
 * Awake.awake-vulkan-generator.main
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

package io.github.ronjunevaldoz.awake.vulkan_generator

import io.github.ronjunevaldoz.awake.vulkan.models.info.VkGraphicsPipelineCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkPipelineDynamicStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkPipelineVertexInputStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkVertexInputAttributeDescription
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkVertexInputBindingDescription
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.generateCpp

fun main() {
    generateCpp<VkGraphicsPipelineCreateInfo>()
    generateCpp<VkPipelineDynamicStateCreateInfo>()
    generateCpp<VkVertexInputBindingDescription>()
    generateCpp<VkVertexInputAttributeDescription>()
    generateCpp<VkPipelineVertexInputStateCreateInfo>()

}