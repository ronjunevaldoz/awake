package io.github.ronjunevaldoz.awake.core.graphics

import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL

data class Config(
    var debug: Boolean = true,
    var fps : Int = 60,
    var glVersion : OpenGL.Version = OpenGL.Version.ES3,
)