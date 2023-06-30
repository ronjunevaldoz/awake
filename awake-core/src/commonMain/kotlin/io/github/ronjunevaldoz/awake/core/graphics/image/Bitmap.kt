package io.github.ronjunevaldoz.awake.core.graphics.image

interface Bitmap {
    val width: Int
    val height: Int
    val channel: Int
    val pixels: IntArray
}

expect fun createBitmap(bytes: ByteArray) : Bitmap