package io.github.ronjunevaldoz.awake.core.graphics

interface Renderer {
    fun create()
    fun update(delta: Float)
    fun pause()
    fun resume()
    fun resize(x: Int, y: Int, width: Int, height: Int)
    fun dispose()
}