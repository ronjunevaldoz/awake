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

import io.github.ronjunevaldoz.awake.vulkan.models.VkExtent2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkOffset2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkRect2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkViewport
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceQueueCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkGraphicsPipelineCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkPipelineCacheCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkPipelineDynamicStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkPipelineInputAssemblyStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkPipelineVertexInputStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkPipelineViewportStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkShaderModuleCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkSwapchainCreateInfoKHR
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkVertexInputAttributeDescription
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkVertexInputBindingDescription
import io.github.ronjunevaldoz.awake.vulkan.physicaldevice.VkPhysicalDeviceFeatures
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.FileWriter
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.cmakeListTemplate
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.generateCpp

fun main(args: Array<String>) {
    if (args.isNotEmpty()) {
        FileWriter.rootDir = args[0]
    }
    generateCpp<VkDeviceCreateInfo>()
    // physical device
    generateCpp<VkPhysicalDeviceFeatures>()
    // queues & families
    generateCpp<VkDeviceQueueCreateInfo>()
    // swap chain
    generateCpp<VkExtent2D>()
    generateCpp<VkSwapchainCreateInfoKHR>()
    // graphics
    generateCpp<VkShaderModuleCreateInfo>()
    generateCpp<VkPipelineCacheCreateInfo>()
    generateCpp<VkGraphicsPipelineCreateInfo>()
    // dynamic state
    generateCpp<VkPipelineDynamicStateCreateInfo>()
    // vertex input state
    generateCpp<VkVertexInputBindingDescription>()
    generateCpp<VkVertexInputAttributeDescription>()
    generateCpp<VkPipelineVertexInputStateCreateInfo>()
    // input assembly
    generateCpp<VkPipelineInputAssemblyStateCreateInfo>()
    generateCpp<VkOffset2D>()
    generateCpp<VkRect2D>()
    generateCpp<VkViewport>()
    generateCpp<VkPipelineViewportStateCreateInfo>()
    println(cmakeListTemplate("awake-vulkan/src/main/cpp/common/utils/"))
}