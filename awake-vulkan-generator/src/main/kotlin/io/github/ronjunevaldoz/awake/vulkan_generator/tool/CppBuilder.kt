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

package io.github.ronjunevaldoz.awake.vulkan_generator.tool

import io.github.ronjunevaldoz.awake.vulkan_generator.tool.builder.CppClassBuilder

fun cppClass(
    className: String,
    fileDescription: String,
    block: CppClassBuilder.() -> Unit
): Pair<String, String> {
    val builder = CppClassBuilder(className, fileDescription)
    builder.block()
    return Pair(builder.buildInterface(), builder.buildClass())
}