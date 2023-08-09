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

package io.github.ronjunevaldoz.awake.vulkan

import kotlin.reflect.KClass

@Target(AnnotationTarget.FIELD)
annotation class VkPointer

@Target(
    AnnotationTarget.FIELD,
    AnnotationTarget.TYPEALIAS,
    AnnotationTarget.PROPERTY,
    AnnotationTarget.VALUE_PARAMETER,
    AnnotationTarget.TYPE, AnnotationTarget.CLASS
)
annotation class VkHandleRef(val name: String)


@Target(AnnotationTarget.FIELD)
annotation class VkType(val name: String = "", val unsigned: Boolean = true)

/**
 * @param sizeSuffix <elementType> [sizeSuffix] otherwise do not generate
 * @param elementCast std::vector<[elementCast]>
 * @param stride multiplier for array size for example given UInt::class -> sizeOf(uint32_t)
 */
@Target(AnnotationTarget.FIELD)
annotation class VkArray(
    val sizeSuffix: String = "Count",
    val elementCast: KClass<*> = Nothing::class,
    val stride: KClass<*> = Nothing::class
)

/**
 * Allows to generate toObject cpp method
 */
@Target(AnnotationTarget.CLASS)
annotation class VkDeserializer