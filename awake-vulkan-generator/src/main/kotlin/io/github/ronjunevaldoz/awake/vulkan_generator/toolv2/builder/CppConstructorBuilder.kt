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

import io.github.ronjunevaldoz.awake.vulkan_generator.toolv2.dsl.CppFunctionDSL

@CppFunctionDSL
class CppConstructorBuilder(private val explicit: Boolean = false, private val indent: Int = 1) {
    private var parameters: List<Pair<String, String>> = emptyList()
    private val body = StringBuilder()

    fun parameters(parameters: List<Pair<String, String>>) {
        this.parameters = parameters
    }

    fun body(indent: Int = 1, functionBody: CppFunctionBodyBuilder.() -> Unit) {
        this.body.apply {
            val bodyBuilder = CppFunctionBodyBuilder(indent)
            bodyBuilder.functionBody()
            append(bodyBuilder.build())
        }
    }

    fun build(className: String): String {
        val indentation = "    ".repeat(indent)
        val cppParameters =
            parameters.joinToString(", ") { "${it.second} ${it.first}" }
        val prefix = if (explicit) "explicit " else ""
        return buildString {
            append("$indentation$prefix$className($cppParameters)")
            append(" {\n")
            append(body)
            append("$indentation}\n")
        }
    }
}