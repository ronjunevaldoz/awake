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
import io.github.ronjunevaldoz.awake.vulkan_generator.toolv2.dsl.CppFunctionDSL

@CppFunctionDSL
class CppFunctionBuilder(
    private val returnType: String,
    private val indent: Int = 1,
    private val className: String,
    private val withInterface: Boolean
) {
    private var parameters: List<Pair<String, String>> = emptyList()
    private val functionBody = StringBuilder()

    fun parameters(parameters: List<Pair<String, String>>) {
        this.parameters = parameters
    }

    @CppFunctionBodyDSL
    fun body(indent: Int = 1, functionBody: CppFunctionBodyBuilder.() -> Unit) {
        this.functionBody.apply {
            val bodyBuilder = CppFunctionBodyBuilder(if (withInterface) 1 else indent)
            bodyBuilder.functionBody()
            append(bodyBuilder.build())
        }
    }

    fun build(name: String): String {
        val indentation = "    ".repeat(if (withInterface) 0 else indent)
        val cppParameters =
            parameters.joinToString(", ") { "${it.second} ${it.first}" }
        val function = if (withInterface) {
            "$returnType\n$className::$name($cppParameters)"
        } else {
            "$indentation$returnType $name($cppParameters)"
        }
        return buildString {
            append(function)
            append(" {\n")
            append(functionBody)
            append("$indentation}\n")
        }
    }

    fun buildInterface(name: String): String {
        val indentation = "    ".repeat(indent)
        val cppParameters = parameters.joinToString(", ") { "${it.second} ${it.first}" }
        return "$indentation$returnType $name($cppParameters);"
    }
}