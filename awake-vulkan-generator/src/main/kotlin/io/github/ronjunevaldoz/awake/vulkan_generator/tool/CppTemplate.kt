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

import io.github.ronjunevaldoz.awake.vulkan.VkDeserializer
import java.lang.reflect.Field

fun cppTemplate(
    clazz: Class<*>,
    fields: Array<Field>,
    className: String,
    classSimpleName: String,
    classSig: String,
    date: String,
    converters: String,
    imports: String,
    sourceObj: String,
    initFields: String,
    processFields: String,
    assignValues: String,
    deleteFields: String,
    clearFields: String
): String {
    val isDeserializerEnabled = clazz.isAnnotationPresent(VkDeserializer::class.java)
    val processDeserializer = buildString {
        val tab = "\t".repeat(1)
        val childTab = "\t".repeat(2)
        if (isDeserializerEnabled) {
            append(tab)
            append("jobject newObj = env->NewObject(clazz, constructor);")
            appendLine()
            append(tab)
            append("if(newObj == nullptr) {")
            appendLine()
            append(childTab)
            append("return nullptr;")
            appendLine()
            append(tab)
            append("}")
            appendLine()
            append(fields.setObjValues("newObj", "vulkan"))
            appendLine()
            append(tab)
            append("return newObj;")
        } else {
            append(tab)
            append("// TODO not yet implemented")
            appendLine()
            append("return nullptr;")
        }
    }
    return """
/* 
 * $className.cpp
 * Created by Ron June Valdoz on $date
 */
 
#include <vector>
#include "$className.h"
#include "enum_utils.h"
$imports

$className::$className(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass("$classSig");
    ${if (isDeserializerEnabled) "constructor = env->GetMethodID(clazz, \"<init>\", \"()V\");" else ""}
$initFields
}

$classSimpleName
$className::fromObject(jobject $sourceObj) {
    if(!env->IsInstanceOf($sourceObj, clazz)) {
        throw std::runtime_error("Invalid object. Expected $classSimpleName.");
    }
${fields.initValkanValues(sourceObj)}
$converters
$processFields
$classSimpleName createInfo;
$assignValues
$deleteFields
    return createInfo;
}

jobject $className::toObject($classSimpleName &vulkan) {
$processDeserializer
}

$className::~$className() {

}
        """.trimIndent()
}