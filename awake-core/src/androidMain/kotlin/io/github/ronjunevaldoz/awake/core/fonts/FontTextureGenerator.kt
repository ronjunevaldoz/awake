package io.github.ronjunevaldoz.awake.core.fonts

import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.graphics.PorterDuff
import android.graphics.Typeface
import android.text.Layout
import android.text.StaticLayout
import android.text.TextPaint
import android.text.TextUtils
import io.github.ronjunevaldoz.awake.core.graphics.AndroidBitmap
import io.github.ronjunevaldoz.awake.core.graphics.NativeBitmap
import io.github.ronjunevaldoz.awake.core.graphics.NativeBitmapConfig
import io.github.ronjunevaldoz.awake.core.rendering.Texture

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