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
        val sig = convertToJniTypeSignature(field.type.name).replace(".", "/")
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
            val variableType = componentType.simpleName
            val variableSize = field.name + "Count"
            val fieldName = field.name + "Field"
            val primitiveField = field.type.simpleName.capitalize()
            val valueObj = field.name.removeSuffix("s")
            val element = "${valueObj}Element"
            val value = when {
                componentType.isPrimitive -> "env->Get" + primitiveField + "Field($sourceObj, $fieldName)"
                componentType.isEnum -> """static_cast<$variableType>(enum_utils::getEnumFromObject(
                env, $element));"""

                else -> "${valueObj}Converter.fromObject($element);"
            }
            addImport(componentType, variableType, valueObj, converters, imports)
            val listType = field.toCType()
            buildString {
                if (componentType.simpleName.contains(
                        "Object",
                        true
                    ) || componentType.simpleName.startsWith("vk", true)
                ) {
                    append("\tstd::vector<$listType> ${field.name};")
                    appendLine()
                    append("\tauto $variableSize = env->GetArrayLength($variable);")
                    appendLine()
                    append("\tfor (int i = 0; i < $variableSize; ++i) {")
                    appendLine()
                    append("\t\tauto $element = env->GetObjectArrayElement($variable, i);")
                    appendLine()
                    append("\t\tauto value = $value; ")
                    appendLine()
                    append("\t\t${field.name}.push_back(value);")
                    appendLine()
                    append("\t\tenv->DeleteLocalRef(${element});")
                    appendLine()
                    append("\t}")
                    appendLine()
                } else {
                    append("\tstd::vector<${listType}> ${field.name};")
                    appendLine()
                    if (field.primitiveTypeIsNull()) {
                        append("\tif(${variable} != nullptr) {")
                        appendLine()
                    }
                    append("\t\tauto $variableSize = env->GetArrayLength($variable);")
                    appendLine()
                    append("\t\tenv->${field.toArrayElementType()}($variable, 0, $variableSize, reinterpret_cast<${field.toJNIType()} *>(${field.name}.data()));")
                    appendLine()
                    if (field.primitiveTypeIsNull()) {
                        append("\t}")
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
            val variableSize = fieldName.removePrefix("p")
                .replaceFirstChar { if (it.isUpperCase()) it.lowercase() else it.toString() }
                .replace("Indices", "Index")
                .removeSuffix("s") + "Count"

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
                append("\tif($variable == nullptr) {")
                appendLine()
                if (field.type.isArray) {
                    append("\t\tcreateInfo.${variableSize} = 0;")
                    appendLine()
                }
                append("\t\tcreateInfo.${fieldName} = nullptr;")
                appendLine()
                append("\t} else {")
                appendLine()
                if (field.type.isArray) {
                    append("\t$converters$arrayCount")
                    append("\t\tcreateInfo.${fieldName} = $assign")
                } else {
                    val reinterpret =
                        "$toCast<$castType>($variable); // primitive type $variableType"
                    append("\t\tcreateInfo.${fieldName} = $reinterpret")
                }
                appendLine()
                append("\t}")
                appendLine()
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
    variableType: String,
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
        imports.append("""#include "${variableType}Converter.h"""")
        imports.appendLine()
        converters.append("\t${variableType}Converter ${valueObj}Converter(env);")
        converters.appendLine()
    }
}