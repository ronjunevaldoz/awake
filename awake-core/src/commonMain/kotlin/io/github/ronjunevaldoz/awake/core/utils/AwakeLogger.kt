package io.github.ronjunevaldoz.awake.core.utils

import io.github.aakira.napier.LogLevel
import io.github.aakira.napier.Napier

object AwakeLogger {
    fun log(level: LogLevel, tag: String?, throwable: Throwable?, message: String) {
        Napier.log(level, tag, throwable, message)
    }
    fun debug(message: String) {
        Napier.d(message)
    }
    fun info(message: String) {
        Napier.i(message)
    }
    fun warn(message: String) {
        Napier.w(message)
    }
    fun error(message: String) {
        Napier.e(message)
    }
}