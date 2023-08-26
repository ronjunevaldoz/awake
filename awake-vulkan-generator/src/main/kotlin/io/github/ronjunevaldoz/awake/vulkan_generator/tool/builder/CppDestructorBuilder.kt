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

package io.github.ronjunevaldoz.awake.vulkan_generator.tool.builder

import io.github.ronjunevaldoz.awake.vulkan_generator.tool.dsl.CppFunctionDSL

@CppFunctionDSL
class CppDestructorBuilder(private val indent: Int = 1, private val withInterface: Boolean) {
    private val body = StringBuilder()

    fun body(indent: Int = 1, functionBody: CppFunctionBodyBuilder.() -> Unit) {
        this.body.apply {
            val bodyBuilder = CppFunctionBodyBuilder(if (withInterface) 1 else indent)
            bodyBuilder.functionBody()
            append(bodyBuilder.build())
        }
    }

    fun build(className: String): String {
        val indentation = "    ".repeat(if (withInterface) 0 else indent)
        val function = if (withInterface) {
            "$className::~$className()"
        } else {
            "$indentation~$className()"
        }
        return buildString {
            append(function)
            append(" {\n")
            append(body)
            append("$indentation}\n")
        }
    }

    fun buildInterface(className: String): String {
        val indentation = "    ".repeat(indent)
        return "$indentation~$className();"
    }
}