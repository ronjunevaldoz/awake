package io.github.ronjunevaldoz.awake.core.graphics.image


import android.graphics.BitmapFactory
import android.graphics.Matrix

class AndroidBitmap(
    override val width: Int,
    override val height: Int,
    override val channel: Int,
    override val pixels: IntArray
) : Bitmap

actual fun createBitmap(bytes: ByteArray): Bitmap {
    val matrix = Matrix()
    val bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.size, BitmapFactory.Options())
        .let { bitmap ->
            matrix.reset()
            // flip y axis
            matrix.postScale(1f, -1f)
            android.graphics.Bitmap.createBitmap(
                bitmap,
                0,
                0,
                bitmap.width,
                bitmap.height,
                matrix,
                true
            )
        }

    val width = bitmap.width
    val height = bitmap.height
    val pixels = IntArray(width * height)
    bitmap.getPixels(pixels, 0, width, 0, 0, width, height)
    bitmap.recycle()
    return AndroidBitmap(
        width = bitmap.width,
        height = bitmap.height,
        channel = 4,
        pixels = pixels
    )
}