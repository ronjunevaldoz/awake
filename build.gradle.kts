/*
 * Awake
 * Awake
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
    // this is necessary to avoid the plugins to be loaded multiple times
    // in each subproject's classloader
    kotlin("jvm").apply(false)
    kotlin("multiplatform").apply(false)
    id("com.android.application").apply(false)
    id("com.android.library").apply(false)
    id("org.jetbrains.compose").apply(false)
}

buildscript {
    dependencies {
        classpath("org.jetbrains.dokka:dokka-gradle-plugin:${Versions.kotlin}")
        classpath("io.gitlab.arturbosch.detekt:detekt-gradle-plugin:${Versions.detekt}")
    }
}

allprojects {
    group = "io.github.ronjunevaldoz"
    version = "1.0.0-SNAPSHOT"

    subprojects {
        apply(plugin = "org.jetbrains.dokka")
        apply(plugin = "io.gitlab.arturbosch.detekt")
    }
}