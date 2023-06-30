import Deps.lwjgl
import Deps.napier
plugins {
    kotlin("multiplatform")
    id("com.android.library")
    id("org.jetbrains.compose")
    id("convention.publication")
}

kotlin {
    targetHierarchy.default()

    android {
        compilations.all {
            kotlinOptions {
                jvmTarget = "1.8"
            }
        }
        publishLibraryVariants("release", "debug")
    }
    val iosArm64 = iosArm64()
    val iosX64 = iosX64()
    val iosSimulatorArm64 = iosSimulatorArm64()

    val appleTargets = listOf(
        iosX64,
        iosArm64,
        iosSimulatorArm64
    )

    appleTargets.forEach { target ->
        with(target) {
            binaries {
                framework {
                    baseName = "awake-core"
                }
            }
        }
    }

    jvm("desktop") {
        compilations.all {
            kotlinOptions.jvmTarget = "11"
        }
    }

    // all items included here will be uploaded once isMainHost=true
    // ./gradlew publishAllPublicationsToSonatypeRepository -PisMainHost=true
    val publicationsFromMainHost = listOf(
        android(),
        jvm("desktop"),
        iosX64(),
        iosArm64(),
        iosSimulatorArm64(),
    ).map { it.name } + "kotlinMultiplatform"

    publishing {
        publications {
            matching { it.name in publicationsFromMainHost }.all {
                val targetPublication = this@all
                tasks.withType<AbstractPublishToMaven>()
                    .matching {
                        it.publication == targetPublication && targetPublication.name.contains(
                            "ios",
                            false
                        )
                    }
                    .configureEach {
                        onlyIf {
                            findProperty("isMainHost") == "true"
                        }
                    }
            }
        }
    }

    sourceSets {
        val commonMain by getting {
            dependencies {
                //put your multiplatform dependencies here
                implementation(compose.runtime)
                implementation(compose.foundation)
                @OptIn(org.jetbrains.compose.ExperimentalComposeLibrary::class)
                implementation(compose.components.resources)
                implementation(napier)
            }
        }
        val commonTest by getting {
            dependencies {
                implementation(kotlin("test"))
            }
        }
        val desktopMain by getting {
            dependencies {
                implementation(compose.desktop.currentOs)
                implementation(platform(lwjgl.bom))
                implementation(lwjgl.lwjgl)
                implementation(lwjgl.glfw)
                implementation(lwjgl.opengl)
                implementation(lwjgl.stb)
                implementation(lwjgl.natives.lwjgl)
                implementation(lwjgl.natives.glfw)
                implementation(lwjgl.natives.opengl)
                implementation(lwjgl.natives.stb)
            }
        }
    }
}


android {
    namespace = "io.github.ronjunevaldoz.awake.core"
    compileSdk = 33
    defaultConfig {
        minSdk = 24
    }
    publishing {
        multipleVariants {
            withSourcesJar()
            withJavadocJar()
            allVariants()
        }
    }
}

afterEvaluate {
    // TODO find a better way to fix publishAllPublicationsToSonatypeRepository without below config
    tasks.withType<PublishToMavenRepository> {
        dependsOn(tasks.signKotlinMultiplatformPublication)
        val platforms = listOf(
            "AndroidDebug",
            "AndroidRelease",
            "Desktop",
            "IosX64",
            "IosArm64",
            "IosSimulatorArm64",
        )
        platforms.forEach { platform ->
            dependsOn("sign${platform}Publication")
        }
    }
}