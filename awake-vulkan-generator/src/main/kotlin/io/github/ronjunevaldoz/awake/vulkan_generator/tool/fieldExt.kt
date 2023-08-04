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
        type.simpleName.contains("short", true) -> "NOSURE SHORT"
        type.simpleName.contains("byte", true) -> "NOSURE BYTE"
        type.simpleName.contains("double", true) -> "NOSURE DOUBLE"
        type.simpleName.contains("float", true) -> "VkBool32"
        else -> type.simpleName.replace("[]", "")
    }
}

fun Field.toJNIType(): String {
    val comType = type.componentType
    return when {
        comType.simpleName.contains("Integer", true) -> "jint"
        comType.simpleName.contains("Long", true) -> "jlong"
        comType.simpleName.contains("Short", true) -> "jshort"
        comType.simpleName.contains("Byte", true) -> "jbyte"
        comType.simpleName.contains("Double", true) -> "jdouble"
        comType.simpleName.contains("Float", true) -> "jfloat"
        else -> type.simpleName
    }
}

fun Field.toArrayElementType(): String {
    val comType = type.componentType
    return when {
        comType.simpleName.contains("Integer", true) -> "GetIntArrayRegion"
        comType.simpleName.contains("Long", true) -> "GetLongArrayRegion"
        comType.simpleName.contains("Short", true) -> "GetShortArrayRegion"
        comType.simpleName.contains("Byte", true) -> "GetByteArrayRegion"
        comType.simpleName.contains("Double", true) -> "GetDoubleArrayRegion"
        comType.simpleName.contains("Float", true) -> "GetFloatArrayRegion"
        else -> type.simpleName
    }
}
