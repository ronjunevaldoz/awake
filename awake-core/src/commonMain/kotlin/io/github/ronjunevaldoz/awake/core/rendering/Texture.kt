package io.github.ronjunevaldoz.awake.core.rendering

import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants

fun Int.toFormat(): Int {
    return when (this) {
        Constants.GL_RED, Constants.GL_R8, Constants.GL_R16F, Constants.GL_R32F -> Constants.GL_RED
        Constants.GL_RG, Constants.GL_RG8, Constants.GL_RG16F, Constants.GL_RG32F -> Constants.GL_RG
        Constants.GL_RGB, Constants.GL_RGB8, Constants.GL_RGB16F, Constants.GL_RGB32F -> Constants.GL_RGB
        Constants.GL_RGBA, Constants.GL_RGBA8, Constants.GL_RGBA16F, Constants.GL_RGBA32F -> Constants.GL_RGBA
        else -> throw IllegalArgumentException("Unsupported internal format: $this")
    }
}

class Texture(
    val width: Int,
    val height: Int,
    private val internalFormat: Int = Constants.GL_RGBA8
) : BufferObject {
    override var id: Int = -1

    override fun create() {
        id = AwakeContext.gl.genTextures()
        bind()
        AwakeContext.gl.texImage2D(
            Constants.GL_TEXTURE_2D,
            0,
            internalFormat,
            width,
            height,
            0,
            internalFormat.toFormat(),
            Constants.GL_UNSIGNED_BYTE,
            null
        )
        AwakeContext.gl.texParameteri(
            Constants.GL_TEXTURE_2D,
            Constants.GL_TEXTURE_MIN_FILTER,
            Constants.GL_LINEAR
        )
        AwakeContext.gl.texParameteri(
            Constants.GL_TEXTURE_2D,
            Constants.GL_TEXTURE_MAG_FILTER,
            Constants.GL_LINEAR
        )
        unbind()
    }

    override fun bind() {
        AwakeContext.gl.bindTexture(Constants.GL_TEXTURE_2D, id)
    }

    override fun unbind() {
        AwakeContext.gl.bindTexture(Constants.GL_TEXTURE_2D, 0)
    }

    override fun delete() {
        AwakeContext.gl.deleteTextures(id)
    }

}