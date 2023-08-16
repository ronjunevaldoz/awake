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

import io.github.ronjunevaldoz.awake.vulkan_generator.tool.FileWriter
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.JNIType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.builder.CppClassBuilder
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.builder.CppFunctionBodyBuilder
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.cppClass
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getArrayElement
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getArrayElementJavaType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getArrayRegion
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getJavaValue
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getVkArray
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getVkHandle
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.isVkConstArray
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.isVkHandle
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.isVkPointer
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.javaTypeSuffix
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toJavaSignature
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toJavaType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toJavaTypeArray
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toVulkanType
import java.lang.reflect.Field

fun createVulkanAccessor(clazz: Class<*>) {
    val declareMembers = clazz.declaredFields
    val cppClassCode =
        cppClass(clazz.simpleName + "Accessor", "Vulkan accessor for ${clazz.simpleName}") {
            import("<jni.h>")
            import("<vulkan/vulkan_core.h>")
            import("<string>")
            import("<vector>")
            import("<enum_utils.h>")

            member("private", "JNIEnv*", "env")
            member("private", "jobject", "obj")
            member("private", "jclass", "clazz")
            declareMembers.forEach { member ->
                member("private", "jfieldID", member.name + "Field")
            }

            destructor {
                // default destructor
                body(2) {
                    child("env->DeleteGlobalRef(obj);")
                    child("env->DeleteGlobalRef(clazz);")
                }
            }

            constructor(
                false,
                1, listOf(
                    Pair("env", "JNIEnv*"),
                    Pair("obj", "jobject"),
                )
            ) {
                body(2) {
                    child("this->env = env;")
                    child("this->obj = env->NewGlobalRef(obj);")
                    members.forEach { member ->
                        if (member.type == "jfieldID") {
                            val javaField =
                                declareMembers.find { it.name + "Field" == member.name }!!
                            val javaSig = "\"${javaField.toJavaSignature()}\""
                            val sourceClass = "clazz"
                            val fieldName = "\"${javaField.name}\""
                            child("${member.name} = env->GetFieldID($sourceClass, $fieldName, $javaSig);")
                        } else if (member.type == "jclass") {
                            child("${member.name} = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));")
                        }
                    }
                }
            }

            val hasArrayField = true

            // generate getters
            generateVulkanGetters(clazz, declareMembers, hasArrayField)


            generateVulkanFromObject(clazz, declareMembers, hasArrayField)
        }

    val awakeVulkanCpp = "awake-vulkan/src/main/cpp/vulkan-kotlin"
    FileWriter.writeFile(
        "$awakeVulkanCpp/includes/${clazz.simpleName + "Accessor"}.h",
        cppClassCode.first
    )
    FileWriter.writeFile(
        "$awakeVulkanCpp/${clazz.simpleName + "Accessor"}.cpp",
        cppClassCode.second
    )
}


private fun CppClassBuilder.generateVulkanGetters(
    clazz: Class<*>,
    declareMembers: Array<Field>,
    hasArrayField: Boolean
) {
    declareMembers.forEach { javaMember ->
        val type = if (javaMember.type.isArray) {
            javaMember.toJavaTypeArray()
        } else {
            javaMember.toJavaType()
        }
        val returnType: String = if (javaMember.type.isEnum) {
            javaMember.type.simpleName
        } else {
            javaMember.toVulkanType()
        }
        val functionName = "get" + javaMember.name
        fun getReturnType(type: Class<*>): String {
            return when {
                type.isEnum -> returnType
                type.isPrimitive -> when {
                    javaMember.isVkConstArray() -> "void"
                    javaMember.isVkPointer() -> "void"
                    else -> returnType
                }

                type.isArray -> when {
                    type.componentType.isEnum -> "void"
                    else -> when (javaMember.getArrayElementJavaType()) {
                        JNIType.JString -> getReturnType(type.componentType)
                        JNIType.JObject -> getReturnType(type.componentType)
                        else -> "void"
                    }
                }

                else -> "void"
            }
        }

        fun getParameter(type: Class<*>): List<Pair<String, String>> {
            return when {
                type.isEnum -> emptyList()
                type.isPrimitive -> when {
                    javaMember.isVkPointer() -> listOf(Pair("clazzInfo", "${clazz.simpleName}&"))
                    else -> emptyList()
                }

                type.isArray -> when {
                    type.componentType.isEnum -> listOf(Pair("clazzInfo", "${clazz.simpleName}&"))
                    else -> when (javaMember.getArrayElementJavaType()) {
                        JNIType.JString -> getParameter(type.componentType)
                        JNIType.JObject -> getParameter(type.componentType)
                        else -> listOf(Pair("clazzInfo", "${clazz.simpleName}&"))
                    }
                }

                else -> listOf(Pair("clazzInfo", "${clazz.simpleName}&"))
            }
        }

        fun CppFunctionBodyBuilder.createBody(void: Boolean = false) {
            val javaValue = javaMember.getJavaValue(
                "env",
                "obj",
                javaMember.name + "Field"
            )

            val suffix = javaMember.javaTypeSuffix()
            val localVariable = javaMember.name + suffix
            val arrayName = javaMember.name
            fun processArray() {
                fun processDefaultArrayData(clazzInfo: String) {
                    // generate array size assignee
                    val vkArray = javaMember.getVkArray()
                    if (vkArray != null) {
                        val arraySizeName = vkArray.sizeAlias // javaMember.name + "Count"
                        if (arraySizeName.isNotEmpty()) {
                            child("    $clazzInfo.${arraySizeName} = 0;")
                        }
                        child("    clazzInfo.$arrayName = nullptr;")
                    } else if (javaMember.isVkConstArray()) {
                        child("    // const array")
                        child("    // clazzInfo.$arrayName = nullptr;")
                    } else {
                        child("    clazzInfo.$arrayName = nullptr;")
                    }
                }

                fun processStringArray(javaType: JNIType) {
                    child("$returnType $arrayName;")
                    child("for (int i = 0; i < size; ++i) {")
                    child(
                        "     auto element = ($javaType) env->${
                            javaMember.getArrayElement(
                                localVariable,
                                "i"
                            )
                        };"
                    )
                    child("     auto str = env->GetStringUTFChars(element, nullptr);")
                    child("     auto result = strdup(str); // Allocate memory and copy the string")
                    child("     env->ReleaseStringUTFChars(element, str); // Release the local string reference")
                    child("     $arrayName.push_back(result);")
                    child("}")
                }

                fun processObjectArray(javaType: JNIType) {
                    if (javaMember.type.componentType.isEnum) {
                        // process enum array
                        child("$returnType $arrayName;")
                        child("for (int i = 0; i < size; ++i) {")
                        child(
                            "     auto element = ($javaType) env->${
                                javaMember.getArrayElement(
                                    localVariable,
                                    "i"
                                )
                            };"
                        )
                        val enumName = javaMember.type.componentType.simpleName
                        child("     $arrayName.push_back(static_cast<$enumName>(enum_utils::getEnumFromObject(env, element))); // type is enum")
                        child("}")
                    } else {
                        val accessor =
                            "${javaMember.type.componentType.simpleName}Accessor"  // TODO fix hardcoded

                        child("$returnType $arrayName;")
                        child("for (int i = 0; i < size; ++i) {")
                        child(
                            "     auto element = ($javaType) env->${
                                javaMember.getArrayElement(
                                    localVariable,
                                    "i"
                                )
                            };"
                        )
                        // possible std::vector<void*> or void*
                        if (returnType !in listOf("void*", "std::vector<void*>")) {
                            import("<$accessor.cpp>") // TODO move to .h
                            child("     // experimental optimize accessor")
                            child("     $accessor accessor(env, element);") // TODO fix hardcoded
                            if (void) {
                                child("     ${javaMember.type.componentType.simpleName} ref{};")
                                child("     accessor.fromObject(ref);")
                                child("     $arrayName.push_back(ref);")
                            } else {
                                child("     $arrayName.push_back(accessor.fromObject());")
                            }
                        } else {
                            // possible type is Any or Null??
                            child("     $arrayName.push_back(element); // type is Any??")
                        }
                        child("}")
                    }
                }

                fun processPrimitiveArray() {
                    child("// primitive array?")
                    child("$returnType $arrayName(size);")
                    child(
                        "env->${
                            javaMember.getArrayRegion(
                                localVariable,
                                "0",
                                "size",
                                "reinterpret_cast<${javaMember.getArrayElementJavaType()} *>(${arrayName}.data())"
                            )
                        }"
                    )
                }

                fun processArrayData(clazzInfo: String) {
                    val elementType = javaMember.type.componentType
                    // generate array size assignee
                    val vkArray = javaMember.getVkArray()
                    if (vkArray != null) {
                        val arraySizeName = vkArray.sizeAlias // javaMember.name + "Count"
                        if (arraySizeName.isNotEmpty()) {
                            child("auto $arraySizeName = static_cast<uint32_t>($arrayName.size());")
                            child("$clazzInfo.${arraySizeName} = $arraySizeName;")
                        } else {
                            child("// no array size generated")
                        }
                    }
                    if (elementType.isPrimitive) {
                        if (javaMember.isVkConstArray()) {
                            // fixed size array
                            child("std::copy(${arrayName}.begin(), ${arrayName}.end(), $clazzInfo.${arrayName}); // fixed array size")
                        } else {
                            child("// Make a copy of the data to ensure proper memory management;")
                            val newData = javaMember.type.componentType.simpleName
                            child("auto copy = new ${newData}[size];")
                            child("std::copy(${arrayName}.begin(), ${arrayName}.end(), copy);")
                            child("clazzInfo.$arrayName = copy;")
//                            child("$clazzInfo.${arrayName} = $arrayName.data(); // primitive $comment")
                        }
                    } else {
//                        child("$clazzInfo.${arrayName} = $arrayName.data(); // object $comment")
                        child("// Make a copy of the object to ensure proper memory management;")
                        val newData = if (javaMember.toJavaType() == JNIType.JString) {
                            "const char*"
                        } else if (!javaMember.type.componentType.simpleName.startsWith("vk", true)
                            && javaMember.toJavaType() == JNIType.JObject
                        ) {
                            "const void*"
                        } else if (javaMember.toJavaType() == JNIType.JLong && javaMember.isVkHandle()) {
                            javaMember.getVkHandle().name
                        } else if (javaMember.toJavaType() == JNIType.JInt) {
                            "uint32_t"
                        } else {
                            javaMember.type.componentType.simpleName
                        }
                        child("auto copy = new ${newData}[size];")
                        child("std::copy(${arrayName}.begin(), ${arrayName}.end(), copy);")
                        child("clazzInfo.$arrayName = copy;")
                    }
                }


                child("auto $localVariable = ($type) $javaValue;")
                child("if($localVariable == nullptr) {")
                processDefaultArrayData("clazzInfo")
                if (void) {
                    child("    return;")
                } else {
                    child("    return {};")
                }
                child("}")
                child("auto size = env->GetArrayLength($localVariable);")
                when (val javaElementType = javaMember.getArrayElementJavaType()) {
                    JNIType.JString -> processStringArray(javaElementType)
                    JNIType.JObject -> processObjectArray(javaElementType)
                    else -> processPrimitiveArray()
                }
                child("// processing array data")
                processArrayData("clazzInfo")
            }

            fun processObject() {
                // object
                if (type == JNIType.JString) {
                    child("auto $localVariable = ($type) $javaValue;")
                    child("auto str = ($returnType) env->GetStringUTFChars($localVariable, nullptr);")
                    child("auto result = strdup(str); // Allocate memory and copy the string")
                    child("env->ReleaseStringUTFChars($localVariable, str); // Release the local string reference")
                    child("clazzInfo.${javaMember.name} = result;")
                } else {
                    if (javaMember.isVkHandle()) {
                        child("return reinterpret_cast<$returnType>($javaValue); // VkHandle from object??")
                    } else if (returnType.startsWith("vk", true)) {
                        // vulkan object
                        // object is null??
                        // should be accessed by an accessor
                        val accessor =
                            "${javaMember.type.simpleName}Accessor"  // TODO fix hardcoded
                        import("<$accessor.cpp>") // TODO move to .h
                        child("auto $localVariable = ($type) $javaValue;")
                        child("if($localVariable == nullptr) {")
                        if (hasArrayField) {
                            child("     return;")
                        } else {
                            child("     return {};")
                        }
                        child("}")
                        child("$accessor accessor(env, $localVariable);") // TODO fix hardcoded
                        // experimental
                        if (void) {
                            child("${javaMember.type.simpleName} ref{};")
                            child("accessor.fromObject(ref);")
                            if (javaMember.isVkPointer()) {
                                child("clazzInfo.${javaMember.name} = &ref;")
                            } else {
                                child("clazzInfo.${javaMember.name} = ref;")
                            }
                        } else {
                            child("return (${returnType}) (accessor.fromObject()); // Object is null, should be accessed by an accessor")
                        }
                    } else {
                        if (void) {
                            child("auto ref = (${returnType}) ($type) $javaValue; // Any Object")
                            child("clazzInfo.${javaMember.name} = ref;")
                        } else {
                            child("return (${returnType}) ($type) $javaValue; // Any Object")
                        }
                    }
                }
            }

            fun processEnum() {
                child("auto $localVariable = ($type) $javaValue;")
                child("return (${returnType}) enum_utils::getEnumFromObject(env, $localVariable);")
            }

            fun processPrimitive() {
                if (javaMember.isVkHandle()) {
                    child("auto value = $javaValue;")
                    child("if(value == 0) {")
                    child("     return VK_NULL_HANDLE;")
                    child("}")
                    child("return reinterpret_cast<$returnType>(value); // VkHandle")
                } else if (javaMember.isVkPointer()) {
                    child("auto ptr = ($returnType) $javaValue; // Primitive Pointer")
                    child("clazzInfo.${javaMember.name} = &ptr; // Primitive Pointer")
                } else {
                    child("return (${returnType}) ($type) $javaValue; // primitive")
                }
            }
            // convert to vulkan value
            when {
                javaMember.type.isEnum -> processEnum()
                javaMember.type.isPrimitive -> processPrimitive()
                javaMember.type.isArray -> processArray()
                else -> processObject()
            }
        }
        function(
            1,
            getReturnType(javaMember.type),
            functionName,
            getParameter(javaMember.type)
        ) {
            body(2) {
                createBody(void = getReturnType(javaMember.type) == "void")
            }
        }
    }
}

private fun CppClassBuilder.generateVulkanFromObject(
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