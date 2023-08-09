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

package io.github.ronjunevaldoz.awake.vulkan_generator.toolv2

import io.github.ronjunevaldoz.awake.vulkan.VkDeserializer
import io.github.ronjunevaldoz.awake.vulkan.VkHandleRef
import io.github.ronjunevaldoz.awake.vulkan.models.VkExtent2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkOffset2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkRect2D
import io.github.ronjunevaldoz.awake.vulkan.models.VkStencilOpState
import io.github.ronjunevaldoz.awake.vulkan.models.VkViewport
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkApplicationInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkDeviceQueueCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.VkGraphicsPipelineCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineCacheCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineColorBlendAttachmentState
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineColorBlendStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineDepthStencilStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineDynamicStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineInputAssemblyStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineLayoutCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineMultisampleStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineRasterizationStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineShaderStageCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineTessellationStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineVertexInputStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPipelineViewportStateCreateInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkPushConstantRange
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkSpecializationInfo
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkSpecializationMapEntry
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkVertexInputAttributeDescription
import io.github.ronjunevaldoz.awake.vulkan.models.info.pipeline.VkVertexInputBindingDescription
import io.github.ronjunevaldoz.awake.vulkan.physicaldevice.VkPhysicalDeviceFeatures
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.FileWriter
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.JNIType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.cast
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.cmakeListTemplate
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getArrayElement
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getArrayElementJavaType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getArrayRegion
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getJavaValue
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.getVkHandle
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.isVkHandle
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.isVkPointer
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.javaTypeSuffix
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.setJavaValue
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toCppType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toJavaSignature
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toJavaType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toJavaTypeArray


inline fun <reified T : Any> generateJavaToVulkanCpp() {
    val clazz = T::class.java

    createVulkanAccessor(clazz)
    createVulkanMutator(clazz)
}

fun createVulkanAccessor(clazz: Class<*>) {
    val declareMembers = clazz.declaredFields
    val cppClassCode =
        cppClass(clazz.simpleName + "Accessor", "Vulkan accessor e C++ header file") {
            import("<jni.h>")
            import("<vulkan/vulkan.h>")
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

            // generate getters
            declareMembers.forEach { javaMember ->
                val type = if (javaMember.type.isArray) {
                    javaMember.toJavaTypeArray()
                } else {
                    javaMember.toJavaType()
                }

                val returnType: String = if (javaMember.type.isEnum) {
                    javaMember.type.simpleName
                } else if (javaMember.isVkHandle()) {
                    javaMember.getVkHandle().name
                } else {
                    javaMember.toCppType()
                }
                val functionName = "get" + javaMember.name
                function(
                    1, returnType, functionName, emptyList()
                ) {
                    body(2) {
                        val javaValue = javaMember.getJavaValue(
                            "env",
                            "obj",
                            javaMember.name + "Field"
                        )

                        val suffix = javaMember.javaTypeSuffix()
                        val localVariable = javaMember.name + suffix

                        // convert to vulkan value
                        if (javaMember.type.isEnum) {
                            child("auto $localVariable = ($type) $javaValue;")
                            child("return (${returnType}) enum_utils::getEnumFromObject(env, $localVariable);")
                        } else if (javaMember.type.isPrimitive) {
                            if (javaMember.isVkHandle()) {
                                child("return reinterpret_cast<$returnType>($javaValue); // VkHandle")
                            } else if (javaMember.isVkPointer()) {
                                child("return reinterpret_cast<$returnType>($javaValue); // Pointer")
                            } else {
                                child("return (${returnType}) ($type) $javaValue; // primitive")
                            }
                        } else if (javaMember.type.isArray) {
                            child("auto $localVariable = ($type) $javaValue;")
                            child("if($localVariable == nullptr) {")
                            child("     return {};")
                            child("}")
                            child("auto size = env->GetArrayLength($localVariable);")
                            when (val javaType = javaMember.getArrayElementJavaType()) {
                                JNIType.JString -> {
                                    child("$returnType array;")
                                    child("for (int i = 0; i < size; ++i) {")
                                    child(
                                        "     auto element = ($javaType) env->${
                                            javaMember.getArrayElement(
                                                localVariable,
                                                "i"
                                            )
                                        }(ppEnabledLayerNamesArray, i);"
                                    )
                                    child("     auto str = env->GetStringUTFChars(element, nullptr);")
                                    child("     auto result = strdup(str); // Allocate memory and copy the string")
                                    child("     env->ReleaseStringUTFChars(element, str); // Release the local string reference")
                                    child("     array.push_back(result);")
                                    child("}")
                                }

                                JNIType.JObject -> {
                                    val accessor =
                                        "${javaMember.type.componentType.simpleName}Accessor"  // TODO fix hardcoded

                                    child("$returnType array;")
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
                                        child("     array.push_back(accessor.fromObject());")
                                    } else {
                                        // possible type is Any or Null??
                                        child("     array.push_back(element); // type is Any??")
                                    }
                                    child("}")
                                }

                                else -> {
                                    child("$returnType array(size);")

                                    child(
                                        "env->${
                                            javaMember.getArrayRegion(
                                                localVariable,
                                                "0",
                                                "size",
                                                "reinterpret_cast<${javaMember.toJavaType()} *>(array.data())"
                                            )
                                        }"
                                    )
                                }
                            }
                            child("return array;")
                        } else {
                            // object
                            if (type == "jstring" || type == JNIType.JString) {
                                child("auto $localVariable = ($type) $javaValue;")
                                child("auto str = ($returnType) env->GetStringUTFChars($localVariable, nullptr);")
                                child("auto result = strdup(str); // Allocate memory and copy the string")
                                child("env->ReleaseStringUTFChars($localVariable, str); // Release the local string reference")
                                child("return result;")
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
                                    child("$accessor accessor(env, $localVariable);") // TODO fix hardcoded
                                    child("if($localVariable == nullptr) {")
                                    child("     return {};")
                                    child("}")
                                    child("return (${returnType}) (accessor.fromObject()); // Object is null, should be accessed by an accessor")
                                } else {
                                    child("return (${returnType}) ($type) $javaValue; // Object??")
                                }
                            }
                        }
                    }
                }
            }


            function(
                1, clazz.simpleName, "fromObject"
            ) {
                body(2) {
                    val clazzInfo = "clazzInfo"
                    child("${clazz.simpleName} $clazzInfo{};")
                    declareMembers.forEach { javaMember ->
                        val functionName = "get" + javaMember.name
                        if (javaMember.type.isArray) {
                            // assume that this array is a std::vector
                            if (javaMember.type.componentType.isPrimitive) {
                                child("auto ${javaMember.name} = ${functionName}();  // ${javaMember.type.componentType.simpleName} Primitive Array")
                                child("std::copy(${javaMember.name}.begin(), ${javaMember.name}.end(), $clazzInfo.${javaMember.name});")
                            } else {
//                                if(clazz.isAnnotationPresent(VkHandleRef::class.java)) {
//                                    val handle = clazz.getDeclaredAnnotation(VkHandleRef::class.java)
//                                    handle.name ==
//                                }
                                // TODO VkHandleRef is not working in pSetLayouts
//                                @VkHandleRef("VkDescriptorSetLayout")
//                                val pSetLayouts: Array<VkDescriptorSetLayout> = emptyArray(), // Optional
                                if (javaMember.type.componentType.isAnnotationPresent(VkHandleRef::class.java)) {
//                                   child("reinterpret_cast<${javaMember.type.componentType..simpleName} const *>(${functionName}().data())")
                                    child("$clazzInfo.${javaMember.name} = ${functionName}().data(); // VkHandle Element Array")
                                } else {
                                    child("$clazzInfo.${javaMember.name} = ${functionName}().data(); // Object Array")
                                }
                            }
                        } else if (javaMember.isVkPointer()) {
                            child("auto ${javaMember.name}Ptr = ${functionName}();")
                            child("$clazzInfo.${javaMember.name} = ${javaMember.name}Ptr; // Pointer")
                        } else {
                            child("$clazzInfo.${javaMember.name} = ${functionName}(); // Object")
                        }
                    }
                    // return clazz info
                    child("return $clazzInfo;")
                }
            }
        }

    val awakeVulkanCpp = "awake-vulkan/src/main/cpp/common/utils/"
    FileWriter.writeFile("$awakeVulkanCpp${clazz.simpleName + "Accessor"}.cpp", cppClassCode)
    println(cppClassCode)
}

fun createVulkanMutator(clazz: Class<*>) {
    if (!clazz.isAnnotationPresent(VkDeserializer::class.java)) {
        return
    }
    val declareMembers = clazz.declaredFields
    val cppClassCode =
        cppClass(clazz.simpleName + "Mutator", "Vulkan mutator e C++ header file") {
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
                    child("env->DeleteGlobalRef(clazz);")
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
                        child("${javaMember.setJavaValue("env", "newObj", field, functionName)};")
                    }
                    child("return newObj;")
                }
            }
        }

    val awakeVulkanCpp = "awake-vulkan/src/main/cpp/common/utils/"
    FileWriter.writeFile("$awakeVulkanCpp${clazz.simpleName + "Mutator"}.cpp", cppClassCode)
    println(cppClassCode)
}

fun main() {
    generateJavaToVulkanCpp<VkApplicationInfo>()
    generateJavaToVulkanCpp<VkPhysicalDeviceFeatures>()
    generateJavaToVulkanCpp<VkDeviceQueueCreateInfo>()
    generateJavaToVulkanCpp<VkDeviceCreateInfo>()

    //
    generateJavaToVulkanCpp<VkExtent2D>()

    // pipeline
    generateJavaToVulkanCpp<VkSpecializationMapEntry>()
    generateJavaToVulkanCpp<VkSpecializationInfo>()
    generateJavaToVulkanCpp<VkPipelineShaderStageCreateInfo>()
    generateJavaToVulkanCpp<VkGraphicsPipelineCreateInfo>()

    generateJavaToVulkanCpp<VkPushConstantRange>()
    generateJavaToVulkanCpp<VkPipelineLayoutCreateInfo>()
    generateJavaToVulkanCpp<VkPipelineCacheCreateInfo>()
    generateJavaToVulkanCpp<VkGraphicsPipelineCreateInfo>()
    // states
    generateJavaToVulkanCpp<VkStencilOpState>()
    generateJavaToVulkanCpp<VkPipelineColorBlendAttachmentState>()

    generateJavaToVulkanCpp<VkPipelineColorBlendStateCreateInfo>()
    generateJavaToVulkanCpp<VkPipelineDepthStencilStateCreateInfo>()
    generateJavaToVulkanCpp<VkPipelineMultisampleStateCreateInfo>()
    generateJavaToVulkanCpp<VkPipelineRasterizationStateCreateInfo>()
    generateJavaToVulkanCpp<VkPipelineTessellationStateCreateInfo>()
    // dynamic state
    generateJavaToVulkanCpp<VkPipelineDynamicStateCreateInfo>()
    // vertex input state
    generateJavaToVulkanCpp<VkVertexInputBindingDescription>()
    generateJavaToVulkanCpp<VkVertexInputAttributeDescription>()
    generateJavaToVulkanCpp<VkPipelineVertexInputStateCreateInfo>()
    // input assembly
    generateJavaToVulkanCpp<VkPipelineInputAssemblyStateCreateInfo>()
    generateJavaToVulkanCpp<VkOffset2D>()
    generateJavaToVulkanCpp<VkRect2D>()
    generateJavaToVulkanCpp<VkViewport>()
    generateJavaToVulkanCpp<VkPipelineViewportStateCreateInfo>()

    println(cmakeListTemplate("awake-vulkan/src/main/cpp/common/utils/"))
}