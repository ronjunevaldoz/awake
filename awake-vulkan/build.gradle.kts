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
            val libVkLayerPath =
                "${rootDir.absolutePath}/awake-vulkan/src/main/jniLibs/arm64-v8a/libVkLayer_khronos_validation.so"
            if (!File(libVkLayerPath).exists()) {
                throw Exception("libVkLayer_khronos_validation.so does not exist in $libVkLayerPath")
            }
            dependencies {
                implementation(files(libVkLayerPath))
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
                abiFilters += listOf("arm64-v8a")
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