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
import io.github.ronjunevaldoz.awake.vulkan.VkConstArray
import io.github.ronjunevaldoz.awake.vulkan.VkHandleRef
import io.github.ronjunevaldoz.awake.vulkan.VkPointer
import java.lang.reflect.Field

enum class JNIType(private val value: String) {
    JByte("jstring"),
    JChar("jchar"),
    JBoolean("jboolean"),
    JShort("jshort"),
    JInt("jint"),
    JLong("jlong"),
    JDouble("jdouble"),
    JFloat("jfloat"),
    JString("jstring"),
    JObject("jobject");

    override fun toString(): String {
        return value
    }
}

fun Field.javaTypeSuffix() = when {
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

fun Field.toVulkanType(): String {
    val isPrimitiveArray = type.isArray && type.componentType.isPrimitive
    val isArray = type.isArray && !isPrimitiveArray
    val elementType = if (isArray) type.componentType.simpleName else type.simpleName
    val simpleName = elementType.toLowerCase()

    // by default the value should all unsigned
    var prefix = "u"
    var suffix = ""

    if (name.contains("index", true)) {
        prefix = ""
    }
    if (isVkPointer()) {
        suffix = ""
    }

    val type = when {
        simpleName.contains("int") -> "${prefix}int32_t$suffix"
        simpleName.contains("long") -> "${prefix}int64_t$suffix"
        simpleName.contains("short") -> "${prefix}int16_t$suffix"
        simpleName.contains("byte") -> "${prefix}int8_t$suffix"
        simpleName.contains("double") -> "double"
        simpleName.contains("float") -> "float"
        simpleName.contains("boolean") -> "bool"
        simpleName.contains("char") -> "char"
        simpleName.contains("string") -> "const char*"
        simpleName.contains("object") -> "void*"
        isArray -> elementType
        else -> elementType //"void* sdsd"
    }
    return if (isPrimitiveArray) {
        "std::vector<${type}>"
    } else if (isArray) {
        return if (this.isVkHandle()) {
            "std::vector<${this.getVkHandle().name}>"
        } else {
            "std::vector<$type>"
        }
    } else {
        return if (this.isVkHandle()) {
            this.getVkHandle().name
        } else {
            type
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

        else -> "jobjectArray"
    }
}

fun Field.getArrayElementJavaType(): JNIType {
    val comType = type.componentType
    return when {
        comType == Int::class.javaPrimitiveType || comType.simpleName.contains(
            "Integer",
            true
        ) -> JNIType.JInt

        comType == Long::class.javaPrimitiveType || comType.simpleName.contains(
            "Long",
            true
        ) -> JNIType.JLong

        comType == Short::class.javaPrimitiveType || comType.simpleName.contains(
            "Short",
            true
        ) -> JNIType.JShort

        comType == Byte::class.javaPrimitiveType || comType.simpleName.contains(
            "Byte",
            true
        ) -> JNIType.JByte

        comType == Double::class.javaPrimitiveType || comType.simpleName.contains(
            "Double",
            true
        ) -> JNIType.JDouble

        comType == Float::class.javaPrimitiveType || comType.simpleName.contains(
            "Float",
            true
        ) -> JNIType.JFloat

        comType == Char::class.javaPrimitiveType || comType.simpleName.contains(
            "Character",
            true
        ) -> JNIType.JChar

        comType == String::class.java || comType.simpleName.contains(
            "String",
            true
        ) -> JNIType.JString

        comType == Boolean::class.javaPrimitiveType || comType.simpleName.contains(
            "Boolean",
            true
        ) -> JNIType.JBoolean

        else -> JNIType.JObject
    }
}

fun Field.toJavaType(): JNIType {
    val comType = type
    return when {
        comType == Int::class.javaPrimitiveType || comType.simpleName.contains(
            "Integer",
            true
        ) -> JNIType.JInt

        comType == Long::class.javaPrimitiveType || comType.simpleName.contains(
            "Long",
            true
        ) -> JNIType.JLong

        comType == Short::class.javaPrimitiveType || comType.simpleName.contains(
            "Short",
            true
        ) -> JNIType.JShort

        comType == Byte::class.javaPrimitiveType || comType.simpleName.contains(
            "Byte",
            true
        ) -> JNIType.JByte

        comType == Double::class.javaPrimitiveType || comType.simpleName.contains(
            "Double",
            true
        ) -> JNIType.JDouble

        comType == Float::class.javaPrimitiveType || comType.simpleName.contains(
            "Float",
            true
        ) -> JNIType.JFloat

        comType == Char::class.javaPrimitiveType || comType.simpleName.contains(
            "Character",
            true
        ) -> JNIType.JChar

        comType == String::class.java || comType.simpleName.contains(
            "String",
            true
        ) -> JNIType.JString

        comType == Boolean::class.javaPrimitiveType || comType.simpleName.contains(
            "Boolean",
            true
        ) -> JNIType.JBoolean

        else -> JNIType.JObject
    }
}

fun Field.getJavaValue(env: String = "env", obj: String, fieldID: String): String {
    val comType = type
    val objParam = obj //"\"$obj\""
    val fieldIdParam = fieldID //"\"$fieldID\""
    val type = when {
        comType == Int::class.javaPrimitiveType || comType.simpleName.contains(
            "Integer",
            true
        ) -> "Int"

        comType == Long::class.javaPrimitiveType || comType.simpleName.contains(
            "Long",
            true
        ) -> "Long"

        comType == Short::class.javaPrimitiveType || comType.simpleName.contains(
            "Short",
            true
        ) -> "Short"

        comType == Byte::class.javaPrimitiveType || comType.simpleName.contains(
            "Byte",
            true
        ) -> "Byte"

        comType == Double::class.javaPrimitiveType || comType.simpleName.contains(
            "Double",
            true
        ) -> "Double"

        comType == Float::class.javaPrimitiveType || comType.simpleName.contains(
            "Float",
            true
        ) -> "Float"

        comType == Char::class.javaPrimitiveType || comType.simpleName.contains(
            "Character",
            true
        ) -> "Char"

        comType == String::class.java || comType.simpleName.contains("String", true)
        -> "Object"

        comType == Boolean::class.javaPrimitiveType || comType.simpleName.contains(
            "Boolean",
            true
        ) -> "Boolean"

        else -> "Object"
    }
    if (comType.isArray) {
        return "$env->GetObjectField($objParam, $fieldIdParam)"
    }
    return "$env->Get${type}Field($objParam, $fieldIdParam)"
}

fun Field.setJavaValue(env: String = "env", obj: String, fieldID: String, value: String): String {
    val comType = type
    val objParam = obj //"\"$obj\""
    val fieldIdParam = fieldID //"\"$fieldID\""
    val type = when {
        comType == Int::class.javaPrimitiveType || comType.simpleName.contains(
            "Integer",
            true
        ) -> "Int"

        comType == Long::class.javaPrimitiveType || comType.simpleName.contains(
            "Long",
            true
        ) -> "Long"

        comType == Short::class.javaPrimitiveType || comType.simpleName.contains(
            "Short",
            true
        ) -> "Short"

        comType == Byte::class.javaPrimitiveType || comType.simpleName.contains(
            "Byte",
            true
        ) -> "Byte"

        comType == Double::class.javaPrimitiveType || comType.simpleName.contains(
            "Double",
            true
        ) -> "Double"

        comType == Float::class.javaPrimitiveType || comType.simpleName.contains(
            "Float",
            true
        ) -> "Float"

        comType == Char::class.javaPrimitiveType || comType.simpleName.contains(
            "Character",
            true
        ) -> "Char"

        comType == String::class.java || comType.simpleName.contains("String", true)
        -> "Object"

        comType == Boolean::class.javaPrimitiveType || comType.simpleName.contains(
            "Boolean",
            true
        ) -> "Boolean"

        else -> "Object"
    }
    if (comType.isArray) {
        return "$env->SetObjectField($objParam, $fieldIdParam, $value)"
    }
    return "$env->Set${type}Field($objParam, $fieldIdParam, $value)"
}

fun Field.getArrayElement(list: String, index: String): String {
    return when (type.componentType) {
        String::class.javaPrimitiveType, java.lang.String::class.java -> "GetObjectArrayElement($list, $index); // actual type is ${type.simpleName}"
        Object::class.javaPrimitiveType, java.lang.Object::class.java -> "GetObjectArrayElement($list, $index); // actual type is ${type.simpleName}"
        else -> {
            if (type.simpleName.startsWith("vk", true)) {
                "GetObjectArrayElement($list, $index); // actual type is ${type.simpleName}"
            } else {
                throw RuntimeException("getArrayElement not supported (use getArrayRegion instead) ${type.simpleName}")
            }
        }
    }
}

fun Field.getArrayRegion(
    list: String,
    index: String,
    size: String = "1",
    outElement: String
): String {
    val arrayRegionConstructor = "($list, $index, $size, $outElement);"
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
        if (annotationVkArray.sizeAlias.isNotEmpty()) {
            return true
        }
    }
    return false
}

fun Field.onVkArray(alias: (sizeSuffix: String, listType: String, stride: String) -> Unit) {
    var sizeSuffix = "Count"
    var listType = toVulkanType()
    var stride = ""
    if (isAnnotationPresent(VkArray::class.java)) {
        val annotationVkArray = getDeclaredAnnotation(VkArray::class.java)
        sizeSuffix = annotationVkArray.sizeAlias

        if (annotationVkArray.elementCast.simpleName == UInt::class.java.simpleName) {
            listType = "uint32_t"
        }
        if (annotationVkArray.stride.simpleName == UInt::class.java.simpleName) {
            stride = "sizeof(uint32_t)"
        }
    }
    alias(sizeSuffix, listType, stride)
}


fun Field.toJavaSignature(): String {
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


// vulkan extensions

fun Field.isVkHandle(): Boolean {
//    val isVkHandle = kotlinProperty!!.returnType.classifier == VkHandle::class
    if (isAnnotationPresent(VkHandleRef::class.java)) {
        return true
    }
    return false
}

fun Field.getVkHandle(): VkHandleRef {
    return getDeclaredAnnotation(VkHandleRef::class.java)
}

fun Field.isVkPointer(): Boolean {
    if (isAnnotationPresent(VkPointer::class.java)) {
        return true
    }
    return false
}

fun Field.isVkConstArray(): Boolean {
    if (isAnnotationPresent(VkConstArray::class.java)) {
        return true
    }
    return false
}

fun Field.getVkArray(): VkArray? {
    if (isAnnotationPresent(VkArray::class.java)) {
        return getDeclaredAnnotation(VkArray::class.java)
    }
    return null
}