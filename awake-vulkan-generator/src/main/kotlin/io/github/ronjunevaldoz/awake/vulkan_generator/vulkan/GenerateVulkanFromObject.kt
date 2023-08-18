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

package io.github.ronjunevaldoz.awake.vulkan_generator.vulkan

import io.github.ronjunevaldoz.awake.vulkan_generator.tool.builder.CppClassBuilder
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.builder.CppFunctionBodyBuilder
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getVkHandle
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.isVkHandle
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.isVkPointer
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toVulkanType
import java.lang.reflect.Field

fun CppClassBuilder.generateVulkanFromObject(
    clazz: Class<*>,
    declareMembers: Array<Field>,
    hasArrayField: Boolean
) {
    val clazzInfo = "clazzInfo"
    fun CppFunctionBodyBuilder.createBody(void: Boolean = false) {
        if (!void) {
            child("${clazz.simpleName} $clazzInfo{};")
        }
        declareMembers.forEach { javaMember ->
            val functionName = "get" + javaMember.name
            val returnType: String = if (javaMember.type.isEnum) {
                javaMember.type.simpleName
            } else if (javaMember.isVkHandle()) {
                javaMember.getVkHandle().name
            } else {
                javaMember.toVulkanType()
            }

            fun generateEnum(comment: String) {
                child("$clazzInfo.${javaMember.name} = ${functionName}(); // $comment")
            }

            fun generatePrimitive(comment: String) {
                child("$clazzInfo.${javaMember.name} = ${functionName}(); // $comment")
            }


            fun generateDefault(returnType: String, comment: String) {
                if (returnType.contains("void", true)
                    || returnType.contains("char", true)
                    || returnType.startsWith("vk", true)
                ) {
                    child("${functionName}(clazzInfo); // $comment")
                } else {
                    child("$clazzInfo.${javaMember.name} = ${functionName}(); // $comment")
                }
            }

            fun generateVkHandle(comment: String) {
                child("$clazzInfo.${javaMember.name} = ${functionName}(); // $comment")
            }

            fun generatePointer(comment: String) {
                child("${functionName}(clazzInfo); // $comment")
            }

            fun processArrayData(comment: String) {
                val elementType = javaMember.type.componentType
                child("${functionName}(clazzInfo);  // ${elementType.simpleName} $comment")
            }
            if (javaMember.type.isArray) {
                processArrayData("Object Array")
            } else if (javaMember.isVkPointer()) {
                generatePointer("Pointer")
            } else if (javaMember.isVkHandle()) {
                generateVkHandle("VkHandle")
            } else if (javaMember.type.isEnum) {
                generateEnum("Enum $returnType")
            } else if (javaMember.type.isPrimitive) {
                generatePrimitive("Primitive $returnType")
            } else {
                generateDefault(returnType, "Other $returnType")
            }
        }
        if (!void) {
            child("return clazzInfo;")
        }
    }

    function(
        1,
        if (hasArrayField) "void" else clazz.simpleName,
        "fromObject",
        if (hasArrayField) listOf(Pair(clazzInfo, clazz.simpleName + "&")) else emptyList()
    ) {
        body(2) {
            createBody(void = hasArrayField)
        }
    }
}