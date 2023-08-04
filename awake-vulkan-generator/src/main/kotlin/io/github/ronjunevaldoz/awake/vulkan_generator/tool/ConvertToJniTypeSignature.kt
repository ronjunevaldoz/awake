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

fun convertToJniTypeSignature(javaTypeName: String): String {
    return when (javaTypeName) {
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
                "[" + convertToJniTypeSignature(javaTypeName.substring(1))
            } else if (javaTypeName.startsWith("L") && javaTypeName.endsWith(";")) {
                // Object types
                "L" + javaTypeName.substring(1, javaTypeName.length - 1) + ";"
            } else {
                "L$javaTypeName;"
            }
        }
    }
}