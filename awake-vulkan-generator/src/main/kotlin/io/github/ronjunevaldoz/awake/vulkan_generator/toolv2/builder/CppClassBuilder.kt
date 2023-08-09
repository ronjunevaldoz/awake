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
import java.util.Calendar

@CppClassDSL
class CppClassBuilder(
    val className: String,
    val fileDescription: String,
    val enableSingleton: Boolean = false,
    val generateGettersSetters: Boolean = false
) {

    val members = mutableListOf<ClassMember>()
    private val constructors = mutableListOf<String>()
    private val destructors = mutableListOf<String>()
    private val imports = mutableListOf<String>()
    private val functions = mutableListOf<String>()

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
        val builder = CppConstructorBuilder(explicit, indent)
        builder.parameters(parameters)
        builder.block()
        constructors.add(builder.build(className))
    }

    fun destructor(
        indent: Int = 1,
        block: CppDestructorBuilder.() -> Unit
    ) {
        val builder = CppDestructorBuilder(indent)
        builder.block()
        destructors.add(builder.build(className))
    }

    fun function(
        indent: Int = 1,
        returnType: String = "void",
        name: String,
        parameters: List<Pair<String, String>> = emptyList(),
        block: CppFunctionBuilder.() -> Unit
    ) {
        val functionBuilder = CppFunctionBuilder(returnType, indent)
        functionBuilder.parameters(parameters)
        functionBuilder.block()
        functions.add(functionBuilder.build(name))
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
        val calendar = Calendar.getInstance()
        val formattedDateTime = calendar.time.toString()

        return buildString {
            append("/*\n")
            append(" *  $className.h\n")
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
            if (enableSingleton) {
                append(" {\n")
                append("private:\n")
                append("    static std::unique_ptr<$className> instance;\n")
                append("    $className() {\n")
                for (member in members) {
                    append("        ${member.name} = ${member.type}();\n")
                }
                append("    }\n")
                append("public:\n")
                append("    static $className& getInstance() {\n")
                append("        if (!instance) {\n")
                append("            instance.reset(new $className());\n")
                append("        }\n")
                append("        return *instance;\n")
                append("    }\n")
            } else {
                append(" {\n")
            }

            for (member in members) {
                append("    ${member.accessModifier}: ${member.type} ${member.name};\n")
            }

            // by default all functions are public
            append("public:\n")
            for (constructor in constructors) {
                append(constructor)
                append("\n")
            }
            for (function in functions) {
                append(function)
                append("\n")
            }
            for (destructor in destructors) {
                append(destructor)
                append("\n")
            }
            // end of class
            append("};\n")
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