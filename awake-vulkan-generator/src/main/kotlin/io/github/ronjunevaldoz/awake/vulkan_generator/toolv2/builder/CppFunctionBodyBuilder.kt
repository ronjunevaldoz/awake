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

package io.github.ronjunevaldoz.awake.vulkan_generator.toolv2.builder

import io.github.ronjunevaldoz.awake.vulkan_generator.toolv2.dsl.CppFunctionBodyDSL

@CppFunctionBodyDSL
class CppFunctionBodyBuilder(private val indent: Int) {
    private val bodyContent = StringBuilder()

    fun child(line: String) {
        val indentation = "    ".repeat(indent)
        bodyContent.append("$indentation$line\n")
    }

    fun build(): String {
        return bodyContent.toString()
    }
}