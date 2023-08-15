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

import io.github.ronjunevaldoz.awake.vulkan.models.VkAttachmentDescription
import io.github.ronjunevaldoz.awake.vulkan.models.VkAttachmentReference
import io.github.ronjunevaldoz.awake.vulkan.models.VkExtent2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkOffset2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkRect2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkStencilOpState
import io.github.ronjunevaldoz.awake.vulkan.models.VkSubpassDependency
import io.github.ronjunevaldoz.awake.vulkan.models.VkViewport
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkApplicationInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceQueueCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkGraphicsPipelineCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkRenderPassCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkSubpassDescription
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineCacheCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineColorBlendAttachmentState
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineColorBlendStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineDepthStencilStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineDynamicStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineInputAssemblyStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineLayoutCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineMultisampleStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineRasterizationStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineShaderStageCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineTessellationStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineVertexInputStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineViewportStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPushConstantRange
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkSpecializationInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkSpecializationMapEntry
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkVertexInputAttributeDescription
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkVertexInputBindingDescription
import io.github.ronjunevaldoz.awake.vulkan.physicaldevice.VkPhysicalDeviceFeatures
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.FileWriter
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.cmakeListTemplate
import io.github.ronjunevaldoz.awake.vulkan_generator.vulkan.generateJavaToVulkanCpp

fun main(args: Array<String>) {
    if (args.isNotEmpty()) {
        FileWriter.rootDir = args[0]
    }
    generateJavaToVulkanCpp<VkApplicationInfo>()
    generateJavaToVulkanCpp<VkPhysicalDeviceFeatures>()
    generateJavaToVulkanCpp<VkDeviceQueueCreateInfo>()
    generateJavaToVulkanCpp<VkDeviceCreateInfo>()
    generateJavaToVulkanCpp<VkExtent2D>()

    // pipeline
    generateJavaToVulkanCpp<VkSpecializationMapEntry>()
    generateJavaToVulkanCpp<VkSpecializationInfo>()
    generateJavaToVulkanCpp<VkPipelineShaderStageCreateInfo>()
    generateJavaToVulkanCpp<VkPushConstantRange>()
    generateJavaToVulkanCpp<VkPipelineLayoutCreateInfo>()
    generateJavaToVulkanCpp<VkPipelineCacheCreateInfo>()
    generateJavaToVulkanCpp<VkGraphicsPipelineCreateInfo>()
    // states
    generateJavaToVulkanCpp<VkStencilOpState>()
    generateJavaToVulkanCpp<VkPipelineColorBlendAttachmentState>()

    generateJavaToVulkanCpp<VkPipelineColorBlendStateCreateInfo>()
    generateJavaToVulkanCpp<VkPipelineDepthStencilStateCreateInfo>()
    generateJavaToVulkanCpp<VkPipelineMultisampleStateCreateInfo>()
    generateJavaToVulkanCpp<VkPipelineRasterizationStateCreateInfo>()
    generateJavaToVulkanCpp<VkPipelineTessellationStateCreateInfo>()
    // dynamic state
    generateJavaToVulkanCpp<VkPipelineDynamicStateCreateInfo>()
    // vertex input state
    generateJavaToVulkanCpp<VkVertexInputBindingDescription>()
    generateJavaToVulkanCpp<VkVertexInputAttributeDescription>()
    generateJavaToVulkanCpp<VkPipelineVertexInputStateCreateInfo>()
    // input assembly
    generateJavaToVulkanCpp<VkPipelineInputAssemblyStateCreateInfo>()
    generateJavaToVulkanCpp<VkOffset2D>()
    generateJavaToVulkanCpp<VkRect2D>()
    generateJavaToVulkanCpp<VkViewport>()
    generateJavaToVulkanCpp<VkPipelineViewportStateCreateInfo>()
    // render pass
    generateJavaToVulkanCpp<VkAttachmentReference>()
    generateJavaToVulkanCpp<VkAttachmentDescription>()
    generateJavaToVulkanCpp<VkSubpassDescription>()
    generateJavaToVulkanCpp<VkSubpassDependency>()
    generateJavaToVulkanCpp<VkRenderPassCreateInfo>()

    println(cmakeListTemplate("awake-vulkan/src/main/cpp/vulkan-kotlin/"))
}