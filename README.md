![Build And Publish](https://github.com/ronjunevaldoz/awake/actions/workflows/build-and-publish.yml/badge.svg)
![Sonatype Nexus (Snapshots)](https://img.shields.io/nexus/s/io.github.ronjunevaldoz/awake-core?server=https%3A%2F%2Fs01.oss.sonatype.org)
[![Kotlin](https://img.shields.io/badge/kotlin-1.8.20-blue.svg?logo=kotlin)](http://kotlinlang.org)
[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

# Awake multiplatform

Cross-platform OpenGL & Vulkan graphics

> **Note**
> The library is still experimental and might experience issues. The Android and iOS platform has an
> stable and working opengl while the Desktop platform which uses lwjgl/glfw window is still under
> development and experimental.

### Features Supported

- OpenGL
    - [x] Android OpenGL
    - [x] iOS OpenGL
    - [x] Desktop OpenGL (JVM experimental due to imcompatibility to compose AWT)
- Vulkan
    - [ ] Android Vulkan (TODO)
    - [ ] iOS MoltenVK / Metal (TODO)
    - [ ] Desktop (TODO)

### Installation

To use this library in your Kotlin Multiplatform project, follow the steps below:

1. Add the library as a dependency in your Gradle `build.gradle.kts`

    ```kotlin
   implementation("io.github.ronjunevaldoz:awake-core:1.0.0-SNAPSHOT")
    ```

    ```kotlin
    repositories {
         maven("https://s01.oss.sonatype.org/content/repositories/snapshots")
    }
    ```

### Example Usage

1. Initialize the AwakeContext

    ```kotlin
        // by default debug is enabled
        // default fps is set to 60
        // default gl version is set to 3
        AwakeContext.init()
    ```
2. Create a sample compose component

   ```kotlin
        
   ```

### License

This library is released under the Apache, Version 2.0 License..