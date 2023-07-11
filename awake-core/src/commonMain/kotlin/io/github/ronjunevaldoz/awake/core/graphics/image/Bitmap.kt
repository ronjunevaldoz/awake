package io.github.ronjunevaldoz.awake.core.graphics.image

import io.github.ronjunevaldoz.awake.core.rendering.Texture

interface Bitmap {
    val width: Int
    val height: Int
    val channel: Int
    val pixels: IntArray
}

expect fun createBitmap(bytes: ByteArray): Bitmap
expect fun createTextTexture(
    aText: String,
    aFontSize: Float
): Texture