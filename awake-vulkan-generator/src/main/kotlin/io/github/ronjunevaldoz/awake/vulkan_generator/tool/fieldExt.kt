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
        type.simpleName.contains("float", true) -> "float"
        type.simpleName.contains("object", true) -> "void*"
        type.simpleName.contains("string", true) -> "const char*"
        else -> {
            type.simpleName.replace("[]", "")
        }
    }
}

fun Field.toJavaTypeArray(): String {
    val comType = type.componentType
    return when {
        comType == Int::class.javaPrimitiveType || comType.simpleName.contains(
            "Integer",
            true
        ) -> "jintArray"

        comType == Long::class.javaPrimitiveType || comType.simpleName.contains(
            "Long",
            true
        ) -> "jlongArray"

        comType == Short::class.javaPrimitiveType || comType.simpleName.contains(
            "Short",
            true
        ) -> "jshortArray"

        comType == Byte::class.javaPrimitiveType || comType.simpleName.contains(
            "Byte",
            true
        ) -> "jbyteArray"

        comType == Double::class.javaPrimitiveType || comType.simpleName.contains(
            "Double",
            true
        ) -> "jdoubleArray"

        comType == Float::class.javaPrimitiveType || comType.simpleName.contains(
            "Float",
            true
        ) -> "jfloatArray"

        comType == Char::class.javaPrimitiveType || comType == String::class.java || comType.simpleName.contains(
            "Char",
            true
        ) || comType.simpleName.contains("String", true) -> "jobjectArray"

        comType == Boolean::class.javaPrimitiveType || comType.simpleName.contains(
            "Boolean",
            true
        ) -> "jbooleanArray"

        else -> type.simpleName + "Array"
    }
}

fun Field.toJavaType(): String {
    val comType = type
    return when {
        comType == Int::class.javaPrimitiveType || comType.simpleName.contains(
            "Integer",
            true
        ) -> "jint"

        comType == Long::class.javaPrimitiveType || comType.simpleName.contains(
            "Long",
            true
        ) -> "jlong"

        comType == Short::class.javaPrimitiveType || comType.simpleName.contains(
            "Short",
            true
        ) -> "jshort"

        comType == Byte::class.javaPrimitiveType || comType.simpleName.contains(
            "Byte",
            true
        ) -> "jbyte"

        comType == Double::class.javaPrimitiveType || comType.simpleName.contains(
            "Double",
            true
        ) -> "jdouble"

        comType == Float::class.javaPrimitiveType || comType.simpleName.contains(
            "Float",
            true
        ) -> "jfloat"

        comType == Char::class.javaPrimitiveType || comType.simpleName.contains(
            "Character",
            true
        ) -> "jchar"

        comType == String::class.java || comType.simpleName.contains("String", true) -> "jstring"
        comType == Boolean::class.javaPrimitiveType || comType.simpleName.contains(
            "Boolean",
            true
        ) -> "jboolean"

        else -> type.simpleName.replace("[]", "")
    }
}

fun Field.getArrayElement(list: String, index: String): String {
    return when (type.componentType) {
        String::class.javaPrimitiveType, java.lang.String::class.java -> "GetObjectArrayElement($list, $index); // actual type is ${type.simpleName}"
        Object::class.javaPrimitiveType, java.lang.Object::class.java -> "GetObjectArrayElement($list, $index); // actual type is ${type.simpleName}"
        else -> {
            if (type.simpleName.startsWith("vk", true)) {
                "GetObjectArrayElement($list, $index); // actual type is ${type.simpleName}"
            } else {
                throw RuntimeException("getArrayElement not supported ${type.simpleName}")
            }
        }
    }
}

fun Field.getArrayRegion(list: String, index: String, outElement: String): String {
    val arrayRegionConstructor = "($list, $index, 1, $outElement);"
    return when (type.componentType) {
        Int::class.javaPrimitiveType, Integer::class.java -> "GetIntArrayRegion$arrayRegionConstructor"
        Long::class.javaPrimitiveType, java.lang.Long::class.java -> "GetLongArrayRegion$arrayRegionConstructor"
        Short::class.javaPrimitiveType, java.lang.Short::class.java -> "GetShortArrayRegion$arrayRegionConstructor"
        Byte::class.javaPrimitiveType, java.lang.Byte::class.java -> "GetByteArrayRegion$arrayRegionConstructor"
        Double::class.javaPrimitiveType, java.lang.Double::class.java -> "GetDoubleArrayRegion$arrayRegionConstructor"
        Float::class.javaPrimitiveType, java.lang.Float::class.java -> "GetFloatArrayRegion$arrayRegionConstructor"
        Char::class.javaPrimitiveType, java.lang.Character::class.java -> "GetCharArrayRegion$arrayRegionConstructor"
        Boolean::class.javaPrimitiveType, java.lang.Boolean::class.java -> "GetBooleanArrayRegion$arrayRegionConstructor"
//        String::class.javaPrimitiveType, java.lang.String::class.java -> "GetObjectArrayElement($list, $index); // actual type is ${type.simpleName}"
//        Object::class.javaPrimitiveType, java.lang.Object::class.java -> "GetObjectArrayElement($list, $index); // actual type is ${type.simpleName}"
        else -> {
//            if(type.simpleName.startsWith("vk", true)) {
//                "GetObjectArrayElement($list, $index); // generated from Field.getArrayRegion"
//            } else {
            throw RuntimeException("getArrayRegion not supported ${type.simpleName}")
//            }
        }
    }
}

fun Field.canGenerateArraySize(): Boolean {
    if (isAnnotationPresent(VkArray::class.java)) {
        val annotationVkArray = getDeclaredAnnotation(VkArray::class.java)
        if (annotationVkArray.sizeSuffix.isNotEmpty()) {
            return true
        }
    }
    return false
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