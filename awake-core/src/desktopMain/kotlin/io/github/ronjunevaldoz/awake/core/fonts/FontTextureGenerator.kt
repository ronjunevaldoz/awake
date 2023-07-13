package io.github.ronjunevaldoz.awake.core.fonts

import io.github.ronjunevaldoz.awake.core.graphics.Bitmap
import io.github.ronjunevaldoz.awake.core.graphics.DesktopBitmap
import io.github.ronjunevaldoz.awake.core.rendering.Texture
import org.jetbrains.skia.Color
import org.jetbrains.skia.Font
import org.jetbrains.skia.Paint
import org.jetbrains.skia.Pixmap
import org.jetbrains.skia.Surface
import org.jetbrains.skia.Typeface

object FontTextureGenerator {
    private var texture: Texture? = null

    // skia
    private val paint = Paint()
    private val typeFace = Typeface.makeDefault()
    private val font = Font(typeFace, 14f)
    private val pixmap = Pixmap()

    private fun createCharBitmap(font: Font, c: Char, antiAlias: Boolean): Bitmap {
        // Get character width and height
        val charWidth = font.measureTextWidth(c.toString())
        val charHeight = font.size

        // Check if charWidth is 0
        require(charWidth > 0f) { "Invalid character width" }

        // Create surface for holding the character
        val charSurface = Surface.makeRasterN32Premul(charWidth.toInt(), charHeight.toInt())
        val charCanvas = charSurface.canvas

        charCanvas.clear(Color.TRANSPARENT)

        paint.reset()
        if (antiAlias) {
            paint.isAntiAlias = true
        }
        paint.color = Color.WHITE

        charCanvas.drawString(c.toString(), 0f, charHeight, font, paint)
        val pixels = getPixels(charSurface)

        val width = charSurface.width
        val height = charSurface.height
        return DesktopBitmap(width, height, 4, pixels)
    }

    private fun getPixels(surface: Surface): IntArray {
        pixmap.reset()
        val width = surface.width
        val height = surface.height
        surface.peekPixels(pixmap)
        val pixels = IntArray(width * height)
        for (y in 0 until height) {
            for (x in 0 until width) {
                val argb = pixmap.getColor(x, y)
                val alpha = (argb shr 24) and 0xFF
                val red = (argb shr 16) and 0xFF
                val green = (argb shr 8) and 0xFF
                val blue = argb and 0xFF
                val pixel = (alpha shl 24) or (red shl 16) or (green shl 8) or blue
                pixels[y * width + x] = pixel
            }
        }
        return pixels
    }

    fun create(text: String, fontSize: Float): Texture {
        val characterBitmap = createCharBitmap(font, 'x', true)

        texture = Texture.load(
            bitmap = characterBitmap,
            options = Texture.Options(
                mag = Texture.Filter.Linear,
                min = Texture.Filter.MipmapLinear,
                wrapS = Texture.Wrap.ClampToEdge,
                wrapT = Texture.Wrap.ClampToEdge
            ),
            mipmap = true
        )

        return texture!!
    }
}