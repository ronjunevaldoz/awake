package io.github.ronjunevaldoz.awake.core.rendering

import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.graphics.opengl.CommonGL

fun Int.toFormat(): Int {
    return when (this) {
        CommonGL.GL_RED, CommonGL.GL_R8, CommonGL.GL_R16F, CommonGL.GL_R32F -> CommonGL.GL_RED
        CommonGL.GL_RG, CommonGL.GL_RG8, CommonGL.GL_RG16F, CommonGL.GL_RG32F -> CommonGL.GL_RG
        CommonGL.GL_RGB, CommonGL.GL_RGB8, CommonGL.GL_RGB16F, CommonGL.GL_RGB32F -> CommonGL.GL_RGB
        CommonGL.GL_RGBA, CommonGL.GL_RGBA8, CommonGL.GL_RGBA16F, CommonGL.GL_RGBA32F -> CommonGL.GL_RGBA
        else -> throw IllegalArgumentException("Unsupported internal format: $this")
    }
}

class Texture(
    val width: Int,
    val height: Int,
    private val internalFormat: Int = CommonGL.GL_RGBA8
) : BufferObject {
    override var id: Int = -1

    override fun create() {
        id = AwakeContext.gl.genTextures()
        bind()
        AwakeContext.gl.texImage2D(
            CommonGL.GL_TEXTURE_2D,
            0,
            internalFormat,
            width,
            height,
            0,
            internalFormat.toFormat(),
            CommonGL.GL_UNSIGNED_BYTE,
            null
        )
        AwakeContext.gl.texParameteri(
            CommonGL.GL_TEXTURE_2D,
            CommonGL.GL_TEXTURE_MIN_FILTER,
            CommonGL.GL_LINEAR
        )
        AwakeContext.gl.texParameteri(
            CommonGL.GL_TEXTURE_2D,
            CommonGL.GL_TEXTURE_MAG_FILTER,
            CommonGL.GL_LINEAR
        )
        unbind()
    }

    override fun bind() {
        AwakeContext.gl.bindTexture(CommonGL.GL_TEXTURE_2D, id)
    }

    override fun unbind() {
        AwakeContext.gl.bindTexture(CommonGL.GL_TEXTURE_2D, 0)
    }

    override fun delete() {
        AwakeContext.gl.deleteTextures(id)
    }

}