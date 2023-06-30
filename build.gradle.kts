plugins {
    // this is necessary to avoid the plugins to be loaded multiple times
    // in each subproject's classloader
    kotlin("multiplatform").apply(false)
    id("com.android.application").apply(false)
    id("com.android.library").apply(false)
    id("org.jetbrains.compose").apply(false)
}

buildscript {
    dependencies {
        // Use the same version in the error
//        classpath("org.jetbrains.kotlinx:atomicfu-gradle-plugin:${Versions.atomicfu}")
        classpath("org.jetbrains.dokka:dokka-gradle-plugin:${Versions.kotlin}")
    }
}

allprojects {
    group = "io.github.ronjunevaldoz"
    version = "1.0.0-SNAPSHOT"

//    apply(plugin = "kotlinx-atomicfu")

    subprojects {
        apply(plugin = "org.jetbrains.dokka")
    }
}