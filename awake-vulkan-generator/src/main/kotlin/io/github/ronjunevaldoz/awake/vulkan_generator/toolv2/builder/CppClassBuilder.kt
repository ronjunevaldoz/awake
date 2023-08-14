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

import io.github.ronjunevaldoz.awake.vulkan_generator.toolv2.ClassMember
import io.github.ronjunevaldoz.awake.vulkan_generator.toolv2.dsl.CppClassDSL

@CppClassDSL
class CppClassBuilder(
    val className: String,
    val fileDescription: String,
    private val withInterface: Boolean = true
) {

    private val imports = mutableListOf<String>()
    val members = mutableListOf<ClassMember>()
    private val constructors = HashMap<String, String>()
    private val destructors = HashMap<String, String>()
    private val functions = HashMap<String, String>()

    fun member(accessModifier: String, type: String, name: String) {
        members.add(ClassMember(accessModifier, type, name))
    }

    fun import(import: String) {
        if (!imports.contains(import)) {
            imports.add(import)
        }
    }

    fun constructor(
        explicit: Boolean = false,
        indent: Int = 1,
        parameters: List<Pair<String, String>>,
        block: CppConstructorBuilder.() -> Unit
    ) {
        val builder =
            CppConstructorBuilder(if (withInterface) false else explicit, indent, withInterface)
        builder.parameters(parameters)
        builder.block()
        constructors[builder.buildInterface(className)] = builder.build(className)
    }

    fun destructor(
        indent: Int = 1,
        block: CppDestructorBuilder.() -> Unit
    ) {
        val builder = CppDestructorBuilder(indent, withInterface)
        builder.block()
        destructors[builder.buildInterface(className)] = builder.build(className)
    }

    fun function(
        indent: Int = 1,
        returnType: String = "void",
        name: String,
        parameters: List<Pair<String, String>> = emptyList(),
        block: CppFunctionBuilder.() -> Unit
    ) {
        val functionBuilder = CppFunctionBuilder(returnType, indent, className, withInterface)
        functionBuilder.parameters(parameters)
        functionBuilder.block()
        functions[functionBuilder.buildInterface(name)] = functionBuilder.build(name)
    }

    @CppClassDSL
    inline fun <reified T : Any> function(
        indent: Int = 1,
        name: String,
        vararg parameters: Pair<String, String>,
        noinline block: CppFunctionBuilder.() -> Unit
    ) {
        val returnType = kotlinTypeToCppType<T>()
        function(indent, returnType, name, parameters.toList(), block)
    }

    fun build(): String {
        return buildString {
            append("/*\n")
            append(" *  $className.cpp\n")
            append(" *  $fileDescription\n")
            append(" *  Created by Ron June Valdoz")
            append(" */\n\n")

            for (import in imports) {
                append("#include $import\n")
            }
            if (imports.isNotEmpty()) {
                append("\n")
            }

            append("class $className")
            append(" {\n")

            for (member in members) {
                append("    ${member.accessModifier}: ${member.type} ${member.name};\n")
            }

            // by default all functions are public
            append("public:\n")
            for (constructor in constructors) {
                append(constructor.value)
                append("\n")
            }
            for (function in functions) {
                append(function.value)
                append("\n")
            }
            for (destructor in destructors) {
                append(destructor.value)
                append("\n")
            }
            // end of class
            append("};\n")
        }
    }

    fun buildClass(): String {
        return buildString {
            append("/*\n")
            append(" *  $className.cpp\n")
            append(" *  $fileDescription\n")
            append(" *  Created by Ron June Valdoz")
            append(" */\n\n")

            append("#include  <includes/$className.h>\n\n")

            for (constructor in constructors) {
                append(constructor.value)
                append("\n")
            }
            for (function in functions) {
                append(function.value)
                append("\n")
            }
            for (destructor in destructors) {
                append(destructor.value)
                append("\n")
            }
        }
    }

    fun buildInterface(): String {
        return buildString {
            append("/*\n")
            append(" *  $className.h\n")
            append(" *  $fileDescription\n")
            append(" *  Created by Ron June Valdoz")
            append(" */\n\n")

            val header = "${className.toUpperCase()}_H"

            append("#ifndef $header\n")
            append("#define $header\n\n")

            for (import in imports) {
                append("#include $import\n")
            }
            if (imports.isNotEmpty()) {
                append("\n")
            }

            append("class $className")
            append(" {\n")

            members.groupBy { it.accessModifier }
                .forEach {
                    append("${it.key}:\n")
                    it.value.forEach { member ->
                        append("    ${member.type} ${member.name};\n")
                    }
                }

            // by default all functions are public
            append("public:\n")
            for (constructor in constructors) {
                append(constructor.key)
                append("\n")
            }
            for (function in functions) {
                append(function.key)
                append("\n")
            }
            for (destructor in destructors) {
                append(destructor.key)
                append("\n")
            }
            // end of class
            append("};\n\n")
            append("#endif // $header")
        }
    }
    companion object {
        inline fun <reified T : Any> kotlinTypeToCppType(): String {
            return when (T::class) {
                Int::class -> "int"
                else -> "void"
            }
        }
    }
}