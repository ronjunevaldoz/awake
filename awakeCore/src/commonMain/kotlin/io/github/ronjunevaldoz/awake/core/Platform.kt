package io.github.ronjunevaldoz.awake.core

interface Platform {
    val name: String
}

expect fun getPlatform(): Platform