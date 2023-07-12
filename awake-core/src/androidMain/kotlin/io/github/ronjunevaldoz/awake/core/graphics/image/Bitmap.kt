package io.github.ronjunevaldoz.awake.core.graphics.image


import android.graphics.BitmapFactory
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Matrix
import android.graphics.Paint
import android.graphics.PorterDuff
import android.graphics.Typeface
import android.text.Layout
import android.text.StaticLayout
import android.text.TextPaint
import android.text.TextUtils
import io.github.ronjunevaldoz.awake.core.rendering.Texture

typealias NativeBitmap = android.graphics.Bitmap
typealias NativeBitmapConfig = android.graphics.Bitmap.Config

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
            NativeBitmap.createBitmap(
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

object FontTextureGenerator {
    private val textPaint = TextPaint()
    private val canvas = Canvas()
    private var texture: Texture? = null

    fun create(
        aText: String,
        aFontSize: Float
    ): Texture {
        textPaint.apply {
            typeface = Typeface.SERIF
            textSize = aFontSize.coerceIn(8.0f, 500.0f)
            isAntiAlias = true
            color = Color.WHITE
            hinting = Paint.HINTING_ON
            isSubpixelText = true
        }

        val width = (textPaint.measureText(aText) + 2.0f).toInt()
        val height = aFontSize.toInt() + 2

        val staticLayout = StaticLayout.Builder.obtain(aText, 0, aText.length, textPaint, width)
            .setAlignment(Layout.Alignment.ALIGN_NORMAL)
            .setLineSpacing(0f, 1f)
            .setEllipsize(TextUtils.TruncateAt.END)
            .setIncludePad(false)
            .build()

        val bitmap = NativeBitmap.createBitmap(
            width,
            height,
            NativeBitmapConfig.ARGB_8888
        )

        canvas.setBitmap(bitmap)
        canvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR)
        staticLayout.draw(canvas)

        val pixels = IntArray(width * height)
        bitmap.getPixels(pixels, 0, width, 0, 0, width, height)
        val androidBitmap = AndroidBitmap(width, height, 4, pixels)
        texture = Texture.load(
            bitmap = androidBitmap,
            options = Texture.Options(
                mag = Texture.Filter.Linear,
                min = Texture.Filter.MipmapLinear,
                wrapS = Texture.Wrap.ClampToEdge,
                wrapT = Texture.Wrap.ClampToEdge
            ),
            mipmap = true
        )
        bitmap.recycle()
        return texture!!
    }
}

actual fun createTextTexture(
    aText: String,
    aFontSize: Float
): Texture {
    return FontTextureGenerator.create(aText, aFontSize)
}