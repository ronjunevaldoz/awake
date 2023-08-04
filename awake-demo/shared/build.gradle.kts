/*
 * Awake
 * Awake.awake-demo.shared
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

plugins {
    kotlin("multiplatform")
    kotlin("native.cocoapods")
    id("com.android.library")
    id("org.jetbrains.compose")
}

kotlin {
    android()

    jvm("desktop")

    iosX64()
    iosArm64()
    iosSimulatorArm64()

    cocoapods {
        version = "1.0.0"
        summary = "Awake Demo Compose"
        homepage = "io.github.ronjunevaldoz/awake-demo"
        ios.deploymentTarget = "14.1"
        podfile = project.file("../iosApp/Podfile")
        framework {
            baseName = "shared"
            isStatic = true
        }
        extraSpecAttributes["resources"] =
            "['src/commonMain/resources/**', 'src/iosMain/resources/**']"
    }

    sourceSets {
        val commonMain by getting {
            dependencies {
                implementation(compose.runtime)
                implementation(compose.foundation)
                implementation(compose.material3)
                @OptIn(org.jetbrains.compose.ExperimentalComposeLibrary::class)
                implementation(compose.components.resources)
                implementation(project(":awake-core"))
            }
        }
        val androidMain by getting {
            dependencies {
                api("androidx.activity:activity-compose:1.6.1")
                api("androidx.appcompat:appcompat:1.6.1")
                api("androidx.core:core-ktx:1.9.0")
            }
        }
        val iosX64Main by getting
        val iosArm64Main by getting
        val iosSimulatorArm64Main by getting
        val iosMain by creating {
            dependsOn(commonMain)
            iosX64Main.dependsOn(this)
            iosArm64Main.dependsOn(this)
            iosSimulatorArm64Main.dependsOn(this)
        }
        val desktopMain by getting {
            dependencies {
                implementation(compose.desktop.common)
            }
        }
    }
}

android {
    compileSdkVersion((findProperty("android.compileSdk") as String).toInt())
    namespace = "io.github.ronjunevaldoz.awake.demo.common"

    sourceSets["main"].manifest.srcFile("src/androidMain/AndroidManifest.xml")
    sourceSets["main"].res.srcDirs("src/androidMain/res")
    sourceSets["main"].resources.srcDirs("src/commonMain/resources")

    defaultConfig {
        minSdk = (findProperty("android.minSdk") as String).toInt()
        targetSdk = (findProperty("android.targetSdk") as String).toInt()
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }
    kotlin {
        jvmToolchain(11)
    }
}


tasks.register<Glslangvalidator_conventions_gradle.GlslValidator>("glslValidator") {
    val commonResourceDir = android.sourceSets["main"].resources.srcDirs.first { srcDir ->
        srcDir.toString().contains("common")
    }

    val shadersDir = File(commonResourceDir, "assets/shader/vulkan")
    targetVulkanVersion.set(1.3) // TODO get version from awake-vulkan library
    shaderDir.set(shadersDir.path)
    spvDir.set(shadersDir.path)
}

tasks.register<JavaExec>("runVulkanCpp") {
//    doFirst {
    mainClass.set("io.github.ronjunevaldoz.awake.vulkan_generator.MainKt")
    classpath = project(":awake-vulkan-generator").sourceSets["main"].runtimeClasspath
    args(project(":awake-vulkan-generator").rootDir.path)
//    }
}
// After evaluating the project configuration
afterEvaluate {
    // Access the preCompileShaders task and make it run before Java compilation tasks
    tasks.withType(JavaCompile::class.java) {
        dependsOn(tasks.withType<Glslangvalidator_conventions_gradle.GlslValidator>())
        dependsOn(tasks.named("runVulkanCpp"))
    }
}