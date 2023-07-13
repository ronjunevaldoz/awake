package io.github.ronjunevaldoz.awake.core.graphics

import io.github.ronjunevaldoz.awake.core.rendering.Texture

expect fun createTextTexture(
    aText: String,
    aFontSize: Float
): Texture