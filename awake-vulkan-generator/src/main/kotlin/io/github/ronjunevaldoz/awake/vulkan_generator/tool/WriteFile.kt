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

import io.github.ronjunevaldoz.awake.vulkan_generator.tool.FileWriter.rootDir
import java.io.File

object FileWriter {
    var rootDir: String? = null
    fun writeFile(fileName: String, content: String) {
        val file = File(rootDir, fileName)

        // Ensure that the directory exists
        file.parentFile.mkdirs()
        try {
            file.createNewFile()
            file.writeText(content)
            println("File created successfully. $fileName")
        } catch (e: Exception) {
            println("Error creating the file: ${e.message} | ${file.absoluteFile}")
        }
    }
}

fun cmakeListTemplate(path: String = ""): String {
    val commonUtilsDir = File(rootDir, path)
    val cmakeListsTxt = buildString {
        append("# common/utils/CMakeLists.txt\n\n")
        // Set the source files for the common Vulkan utilities
        append("set(COMMON_UTILS_VULKAN_UTILS_SOURCES\n")
        commonUtilsDir.listFiles()?.forEach { file ->
            if (file.isFile && file.extension == "cpp") {
                append("        ${file.name}\n")
            }
        }
        append("        )\n\n")

        append("# Set the path to your header file directory\n")
        append("include_directories(includes)\n")
        // Create a static library for the common utilities
        append("add_library(common_utils_vulkan_utils STATIC \${COMMON_UTILS_VULKAN_UTILS_SOURCES})\n\n")

        // Add the 'include' directory for the library
        append("target_include_directories(common_utils_vulkan_utils PUBLIC \${CMAKE_CURRENT_SOURCE_DIR})\n")
    }
    FileWriter.writeFile("${path}CMakeLists.txt", cmakeListsTxt)
    return cmakeListsTxt
}