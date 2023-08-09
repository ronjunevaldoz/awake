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

package io.github.ronjunevaldoz.awake.vulkan.physicaldevice

import io.github.ronjunevaldoz.awake.vulkan.VkBool32
import io.github.ronjunevaldoz.awake.vulkan.VkDeserializer

@VkDeserializer
data class VkPhysicalDeviceFeatures(
    val robustBufferAccess: VkBool32 = false,
    val fullDrawIndexUint32: VkBool32 = false,
    val imageCubeArray: VkBool32 = false,
    val independentBlend: VkBool32 = false,
    val geometryShader: VkBool32 = false,
    val tessellationShader: VkBool32 = false,
    val sampleRateShading: VkBool32 = false,
    val dualSrcBlend: VkBool32 = false,
    val logicOp: VkBool32 = false,
    val multiDrawIndirect: VkBool32 = false,
    val drawIndirectFirstInstance: VkBool32 = false,
    val depthClamp: VkBool32 = false,
    val depthBiasClamp: VkBool32 = false,
    val fillModeNonSolid: VkBool32 = false,
    val depthBounds: VkBool32 = false,
    val wideLines: VkBool32 = false,
    val largePoints: VkBool32 = false,
    val alphaToOne: VkBool32 = false,
    val multiViewport: VkBool32 = false,
    val samplerAnisotropy: VkBool32 = false,
    val textureCompressionETC2: VkBool32 = false,
    val textureCompressionASTC_LDR: VkBool32 = false,
    val textureCompressionBC: VkBool32 = false,
    val occlusionQueryPrecise: VkBool32 = false,
    val pipelineStatisticsQuery: VkBool32 = false,
    val vertexPipelineStoresAndAtomics: VkBool32 = false,
    val fragmentStoresAndAtomics: VkBool32 = false,
    val shaderTessellationAndGeometryPointSize: VkBool32 = false,
    val shaderImageGatherExtended: VkBool32 = false,
    val shaderStorageImageExtendedFormats: VkBool32 = false,
    val shaderStorageImageMultisample: VkBool32 = false,
    val shaderStorageImageReadWithoutFormat: VkBool32 = false,
    val shaderStorageImageWriteWithoutFormat: VkBool32 = false,
    val shaderUniformBufferArrayDynamicIndexing: VkBool32 = false,
    val shaderSampledImageArrayDynamicIndexing: VkBool32 = false,
    val shaderStorageBufferArrayDynamicIndexing: VkBool32 = false,
    val shaderStorageImageArrayDynamicIndexing: VkBool32 = false,
    val shaderClipDistance: VkBool32 = false,
    val shaderCullDistance: VkBool32 = false,
    val shaderFloat64: VkBool32 = false,
    val shaderInt64: VkBool32 = false,
    val shaderInt16: VkBool32 = false,
    val shaderResourceResidency: VkBool32 = false,
    val shaderResourceMinLod: VkBool32 = false,
    val sparseBinding: VkBool32 = false,
    val sparseResidencyBuffer: VkBool32 = false,
    val sparseResidencyImage2D: VkBool32 = false,
    val sparseResidencyImage3D: VkBool32 = false,
    val sparseResidency2Samples: VkBool32 = false,
    val sparseResidency4Samples: VkBool32 = false,
    val sparseResidency8Samples: VkBool32 = false,
    val sparseResidency16Samples: VkBool32 = false,
    val sparseResidencyAliased: VkBool32 = false,
    val variableMultisampleRate: VkBool32 = false,
    val inheritedQueries: VkBool32 = false
)