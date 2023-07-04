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
        classpath("org.jetbrains.dokka:dokka-gradle-plugin:${Versions.kotlin}")
    }
}

allprojects {
    group = "io.github.ronjunevaldoz"
    version = "1.0.0-SNAPSHOT"

    subprojects {
        apply(plugin = "org.jetbrains.dokka")
    }
}