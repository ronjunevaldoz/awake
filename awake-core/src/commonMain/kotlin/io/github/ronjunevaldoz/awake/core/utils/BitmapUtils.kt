package io.github.ronjunevaldoz.awake.core.utils

import io.github.ronjunevaldoz.awake.core.graphics.image.Bitmap
import io.github.ronjunevaldoz.awake.core.graphics.image.createBitmap

object BitmapUtils {
    fun decode(bytes: ByteArray): Bitmap = createBitmap(bytes)
}