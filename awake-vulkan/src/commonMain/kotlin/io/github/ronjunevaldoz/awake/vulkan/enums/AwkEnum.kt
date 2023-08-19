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

import io.github.ronjunevaldoz.awake.vulkan.VkFlags

interface VkEnum {
    val value: Int
}

infix fun VkEnum.or(other: VkEnum): Int {
    return this.value or other.value
}

infix fun VkEnum.has(bit: VkEnum): Boolean {
    return this.value and bit.value != 0
}

infix fun VkEnum.and(other: VkEnum): Int {
    return this.value and other.value
}

infix fun VkEnum.set(bit: VkEnum): VkFlags {
    return this.value or bit.value
}

infix fun VkEnum.clear(bit: VkSampleCountFlagBits): VkFlags {
    return this.value and bit.value.inv()
}
