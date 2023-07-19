package io.github.ronjunevaldoz.awake.core.fonts

import io.github.ronjunevaldoz.awake.core.rendering.Texture


class NativeTrueType(filePath: String, fontSize: Float) : TrueType {
    override val texture: Texture

    override fun drawText(text: String) {
        TODO("Not yet implemented")
    }

    override fun dispose() {
        TODO("Not yet implemented")
    }

    init {
        val fontBitmap = FontBitmap(30f, true)
        texture = Texture.load(fontBitmap.bitmap)
    }
}

actual fun createTrueType(path: String, size: Float): TrueType {
    return NativeTrueType(path, size)
}