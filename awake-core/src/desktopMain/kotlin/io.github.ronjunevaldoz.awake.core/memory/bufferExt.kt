package io.github.ronjunevaldoz.awake.core.memory

fun Buffer.`when`(
    byte: java.nio.ByteBuffer?.() -> Unit = {},
    short: java.nio.ShortBuffer?.() -> Unit = {},
    int: java.nio.IntBuffer?.() -> Unit = {},
    float: java.nio.FloatBuffer?.() -> Unit = {}
) {
    when (this) {
        is ByteBuffer -> byte(get())
        is ShortBuffer -> short(get())
        is IntBuffer -> int(get())
        is FloatBuffer -> float(get())
    }
}