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

import io.github.ronjunevaldoz.awake.vulkan.VkHandleRef
import io.github.ronjunevaldoz.awake.vulkan.VkReturnType
import io.github.ronjunevaldoz.awake.vulkan.VkSingleton
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.FileWriter
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.JNIType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.builder.CppFunctionBodyBuilder
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.cppClass
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toJavaType
import io.github.ronjunevaldoz.awake.vulkan_generator.tool.toVulkanType
import java.lang.reflect.Method

fun createVulkanUtils(clazz: Class<*>) {
    val methods = clazz.declaredMethods
    val cppClassCode =
        cppClass(
            className = clazz.simpleName + "Utils",
            fileDescription = "Vulkan utils for ${clazz.simpleName}",
            namespace = "awake",
            disableClass = true
        ) {
            import("<jni.h>")
            import("<vulkan/vulkan.h>")
            import("<stdexcept>")
            import("<vector>")
            import("<enum_utils.h>")

            methods.filterNot { it.name.contains("Default", true) }.forEach { method ->
                val returnType =
                    if (method.returnType == Void.TYPE) "void" else method.returnType.toJavaType(
                        true
                    ).value
                val params = method.parameters.map { param ->
                    Pair(param.name, param.type.toJavaType(true).value)
                }

                function(
                    1,
                    returnType,
                    method.name.removePrefix("vk").decapitalize(),
                    if (!method.name.startsWith("vkDestroy")) listOf(
                        Pair(
                            "env",
                            "JNIEnv*"
                        )
                    ) + params else params
                ) {
                    body(2) {
                        val vkReturnType = method.returnType.toVulkanType()
                        val methodParams = processParameters(method, import = { import(it) })
                        val vkMethodName = method.name
                        val vkMethodParams = methodParams.joinToString(", ")
                        when {
                            method.name.startsWith("vkCreate") -> processVkCreate(
                                method,
                                vkReturnType,
                                vkMethodName,
                                vkMethodParams
                            )

                            method.name.startsWith("vkGet") ||
                                    method.name.startsWith("vkEnumerate")
                            -> processVkGet(
                                method,
                                vkMethodName,
                                vkMethodParams,
                                import = { import(it) }
                            )

                            method.name.startsWith("vkDestroy") -> processVkDestroy(
                                method,
                                vkMethodName,
                                vkMethodParams
                            )

                            method.name.startsWith("vkAllocate") -> processVkAllocate(
                                method,
                                vkMethodName,
                                vkMethodParams
                            )

                            method.name.startsWith("vkCmd") || method.name.contains(
                                "command",
                                true
                            ) -> processVkCmd(
                                vkMethodName,
                                vkMethodParams
                            )

                            else -> processVkDefault(vkMethodName, vkMethodParams)
                        }

                        when (returnType) {
                            "jlong" -> {
                                child("return reinterpret_cast<$returnType>(handle);")
                            }

                            "void" -> {
                                child("// void")
                            }

                            "jobject" -> {
                                import("<includes/${vkReturnType}Mutator.h>")
                                child("return ${vkReturnType}Mutator(env).toObject(handle);")
                            }

                            else -> {
                                if (method.returnType.isArray) {
                                    child("return jArray;")
                                } else {
                                    child("return handle;")
                                }
                            }
                        }
                    }
                }
            }

        }

    val awakeVulkanCpp = "awake-vulkan/src/main/cpp/vulkan-kotlin"
    FileWriter.writeFile(
        "$awakeVulkanCpp/includes/${clazz.simpleName + "Utils"}.h",
        cppClassCode.first
    )
    FileWriter.writeFile(
        "$awakeVulkanCpp/${clazz.simpleName + "Utils"}.cpp",
        cppClassCode.second
    )
}

private fun CppFunctionBodyBuilder.processParameters(
    method: Method,
    import: (dependency: String) -> Unit
): List<String> {
    val methodParams = mutableSetOf<String>()
    method.parameters.forEach { param ->
        val handle = param.getDeclaredAnnotation(VkHandleRef::class.java)
        if (handle != null) {
            val handleVar = handle.name.replace("Vk", "").decapitalize()
            methodParams.add(handleVar)
            child("auto $handleVar = reinterpret_cast<${handle.name}>(${param.name});")
        } else if (param.type.simpleName.startsWith("vk", true)) {
            if (param.type.isEnum) {
                child("// enum ")
                child("auto vk${param.name} = enum_utils::getEnumFromObject(env, ${param.name});")
                methodParams.add("static_cast<${param.type.simpleName}>(vk${param.name})")
            } else if (param.type.isArray) {
                methodParams.add("static_cast<uint32_t>(vkArray.size())")
                methodParams.add("vkArray.data()")
                val accessor = "${param.type.toVulkanType()}Accessor"
                val listType = param.type.componentType.simpleName
                import("<includes/$accessor.h>")
                child("// process array")
                child("auto size = env->GetArrayLength(${param.name});")
                child("std::vector<$listType> vkArray;")
                child("for (int i = 0; i < size; ++i) {")
                child("    $listType info{};")
                child("    auto element = (jobject) env->GetObjectArrayElement(${param.name}, i);")
                child("    $accessor(env, element).fromObject(info);")
                child("    vkArray.push_back(info);")
                child("    env->DeleteLocalRef(element);")
                child("}")
            } else {
                child("// object accessor?")
                methodParams.add("&info")
                child("${param.type.simpleName} info{};")
                val accessor = "${param.type.toVulkanType()}Accessor"
                import("<includes/$accessor.h>")
                // TODO check if singleton
                if (method.name.contains("VkCreateDebugUtilsMessengerEXT", true)) {
                    child("// process singleton")
                    child("$accessor::init(env, ${param.name});")
                    child("$accessor::getInstance().fromObject(info);")
                } else {
                    child("$accessor(env, ${param.name}).fromObject(info);")
                }
            }
        } else {
            methodParams.add("vk${param.name}")
            if (param.type.toJavaType() == JNIType.JString) {
                child("${param.type.toVulkanType()} vk${param.name} = nullptr;")
                child("if (${param.name} != nullptr) {")
                child("    vk${param.name} = env->GetStringUTFChars(${param.name}, nullptr);")
                child("    env->ReleaseStringUTFChars(${param.name}, vk${param.name});")
                child("}")
            } else {
                child("// default??")
                child("${param.type.toVulkanType()} vk${param.name} = ${param.name};")
            }
        }
    }
    return methodParams.toList()
}

private fun CppFunctionBodyBuilder.processVkCreate(
    method: Method,
    returnTypeVulkan: String,
    methodName: String,
    methodParams: String
) {
    val params = if (methodParams.isNotEmpty()) "$methodParams, " else ""
    val handleReturnType = method.getDeclaredAnnotation(VkReturnType::class.java)
    if (handleReturnType != null) {
        child("// handle")
        if (method.returnType.isArray) {
            child("std::vector<${handleReturnType.name}> handle(size);")
            child("VkResult result = $methodName(${params}nullptr, handle.data());")
            child("if(result != VK_SUCCESS){")
            child("    throw std::runtime_error(\"There was a problem executing ${methodName}\");")
            child("}")

            child("auto jArray = env->NewLongArray(static_cast<jsize>(vkArray.size()));")
            child("for (int i = 0; i < size; ++i) {")
            child("    auto value = reinterpret_cast<jlong>(handle[i]);")
            child("    env->SetLongArrayRegion(jArray, i, 1, &value);")
            child("}")
        } else {
            child("${handleReturnType.name} handle;")
            if (method.isAnnotationPresent(VkSingleton::class.java)) {
                child("auto pfn$methodName = (PFN_$methodName) vkGetInstanceProcAddr (instance, \"$methodName\");")

                child("VkResult result = pfn$methodName(${params}nullptr, &handle);")
            } else {

                child("VkResult result = $methodName(${params}nullptr, &handle);")
            }
            child("if(result != VK_SUCCESS){")
            child("    throw std::runtime_error(\"There was a problem executing ${methodName}\");")
            child("}")
        }
    } else {
        child("// default")
        child("$returnTypeVulkan handle;")
        child("VkResult result = $methodName(${params}nullptr, &handle);")
        child("if(result != VK_SUCCESS){")
        child("    throw std::runtime_error(\"There was a problem executing ${methodName}\");")
        child("}")
    }

}

private fun CppFunctionBodyBuilder.processVkAllocate(
    method: Method,
    methodName: String,
    methodParams: String
) {
    val handleReturnType = method.getDeclaredAnnotation(VkReturnType::class.java)
    if (handleReturnType != null) {
        child("${handleReturnType.name} handle;")
    } else {
        child("${method.returnType.toVulkanType()} handle;")
    }
    child("${methodName}(${methodParams}, &handle);")
}

private fun CppFunctionBodyBuilder.processVkDestroy(
    method: Method,
    methodName: String,
    methodParams: String
) {
    if (method.isAnnotationPresent(VkSingleton::class.java)) {
        child("auto pfn$methodName = (PFN_$methodName) vkGetInstanceProcAddr (instance, \"$methodName\");")
        child("pfn${methodName}(${methodParams}, nullptr);")
    } else {
        child("${methodName}(${methodParams}, nullptr);")
    }
}

private fun CppFunctionBodyBuilder.processVkCmd(methodName: String, methodParams: String) {
    child("${methodName}(${methodParams});")
}

private fun CppFunctionBodyBuilder.processVkGet(
    method: Method,
    methodName: String,
    methodParams: String,
    import: (dependency: String) -> Unit
) {
    val returnType = method.returnType
    val vulkanReturnType = returnType.toVulkanType()
    val emptyParams = method.parameters.isEmpty()

    if (returnType.isArray) {
        child("uint32_t count;")
        if (emptyParams) {
            child("${methodName}(&count, nullptr);")
        } else {
            child("${methodName}(${methodParams}, &count, nullptr);")
        }
        if (method.isAnnotationPresent(VkReturnType::class.java)) {
            val handleReturnType = method.getDeclaredAnnotation(VkReturnType::class.java)
            child("std::vector<${handleReturnType.name}> vkArray(count);")
        } else {
            child("std::vector<$vulkanReturnType> vkArray(count);")
        }

        if (emptyParams) {
            child("${methodName}(&count, vkArray.data());")
        } else {
            child("${methodName}(${methodParams}, &count, vkArray.data());")
        }
        // add dependency
        val clazzSig = returnType.componentType.name.replace(".", "/")
        val javaType = returnType.toJavaType(true)
        if (javaType == JNIType.JLongArray) {
            child("auto jArray = env->NewLongArray(static_cast<jsize>(count));")
        } else {
            child("jclass clazz = env->FindClass(\"${clazzSig}\");")
            child("auto jArray = env->NewObjectArray(static_cast<jsize>(count), clazz, nullptr);")
        }
        child("for (int i = 0; i < count; ++i) {")
        if (returnType.componentType.isEnum) {
            child("    jobject obj = enum_utils::setEnumFromVulkan(env, vkArray[i], \"$clazzSig\");")
            child("    env->SetObjectArrayElement(jArray, (jint) i, obj);")
            child("    env->DeleteLocalRef(obj);")
        } else if (javaType == JNIType.JLongArray) {
            child("    auto value = reinterpret_cast<jlong>(vkArray[i]);")
            child("    env->SetLongArrayRegion(jArray, i, 1, &value);")
        } else {
            val mutator = "${vulkanReturnType}Mutator"
            import("<includes/$mutator.h>")
            child("    jobject obj = $mutator(env).toObject(vkArray[i]);")
            child("    env->SetObjectArrayElement(jArray, (jint) i, obj);")
            child("    env->DeleteLocalRef(obj);")
        }
        child("}")
    } else {
        val handleReturnType = method.getDeclaredAnnotation(VkReturnType::class.java)
        if (handleReturnType != null) {
            child("${handleReturnType.name} handle;")
        } else {
            child("$vulkanReturnType handle;")
        }
        if (returnType == Void.TYPE) {
            child("${methodName}(${methodParams}, &handle);")
        } else {
            if (methodName.contains("Properties", true)) {
                child("${methodName}(${methodParams}, &handle);")
            } else {
                child("${methodName}(${methodParams}, &handle);")
            }
        }
    }
}

private fun CppFunctionBodyBuilder.processVkDefault(methodName: String, methodParams: String) {
    child("VkResult result = ${methodName}(${methodParams}, nullptr);")
    child("if(result != VK_SUCCESS){")
    child("    throw std::runtime_error(\"There was a problem executing ${methodName}\");")
    child("}")

}



