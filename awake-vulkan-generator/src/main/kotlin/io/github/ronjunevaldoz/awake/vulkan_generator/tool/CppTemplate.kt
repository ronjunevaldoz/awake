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

fun cppTemplate(
    className: String,
    classSimpleName: String,
    classSig: String,
    date: String,
    converters: String,
    imports: String,
    sourceObj: String,
    initFields: String,
    accessFields: String,
    processFields: String,
    assignValues: String,
    deleteFields: String,
    clearFields: String
): String {
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
$initFields
}

$classSimpleName
$className::fromObject(jobject $sourceObj) { 
$accessFields 
$converters
$processFields
$classSimpleName createInfo;
$assignValues
$deleteFields
    return createInfo;
}

$className::~$className() {
    env->DeleteLocalRef(clazz);
    clazz = nullptr;
$clearFields
}
        """.trimIndent()
}