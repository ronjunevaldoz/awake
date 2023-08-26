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

package io.github.ronjunevaldoz.awake.vulkan.enums

enum class VkDynamicState(val value: Int) {
    VK_DYNAMIC_STATE_VIEWPORT(0),
    VK_DYNAMIC_STATE_SCISSOR(1),
    VK_DYNAMIC_STATE_LINE_WIDTH(2),
    VK_DYNAMIC_STATE_DEPTH_BIAS(3),
    VK_DYNAMIC_STATE_BLEND_CONSTANTS(4),
    VK_DYNAMIC_STATE_DEPTH_BOUNDS(5),
    VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK(6),
    VK_DYNAMIC_STATE_STENCIL_WRITE_MASK(7),
    VK_DYNAMIC_STATE_STENCIL_REFERENCE(8),
    VK_DYNAMIC_STATE_CULL_MODE(1000267000),
    VK_DYNAMIC_STATE_FRONT_FACE(1000267001),
    VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY(1000267002),
    VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT(1000267003),
    VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT(1000267004),
    VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE(1000267005),
    VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE(1000267006),
    VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE(1000267007),
    VK_DYNAMIC_STATE_DEPTH_COMPARE_OP(1000267008),
    VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE(1000267009),
    VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE(1000267010),
    VK_DYNAMIC_STATE_STENCIL_OP(1000267011),
    VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE(1000377001),
    VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE(1000377002),
    VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE(1000377004),
    VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV(1000087000),
    VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT(1000099000),
    VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT(1000143000),
    VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR(1000347000),
    VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV(1000164004),
    VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV(1000164006),
    VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV(1000205001),
    VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR(1000226000),
    VK_DYNAMIC_STATE_LINE_STIPPLE_EXT(1000259000),
    VK_DYNAMIC_STATE_VERTEX_INPUT_EXT(1000352000),
    VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT(1000377000),
    VK_DYNAMIC_STATE_LOGIC_OP_EXT(1000377003),
    VK_DYNAMIC_STATE_COLOR_WRITE_ENABLE_EXT(1000381000),
    VK_DYNAMIC_STATE_CULL_MODE_EXT(VK_DYNAMIC_STATE_CULL_MODE.value),
    VK_DYNAMIC_STATE_FRONT_FACE_EXT(VK_DYNAMIC_STATE_FRONT_FACE.value),
    VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY_EXT(VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY.value),
    VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT_EXT(VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT.value),
    VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT_EXT(VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT.value),
    VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE_EXT(VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE.value),
    VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE_EXT(VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE.value),
    VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE_EXT(VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE.value),
    VK_DYNAMIC_STATE_DEPTH_COMPARE_OP_EXT(VK_DYNAMIC_STATE_DEPTH_COMPARE_OP.value),
    VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE_EXT(VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE.value),
    VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE_EXT(VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE.value),
    VK_DYNAMIC_STATE_STENCIL_OP_EXT(VK_DYNAMIC_STATE_STENCIL_OP.value),
    VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE_EXT(VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE.value),
    VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE_EXT(VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE.value),
    VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE_EXT(VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE.value),
    VK_DYNAMIC_STATE_MAX_ENUM(0x7FFFFFFF)
}