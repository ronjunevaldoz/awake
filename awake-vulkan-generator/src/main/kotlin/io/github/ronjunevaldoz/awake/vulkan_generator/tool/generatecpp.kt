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
    val declareFields = declaredFields.declareFieldIds()
    val initFields = declaredFields.initFieldIds("clazz")
    val clearFields = declaredFields.clearFields()
    val accessFields = declaredFields.accessFields(sourceObj)
    val deleteLocalReferences = declaredFields.deleteLocalReference()
    val processArrayFields = declaredFields.processArrayFields(sourceObj, imports)
    val assignValues = declaredFields.assignValues(imports)
    val header =
        headerTemplate(className, clazz.simpleName, date.toString(), definition, declareFields)
    val cpp = cppTemplate(
        className,
        clazz.simpleName,
        classSig,
        date.toString(),
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
    writeFile("$awakeVulkanCpp$className.h", header)
    writeFile("$awakeVulkanCpp$className.cpp", cpp)
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

fun Field.varSuffix() = when {
    type.isPrimitive -> type.simpleName.capitalize()
    type.isEnum -> "Enum"
    type.isArray -> "Array"
    else -> "Obj"
}

fun Array<Field>.accessFields(sourceObj: String, suffix: String = "Field") =
    joinToString("\n") { field ->
        val varSuffix = field.varSuffix()
        val fieldName = field.name + suffix
        val primitiveField = field.type.simpleName.capitalize()
        val access = when {
            field.type.isPrimitive -> "env->Get" + primitiveField + "Field($sourceObj, $fieldName)"
            field.type.isEnum -> "env->GetObjectField($sourceObj,$fieldName)"
            field.type.isArray -> "(jobjectArray) env->GetObjectField($sourceObj, $fieldName)"
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

fun Array<Field>.processArrayFields(sourceObj: String, imports: StringBuilder) =
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
            var declareConverter = ""
            if (!componentType.isEnum) {
                imports.append("""#include  "${variableType}Converter.h"""")
                imports.appendLine()
                declareConverter = "${variableType}Converter ${valueObj}Converter(env);\n"
            }
            """ 
$declareConverter
std::vector<$variableType> ${field.name};
auto $variableSize = env->GetArrayLength($variable);
for (int i = 0; i < $variableSize; ++i) {
    auto $element = env->GetObjectArrayElement($variable, i);
    auto value = $value; 
    ${field.name}.push_back(value);
    env->DeleteLocalRef(${element});
}
        """.trimIndent()
        }

fun Array<Field>.assignValues(imports: StringBuilder) = joinToString("\n") { field ->
    val suffix = field.varSuffix()
    val fieldName = field.name
    val variable = fieldName + suffix
    val variableType = field.type.simpleName

    val arrayCount = if (field.type.isArray) {
        val variableSize = fieldName.removePrefix("p")
            .replaceFirstChar { if (it.isUpperCase()) it.lowercase() else it.toString() }
            .removeSuffix("s") + "Count"
        "\tcreateInfo.$variableSize = static_cast<uint32_t>(${fieldName}.size());\n"
    } else ""
    var converters = ""
    val castType = if (variableType.contains("int", true)) {
        if (fieldName.contains("index", true)) {
            "int32_t"
        } else {
            "uint32_t"
        }
    } else if (variableType.contains("long", true)) {
        "uint64_t"
    } else {
        ""
    }
    val assign = when {
        field.type.isPrimitive -> "static_cast<$castType>($variable); // primitive type $variableType"
        field.type.isEnum -> "static_cast<$variableType>(enum_utils::getEnumFromObject(env, $variable));"
        field.type.isArray -> "${fieldName}.data();"
        else -> {
            val suffixInfo = "CreateInfo" // TODO get from last 2 words
            converters = if (variableType != "Object") "" +
                    "$variableType ${fieldName}$suffixInfo;\n" +
                    "${fieldName}$suffixInfo = ${variableType}Converter(env).fromObject($variable);\n" +
                    "" else ""
            if (variableType != "Object") {
                imports.append("#include " + """"${variableType}Converter.h"""")
                imports.appendLine()
            }
            if (variableType == "Object") "static_cast<void *>($variable);" else "&${fieldName}$suffixInfo;"
        }
    }
    "$converters$arrayCount\tcreateInfo.${fieldName} = $assign"
}