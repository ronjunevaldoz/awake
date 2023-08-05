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

import io.github.ronjunevaldoz.awake.vulkan.VkHandleRef
import io.github.ronjunevaldoz.awake.vulkan.VkPointer
import java.lang.reflect.Field
import java.util.Calendar


inline fun <reified T> generateCpp() {
    val clazz = T::class.java
    val projectName = "awake"
    val sourceObj = "pCreateInfo"
    val date = Calendar.getInstance().time
    val className = clazz.simpleName + "Converter"
    val definition = projectName.toUpperCase() + "_" + className.toUpperCase()
    val classSig = clazz.name.replace(".", "/")
    val declaredFields = clazz.declaredFields
    val imports = StringBuilder()
    val converters = StringBuilder()
    val declareFields = declaredFields.declareFieldIds()
    val initFields = declaredFields.initFieldIds("clazz")
    val clearFields = declaredFields.clearFields()
    val accessFields = declaredFields.accessFields(sourceObj)
    val deleteLocalReferences = declaredFields.deleteLocalReference()
    val processArrayFields = declaredFields.processArrayFields(sourceObj, converters, imports)
    val assignValues = declaredFields.assignValues(imports)
    val header =
        headerTemplate(className, clazz.simpleName, date.toString(), definition, declareFields)
    val cpp = cppTemplate(
        className,
        clazz.simpleName,
        classSig,
        date.toString(),
        converters.toString(),
        imports.toString(),
        sourceObj,
        initFields,
        accessFields,
        processArrayFields,
        assignValues,
        deleteLocalReferences,
        clearFields
    )
    val awakeVulkanCpp = "awake-vulkan/src/main/cpp/common/utils/"
    FileWriter.writeFile("$awakeVulkanCpp$className.h", header)
    FileWriter.writeFile("$awakeVulkanCpp$className.cpp", cpp)
}

fun Array<Field>.declareFieldIds(type: String = "jfieldID", suffix: String = "Field") =
    joinToString("\n") {
        "\t$type ${it.name}$suffix;"
    }

fun Array<Field>.initFieldIds(className: String = "clazz", suffix: String = "Field") =
    joinToString("\n") { field ->
        val sig = field.toSig()
        val fieldName = field.name + suffix
        """${"\t"}$fieldName = env->GetFieldID($className, "${field.name}", "$sig");"""
    }

fun Array<Field>.clearFields(suffix: String = "Field") = joinToString("\n") { field ->
    val fieldName = field.name + suffix
    "\t$fieldName = nullptr;"
}

fun Array<Field>.accessFields(sourceObj: String, suffix: String = "Field") =
    joinToString("\n") { field ->
        val varSuffix = field.varSuffix()
        val fieldName = field.name + suffix
        val primitiveField = field.type.simpleName.capitalize()

        val access = when {
            field.type.isPrimitive -> "env->Get" + primitiveField + "Field($sourceObj, $fieldName)"
            field.type.isEnum -> "env->GetObjectField($sourceObj,$fieldName)"
            field.type.isArray -> {
                if (field.type.componentType.simpleName.contains(
                        "Object",
                        true
                    ) || field.type.componentType.simpleName.startsWith("vk", true)
                ) {
                    "(jobjectArray) env->GetObjectField($sourceObj, $fieldName)"
                } else {
                    "(${field.toJNIType()}Array) env->GetObjectField($sourceObj, $fieldName)"
                }
            }

            else -> "env->GetObjectField($sourceObj, $fieldName)"
        }
        "\tauto ${field.name}$varSuffix = $access;"
    }

fun Array<Field>.deleteLocalReference() =
    filterNot { it.type.isPrimitive } // take only non-primitive (enum, object or an array)
        .joinToString("\n") { field ->
            val varSuffix = field.varSuffix()
            if (!field.type.isPrimitive) {
                "\tenv->DeleteLocalRef(" + field.name + varSuffix + ");"
            } else {
                ""
            }
        }

fun Array<Field>.processArrayFields(
    sourceObj: String,
    converters: StringBuilder,
    imports: StringBuilder
) =
    filter { it.type.isArray } // take only array
        .joinToString("\n") { field ->
            val suffix = field.varSuffix()
            val componentType = field.type.componentType
            val variable = field.name + suffix
            val elementType = componentType.simpleName
            var variableSize = field.name
            var listType = field.toCType()
            field.onVkArray { sizeSuffix, varListType ->
                variableSize += sizeSuffix
                listType = varListType
            }
            val fieldName = field.name + "Field"
            val primitiveField = field.type.simpleName.capitalize()
            val valueObj = field.name.removeSuffix("s")
            val element = "${valueObj}Element"
            val value = when {
                componentType.isPrimitive -> "env->Get" + primitiveField + "Field($sourceObj, $fieldName)"
                componentType.isEnum -> """static_cast<$elementType>(enum_utils::getEnumFromObject(
                env, $element));"""

                else -> "${valueObj}Converter.fromObject($element);"
            }
            addImport(componentType, valueObj, converters, imports)
            buildString {
                append("\tstd::vector<$listType> ${field.name};")
                appendLine()
                appendCondition(1, "$variable != nullptr") { indent ->
                    if (componentType.simpleName.contains(
                            "Object",
                            true
                        ) || componentType.simpleName.startsWith("vk", true)
                    ) {
                        append("${indent}auto $variableSize = env->GetArrayLength($variable);")
                        appendLine()
                        appendForLoop(2, 0, variableSize) { index ->
                            append("${indent}\tauto $element = env->GetObjectArrayElement($variable, $index);")
                            appendLine()
                            if (listType != "void*") {
                                append("${indent}\tauto value = $value; ")
                                appendLine()
                                append("${indent}\t${field.name}.push_back(value);")
                                appendLine()
                            } else {
                                append("${indent}\t${field.name}.push_back($element);")
                                appendLine()
                            }
                            append("${indent}\tenv->DeleteLocalRef(${element});")
                            appendLine()
                        }
                    } else {
                        append("${indent}${field.toJNIType()} element;")
                        appendLine()
                        append("${indent}env->${field.toArrayElementType()}($variable, 0, 1, &element);")
                        appendLine()
                        append("${indent}${field.name}.push_back(element);")
                        appendLine()
                    }
                }
            }
        }

fun Array<Field>.assignValues(imports: StringBuilder): String {
    return buildString {
        joinToString("\n") { field ->
            val suffix = field.varSuffix()
            val fieldName = field.name
            val variable = fieldName + suffix
            val variableType = field.type.simpleName
            var variableSize = fieldName.removePrefix("p")
                .replaceFirstChar { if (it.isUpperCase()) it.lowercase() else it.toString() }
                .replace("Indices", "Index")
                .removeSuffix("s")

            field.onVkArray { sizeSuffix, varListType ->
                variableSize += sizeSuffix
            }

            val arrayCount = if (field.type.isArray) {
                "\tcreateInfo.${variableSize} = static_cast<uint32_t>(${fieldName}.size());\n"
            } else ""
            var converters = ""
            var toCast = "static_cast" // either to static_cast or reinterpret
            val castType = if (variableType.contains("int", true)) {
                if (fieldName.contains("index", true)) {
                    "int32_t"
                } else {
                    "uint32_t"
                }
            } else if (variableType.contains("long", true)) {
                if (field.isAnnotationPresent(VkHandleRef::class.java)) {
                    toCast = "reinterpret_cast"
                    field.getDeclaredAnnotation(VkHandleRef::class.java).name
                } else {
                    "uint64_t"
                }
            } else if (variableType.contains("boolean", true)) {
                "VkBool32"
            } else {
                "j$variableType"
            }
            val assign = when {
                field.type.isPrimitive -> "$toCast<$castType>($variable); // primitive type $variableType"
                field.type.isEnum -> "$toCast<$variableType>(enum_utils::getEnumFromObject(env, $variable));"
                field.type.isArray -> "${fieldName}.data();"
                else -> {
                    val suffixInfo = "CreateInfo" // TODO get from last 2 words
                    converters = if (variableType != "Object") "" +
                            "\t$variableType ${fieldName}$suffixInfo;\n" +
                            "${fieldName}$suffixInfo = ${variableType}Converter(env).fromObject($variable);\n" +
                            "" else ""

                    addImport(field, variableType, imports)
                    val isPointer =
                        if (field.isAnnotationPresent(VkPointer::class.java)) "&" else ""
                    if (variableType == "Object") "$toCast<void *>($variable);" else "$isPointer${fieldName}$suffixInfo;"
                }
            }
            if (field.primitiveTypeIsNull()) {
                // add null checking then assign
                appendCondition(1, condition = "$variable == nullptr",
                    `if` = { tab ->
                        if (field.type.isArray) {
                            append("${tab}createInfo.${variableSize} = 0;")
                            appendLine()
                        }
                        append("${tab}createInfo.${fieldName} = nullptr;")
                        appendLine()
                    }, `else` = { tab ->
                        if (field.type.isArray) {
                            append("\t$converters$arrayCount")
                            append("${tab}createInfo.${fieldName} = $assign")
                        } else {
                            val reinterpret =
                                "$toCast<$castType>($variable); // primitive type $variableType"
                            append("${tab}createInfo.${fieldName} = $reinterpret")
                        }
                        appendLine()
                    }
                )
            } else {
                append("$converters$arrayCount")
                append("\tcreateInfo.${fieldName} = $assign")
                appendLine()
            }
        }
    }
}

private fun addImport(field: Field, variableType: String, imports: StringBuilder) {
    if (
        !field.type.isEnum &&
        field.type.typeName.contains("vk", true)
    ) {
        imports.append("#include " + """"${variableType}Converter.h"""")
        imports.appendLine()
    }
}

private fun addImport(
    componentType: Class<*>,
    valueObj: String,
    converters: StringBuilder,
    imports: StringBuilder
) {
    if (
        !componentType.isEnum &&
        (componentType.typeName.contains(
            "Object",
            true
        ) || componentType.simpleName.startsWith("vk", true))
    ) {
        if (componentType.simpleName == "Object") {
            // no converter available for Object
            println("no converter available for Object")
            converters.append("\t// no converter available for Object")
            converters.appendLine()
            converters.append("\t// ${componentType.simpleName}Converter ${valueObj}Converter(env);")
        } else {
            imports.append("""#include "${componentType.simpleName}Converter.h"""")
            imports.appendLine()
            converters.append("\t${componentType.simpleName}Converter ${valueObj}Converter(env);")
        }
    }
}

fun StringBuilder.appendCondition(
    tabSize: Int = 1,
    condition: String,
    `if`: StringBuilder.(indent: String) -> Unit,
    `else`: StringBuilder.(indent: String) -> Unit
): StringBuilder {
    val tab = "\t".repeat(tabSize)
    append("${tab}if($condition) {")
    appendLine()
    `if`("${tab}\t")
    append("${tab}} else {")
    appendLine()
    `else`("${tab}\t")
    append("${tab}}")
    appendLine()
    return this
}

fun StringBuilder.appendCondition(
    tabSize: Int = 1,
    condition: String,
    `if`: StringBuilder.(indent: String) -> Unit
): StringBuilder {
    val tab = "\t".repeat(tabSize)
    append("${tab}if($condition) {")
    appendLine()
    `if`("$tab\t")
    append("$tab}")
    appendLine()
    return this
}

fun StringBuilder.appendForLoop(
    tabSize: Int = 1,
    start: Int = 0,
    size: String,
    loop: StringBuilder.(index: String) -> Unit
): StringBuilder {
    val tab = "\t".repeat(tabSize)
    append("${tab}for (int i = $start; i < $size; ++i) {")
    appendLine()
    loop("i")
    append("${tab}}")
    appendLine()
    return this
}