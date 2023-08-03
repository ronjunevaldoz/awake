/*
 * Awake
 * Awake.buildSrc.main
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

import java.io.BufferedReader
import java.io.InputStreamReader

abstract class GlslValidator : DefaultTask() {
    @get:Input
    abstract val shaderDir: Property<String>

    @get:Input
    abstract val spvDir: Property<String>

    @get:Input
    abstract val targetEnv: Property<Double>

    val vulkanVersions = listOf(1.0, 1.1, 1.2, 1.3)

    init {
        shaderDir.convention("src/commonMain/resources/assets/shader/vulkan")
        spvDir.convention("src/commonMain/resources/assets/shader/vulkan")
    }

    @TaskAction
    fun preCompileShaders() {
        val shadersDir = File(shaderDir.get())
        val spvsDir = File(spvDir.get())
        val shaders = project.fileTree(shadersDir) {
            include("**/*.frag", "**/*.vert")
        }

        println("shaders ${shaders.dir}")
        shaders.forEach { shaderFile ->
            val shaderExt = shaderFile.extension
            val shaderName =
                if (shaderExt == "frag" || shaderExt == "vert") shaderFile.name else shaderFile.nameWithoutExtension
            val spvFile = File(spvsDir, "$shaderName.spv")
            runGlslangValidator(shaderFile.absolutePath, spvFile.absolutePath, targetEnv.get())
        }
    }

    // Define a function to execute glslangValidator
    private fun runGlslangValidator(glslFile: String, spvFile: String, targetEnv: Double) {
        println(glslFile)
        println(spvFile)

        if (!vulkanVersions.contains(targetEnv)) {
            throw RuntimeException("Invalid vulkan target env $targetEnv")
        }

        val processBuilder = ProcessBuilder()
            .command("glslangValidator", "-V", glslFile, "--target-env", "vulkan$targetEnv", "-o", spvFile)
            .redirectErrorStream(true)
            .inheritIO()

        val process = processBuilder.start()
        val reader = BufferedReader(InputStreamReader(process.inputStream))
        val lines = reader.readLines()
        val result = process.waitFor()
        if (result != 0) {
            var error = ""
            error = "glslangValidator failed with exit code $result"
            for (line in lines) {
                error += "\n$line"
            }
            throw RuntimeException(error)
        }
    }
}