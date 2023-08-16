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

import io.github.ronjunevaldoz.awake.vulkan.VkMutator
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.FileWriter
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.JNIType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.cast
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.cppClass
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getArrayElementJavaType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getVkConstArray
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.setArrayRegion
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.setJavaValue
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toJavaSignature
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toJavaType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toJavaTypeArray

fun createVulkanMutator(clazz: Class<*>) {
    if (!clazz.isAnnotationPresent(VkMutator::class.java)) {
        return
    }
    val declareMembers = clazz.declaredFields
    val cppClassCode =
        cppClass(clazz.simpleName + "Mutator", "Vulkan mutator for ${clazz.simpleName}") {
            import("<jni.h>")
            import("<vulkan/vulkan.h>")
            import("<string>")
            import("<vector>")
            import("<enum_utils.h>")

            member("private", "JNIEnv*", "env")
            member("private", "jclass", "clazz")
            declareMembers.forEach { member ->
                member("private", "jfieldID", member.name + "Field")
            }

            destructor {
                // default destructor
                body(2) {
                    child("// env->DeleteGlobalRef(clazz);")
                }
            }

            constructor(
                true,
                1, listOf(
                    Pair("env", "JNIEnv*"),
                )
            ) {
                body(2) {
                    child("this->env = env;")
                    members.forEach { member ->
                        if (member.type == "jfieldID") {
                            val javaField =
                                declareMembers.find { it.name + "Field" == member.name }!!
                            val javaSig = "\"${javaField.toJavaSignature()}\""
                            val sourceClass = "clazz"
                            val fieldName = "\"${javaField.name}\""
                            child("${member.name} = env->GetFieldID($sourceClass, $fieldName, $javaSig);")
                        } else if (member.type == "jclass") {
                            val javaClassSig = "\"${clazz.name.replace(".", "/")}\""
                            child("${member.name} = env->FindClass($javaClassSig);")
                        }
                    }
                }
            }

            function(
                1, "jobject", "toObject",
                listOf(Pair("source", clazz.simpleName))
            ) {
                body(2) {
                    // return clazz info
                    child("auto constructor = env->GetMethodID(clazz, \"<init>\", \"()V\");")
                    child("auto newObj = env->NewObject(clazz, constructor);")
                    declareMembers.forEach { javaMember ->
                        val field = javaMember.name + "Field"
                        val functionName = javaMember.cast("source." + javaMember.name)

                        if (javaMember.type.isArray && javaMember.type.componentType.isPrimitive) {

                            val arraySize =
                                javaMember.getVkConstArray()?.arraySize ?: "<NO ARRAY SIZE>"
                            val buffer =
                                "reinterpret_cast<${javaMember.getArrayElementJavaType()} *>(source.${javaMember.name} )"
                            child("${javaMember.toJavaTypeArray()}  ${javaMember.name} = env->New${javaMember.type.componentType.simpleName.capitalize()}Array($arraySize);")
                            child(
                                "env->" + javaMember.setArrayRegion(
                                    javaMember.name,
                                    "0",
                                    arraySize,
                                    buffer
                                )
                            )
                            child("env->SetObjectField(newObj, $field, ${javaMember.name});")
                            child("env->DeleteLocalRef(${javaMember.name});")

                        } else if (javaMember.toJavaType() == JNIType.JObject) {
                            if (javaMember.type.isEnum) {
                                // process enum
                                child(
                                    "${
                                        javaMember.setJavaValue(
                                            "env",
                                            "newObj",
                                            field,
                                            functionName
                                        )
                                    };"
                                )
                            } else {
                                child("${javaMember.type.simpleName}Mutator ${javaMember.name}Mutator(env);")
                                import("<${javaMember.type.simpleName}Mutator.h>")
                                child("env->SetObjectField(newObj, $field, ${javaMember.name}Mutator.toObject(source.${javaMember.name}));")
                            }
                        } else {
                            child(
                                "${
                                    javaMember.setJavaValue(
                                        "env",
                                        "newObj",
                                        field,
                                        functionName
                                    )
                                };"
                            )
                        }
                    }
                    child("return newObj;")
                }
            }
        }

    val awakeVulkanCpp = "awake-vulkan/src/main/cpp/vulkan-kotlin"
    FileWriter.writeFile(
        "$awakeVulkanCpp/includes/${clazz.simpleName + "Mutator"}.h",
        cppClassCode.first
    )
    FileWriter.writeFile("$awakeVulkanCpp/${clazz.simpleName + "Mutator"}.cpp", cppClassCode.second)
}