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

fun headerTemplate(
    clazz: Class<*>,
    className: String,
    classSimpleName: String,
    date: String,
    definition: String,
    fields: String,
): String {
    val enabled = clazz.isAnnotationPresent(VkDeserializer::class.java)
    return """
/* 
 * $className.h
 * Created by Ron June Valdoz on $date
 */

#ifndef ${definition}_H
#define ${definition}_H

#include <jni.h>
#include <vulkan/vulkan.h>

class $className {
private:
    JNIEnv *env;
    jclass clazz;
    ${if (enabled) "jmethodID constructor;" else ""}
$fields
public:
    explicit $className(JNIEnv *env);
    
    $classSimpleName fromObject(jobject createInfo);
    
    jobject toObject($classSimpleName &vulkan);
    
    ~$className();
};

#endif /* ${definition}_H */
        """.trimIndent()
}