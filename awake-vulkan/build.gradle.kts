/*
 * Awake
 * Awake.awake-vulkan
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
    id("com.android.library")
}

@OptIn(org.jetbrains.kotlin.gradle.ExperimentalKotlinGradlePluginApi::class)
kotlin {
    targetHierarchy.default()

    android {
        compilations.all {
            kotlinOptions {
                jvmTarget = "1.8"
            }
        }
    }

    listOf(
        iosX64(),
        iosArm64(),
        iosSimulatorArm64()
    ).forEach {
        it.binaries.framework {
            baseName = "awake-vulkan"
        }
    }

    jvm("desktop")

    sourceSets {
        val commonMain by getting {
            dependencies {
                //put your multiplatform dependencies here
            }
        }
        val commonTest by getting {
            dependencies {
                implementation(kotlin("test"))
            }
        }
        val androidMain by getting {
            dependencies {
                // this will ensure that all vulkan layer validation .so is included
                implementation(fileTree("src/main/jniLibs") {
                    include("**/*.so")
                })
                implementation("com.squareup.leakcanary:leakcanary-android:2.12")
            }
        }
    }
}

android {
    namespace = "io.github.ronjunevaldoz.awake.vulkan"
    compileSdk = 33
    ndkVersion = "25.2.9519653"
    sourceSets["main"].manifest.srcFile("src/androidMain/AndroidManifest.xml")
    sourceSets["main"].res.srcDirs("src/androidMain/res")
    sourceSets["main"].jniLibs.srcDirs("src/main/jniLibs")

    defaultConfig {
        minSdk = 24
        externalNativeBuild {
            cmake {
                abiFilters += listOf("arm64-v8a", "armeabi-v7a", "x86", "x86_64")
                cppFlags += listOf("-DVK_USE_PLATFORM_ANDROID_KHR", "-lvulkan")
//                "-DVKB_VALIDATION_LAYERS=OFF"
                arguments += listOf("-DANDROID_TOOLCHAIN=clang", "-DANDROID_STL=c++_static")
            }
        }
    }
    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
            buildStagingDirectory("build-native")
        }
    }
    buildTypes {
        debug {
            isJniDebuggable = true
        }
    }
    buildFeatures {
        viewBinding = true
        prefab = true
    }
}