package io.github.ronjunevaldoz.awake.core.utils

import kotlin.native.concurrent.ThreadLocal

@ThreadLocal
object Time {
    var Fps: Double = 0.0
    var Delta: Double = 0.0
}