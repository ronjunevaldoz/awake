import java.util.Properties

plugins {
    kotlin("multiplatform")
    id("com.android.library")
    `maven-publish`
    signing
}

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
            baseName = "awakeCore"
        }
    }

    jvm("desktop") {
        compilations.all {
            kotlinOptions.jvmTarget = "11"
        }
    }

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

// setup dokka
val dokkaOutputDir = "$buildDir/dokka"

tasks.getByName<org.jetbrains.dokka.gradle.DokkaTask>("dokkaHtml") {
    outputDirectory.set(file(dokkaOutputDir))
}

val deleteDokkaOutputDir by tasks.register<Delete>("deleteDokkaOutputDirectory") {
    delete(dokkaOutputDir)
}

val javadocJar = tasks.register<Jar>("javadocJar") {
    dependsOn(deleteDokkaOutputDir, tasks.dokkaHtml)
    archiveClassifier.set("javadoc")
    from(dokkaOutputDir)
}

val secretPropExists = File("secret.properties").exists()

// setup publishing
publishing {
    publications {
        if (secretPropExists) {
            val properties = Properties().apply {
                load(rootProject.file("secret.properties").reader())
            }
// <OSSRH jira account username>
            val ossrhUsername = properties["ossrhUsername"] as String?
// <OSSRH jira account password>
            val ossrhPassword = properties["ossrhPassword"] as String?
// <your-key-id-(last 8 character of your key)>
            val signingKeyId = properties["signing.keyId"] as String?
// passphrase
            val signingPassword = properties["signing.password"] as String?
// gpg --export-secret-keys <last 8 character of your key> | base64
            val signingKey = properties["signing.secretKey"] as String?
// gpg --edit-key F8F55D3E
// gpg --list-signatures
// gpg --keyring secring.gpg --export-secret-keys > ~/.gnupg/secring.gpg
// or raw base64 secretkey
// gpg --export-secret-keys <last 8 character of your key> | base64
// https://stackoverflow.com/a/39573795/2801777

            signing {
                useInMemoryPgpKeys(
                    signingKeyId,
                    signingKey,
                    signingPassword
                )
                sign(publishing.publications)
            }

            repositories {
                maven {
                    val releasesRepoUrl = "https://s01.oss.sonatype.org/service/local/staging/deploy/maven2/"
                    val snapshotsRepoUrl = "https://s01.oss.sonatype.org/content/repositories/snapshots/"
                    url =  uri(if (version.toString().endsWith("SNAPSHOT")) snapshotsRepoUrl else releasesRepoUrl)
                    credentials {
                        username = ossrhUsername
                        password = ossrhPassword
                    }
                }
            }
        } else {
            repositories {
                mavenLocal()
            }
        }
        withType<MavenPublication> {
            artifact(javadocJar)
            pom {
                name.set("Awake")
                description.set("Cross-platform Graphics")
                licenses {
                    license {
                        name.set("MIT")
                        url.set("https://opensource.org/licenses/MIT")
                    }
                }
                url.set("https://ronjunevaldoz.github.io/awake")
                issueManagement {
                    system.set("Github")
                    url.set("https://github.com/ronjunevaldoz/awake/issues")
                }
                scm {
                    connection.set("https://github.com/ronjunevaldoz/awake.git")
                    url.set("https://github.com/ronjunevaldoz/awake")
                }
                developers {
                    developer {
                        name.set("Ron June Valdoz")
                        email.set("ronjune.lopez@gmail.com")
                    }
                }
            }
        }
    }
}