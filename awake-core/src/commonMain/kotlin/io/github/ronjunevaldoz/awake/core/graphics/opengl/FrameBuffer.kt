package io.github.ronjunevaldoz.awake.core.graphics.opengl

import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.memory.ByteBuf
import io.github.ronjunevaldoz.awake.core.utils.BufferUtils

class Framebuffer(private val width: Int, private val height: Int) : Disposable {
    private var framebuffer: Int = 0
    private var texture: Int = 0
    private var renderbuffer: Int = 0

    init {
        createFramebuffer()
    }

    private fun createFramebuffer() {
        // Create and bind the framebuffer
        framebuffer = gl.genFrameBuffers()
        gl.bindFramebuffer(Constants.GL_FRAMEBUFFER, framebuffer)

        // Create a texture for rendering
        texture = gl.genTextures()
        gl.bindTexture(Constants.GL_TEXTURE_2D, texture)
        gl.texImage2D(
            Constants.GL_TEXTURE_2D,
            0,
            Constants.GL_RGBA,
            width,
            height,
            0,
            Constants.GL_RGBA8,
            Constants.GL_UNSIGNED_BYTE,
            null
        )
        gl.texParameteri(
            Constants.GL_TEXTURE_2D,
            Constants.GL_TEXTURE_MIN_FILTER,
            Constants.GL_LINEAR
        )
        gl.texParameteri(
            Constants.GL_TEXTURE_2D,
            Constants.GL_TEXTURE_MAG_FILTER,
            Constants.GL_LINEAR
        )
        gl.bindTexture(Constants.GL_TEXTURE_2D, 0)
        gl.framebufferTexture2D(
            Constants.GL_FRAMEBUFFER,
            Constants.GL_COLOR_ATTACHMENT0,
            Constants.GL_TEXTURE_2D,
            texture,
            0
        )

        // Create a renderBuffer for depth and stencil
        renderbuffer = gl.genRenderBuffers()
        gl.bindRenderBuffers(Constants.GL_RENDERBUFFER, renderbuffer)
        gl.renderBufferStorage(
            Constants.GL_RENDERBUFFER,
            Constants.GL_DEPTH24_STENCIL8,
            width,
            height
        )
        gl.framebufferRenderBuffer(
            Constants.GL_FRAMEBUFFER,
            Constants.GL_DEPTH_STENCIL_ATTACHMENT,
            Constants.GL_RENDERBUFFER,
            renderbuffer
        )

        // Check if the frameBuffer is complete
        val status = gl.checkFramebufferStatus(Constants.GL_FRAMEBUFFER)
        check(status == Constants.GL_FRAMEBUFFER_COMPLETE) {
            "Framebuffer is not complete!"
        }

        // Unbind the framebuffer
        gl.bindFramebuffer(Constants.GL_FRAMEBUFFER, 0)
    }

    fun bind() {
        gl.bindFramebuffer(Constants.GL_FRAMEBUFFER, framebuffer)
    }

    fun unbind() {
        gl.bindFramebuffer(Constants.GL_FRAMEBUFFER, 0)
    }

    fun getPixelBuffer(): ByteBuf {
        val pixelBuffer = BufferUtils.byteBuffer(width * height * 4)
        use {
            gl.readPixels(
                0,
                0,
                width,
                height,
                Constants.GL_RGBA,
                Constants.GL_UNSIGNED_BYTE,
                pixelBuffer
            )
        }
        return pixelBuffer
    }

    fun delete() {
        // Release resources
        gl.deleteFrameBuffers(framebuffer)
        gl.deleteTextures(texture)
        gl.deleteRenderBuffers(renderbuffer)
    }

    override fun dispose() {
        delete()
    }
}

fun Framebuffer.use(frame: Framebuffer.() -> Unit) {
    bind()
    frame()
    unbind()
}