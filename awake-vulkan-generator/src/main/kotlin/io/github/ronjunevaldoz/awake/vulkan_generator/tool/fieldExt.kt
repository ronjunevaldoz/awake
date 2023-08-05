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

import io.github.ronjunevaldoz.awake.vulkan.VkArray
import java.lang.reflect.Field


fun Field.varSuffix() = when {
    type.isPrimitive -> type.simpleName.capitalize()
    type.isEnum -> "Enum"
    type.isArray -> "Array"
    else -> "Obj"
}

fun Field.primitiveTypeIsNull(): Boolean {
    // when a primitive become null, the value of isPrimitive became false
    return !type.isPrimitive &&
            (type.simpleName.contains("int", true) ||
                    type.simpleName.contains("long", true) ||
                    type.simpleName.contains("short", true) ||
                    type.simpleName.contains("byte", true) ||
                    type.simpleName.contains("double", true) ||
                    type.simpleName.contains("float", true))
}

fun Field.toCType(): String {
    return when {
        type.simpleName.contains("int", true) -> "uint32_t"
        type.simpleName.contains("long", true) -> "uint64_t"
        type.simpleName.contains("short", true) -> "uint16_t"
        type.simpleName.contains("byte", true) -> "uint8_t"
        type.simpleName.contains("double", true) -> "NOSURE DOUBLE"
        type.simpleName.contains("float", true) -> "VkBool32"
        type.simpleName.contains("object", true) -> "void*"
        else -> {
            type.simpleName.replace("[]", "")
        }
    }
}

fun Field.toJNIType(): String {
    val comType = type.componentType
    return when {
        comType == Int::class.javaPrimitiveType -> "jint"
        comType == Long::class.javaPrimitiveType -> "jlong"
        comType == Short::class.javaPrimitiveType -> "jshort"
        comType == Byte::class.javaPrimitiveType -> "jbyte"
        comType == Double::class.javaPrimitiveType -> "jdouble"
        comType == Float::class.javaPrimitiveType -> "jfloat"
        comType == Char::class.javaPrimitiveType -> "jchar"
        comType == Boolean::class.javaPrimitiveType -> "jboolean"
        comType.simpleName.contains("Integer", true) -> "jint"
        comType.simpleName.contains("Long", true) -> "jlong"
        comType.simpleName.contains("Short", true) -> "jshort"
        comType.simpleName.contains("Byte", true) -> "jbyte"
        comType.simpleName.contains("Double", true) -> "jdouble"
        comType.simpleName.contains("Float", true) -> "jfloat"
        comType.simpleName.contains("Char", true) -> "jchar"
        comType.simpleName.contains("Boolearn", true) -> "jboolean"
        else -> type.simpleName
    }
}

fun Field.toArrayElementType(): String {
    val comType = type.componentType
    return when {
        comType == Int::class.javaPrimitiveType -> "GetIntArrayRegion"
        comType == Long::class.javaPrimitiveType -> "GetLongArrayRegion"
        comType == Short::class.javaPrimitiveType -> "GetShortArrayRegion"
        comType == Byte::class.javaPrimitiveType -> "GetByteArrayRegion"
        comType == Double::class.javaPrimitiveType -> "GetDoubleArrayRegion"
        comType == Float::class.javaPrimitiveType -> "GetFloatArrayRegion"
        comType == Char::class.javaPrimitiveType -> "GetCharArrayRegion"
        comType == Boolean::class.javaPrimitiveType -> "GetBooleanArrayRegion"
        comType.simpleName.contains("Integer", true) -> "GetIntArrayRegion"
        comType.simpleName.contains("Long", true) -> "GetLongArrayRegion"
        comType.simpleName.contains("Short", true) -> "GetShortArrayRegion"
        comType.simpleName.contains("Byte", true) -> "GetByteArrayRegion"
        comType.simpleName.contains("Double", true) -> "GetDoubleArrayRegion"
        comType.simpleName.contains("Float", true) -> "GetFloatArrayRegion"
        comType.simpleName.contains("Char", true) -> "GetCharArrayRegion"
        comType.simpleName.contains("Boolean", true) -> "GetBooleanArrayRegion"
        else -> type.simpleName
    }
}

fun Field.onVkArray(alias: (sizeSuffix: String, listType: String, stride: String) -> Unit) {
    var sizeSuffix = "Count"
    var listType = toCType()
    var stride = ""
    if (isAnnotationPresent(VkArray::class.java)) {
        val annotationVkArray = getDeclaredAnnotation(VkArray::class.java)
        sizeSuffix = annotationVkArray.sizeSuffix

        if (annotationVkArray.elementCast.simpleName == UInt::class.java.simpleName) {
            listType = "uint32_t"
        }
        if (annotationVkArray.stride.simpleName == UInt::class.java.simpleName) {
            stride = "sizeof(uint32_t)"
        }
    }
    alias(sizeSuffix, listType, stride)
}


fun Field.toSig(): String {
    return when (val javaTypeName = type.name) {
        "boolean" -> "Z"
        "byte" -> "B"
        "char" -> "C"
        "short" -> "S"
        "int" -> "I"
        "long" -> "J"
        "float" -> "F"
        "double" -> "D"
        "void" -> "V"
        else -> {
            if (javaTypeName.startsWith("[")) {
                // Array types
                javaTypeName
            } else if (javaTypeName.startsWith("L") && javaTypeName.endsWith(";")) {
                // Object types
                "L" + javaTypeName.substring(1, javaTypeName.length - 1) + ";"
            } else {
                "L$javaTypeName;"
            }
        }
    }.replace(".", "/")
}