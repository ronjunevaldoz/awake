package io.github.ronjunevaldoz.awake.core.graphics

import io.github.ronjunevaldoz.awake.core.fonts.FontTextureGenerator
import io.github.ronjunevaldoz.awake.core.rendering.Texture

actual fun createTextTexture(
    aText: String,
    aFontSize: Float
): Texture {
    return FontTextureGenerator.create(aText, aFontSize)
}