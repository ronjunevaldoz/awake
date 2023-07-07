package io.github.ronjunevaldoz.awake.core.rendering

import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants
import io.github.ronjunevaldoz.awake.core.memory.ByteBuf
import io.github.ronjunevaldoz.awake.core.utils.BufferUtils


class FrameBufferObject(private val width: Int, private val height: Int) : BufferObject,
    Disposable {
    override var id: Int = -1
    private val texture = Texture(width, height)
    private val rbo = RenderBufferObject()

    override fun create() {
        // create buffer
        id = gl.genFrameBuffers()
        // bind framebuffer
        use {
            // Create a texture for rendering
            texture.create()
            // store texture to frame buffer
            gl.framebufferTexture2D(
                Constants.GL_FRAMEBUFFER,
                Constants.GL_COLOR_ATTACHMENT0,
                Constants.GL_TEXTURE_2D,
                texture.id,
                0
            )
            // Create a renderBuffer for depth and stencil
            rbo.create()
            rbo.bind()
            rbo.storeData(width, height)
            // Check if the frameBuffer is complete
            checkComplete()
        }
        // Unbind the framebuffer
    }

    override fun bind() {
        gl.bindFramebuffer(Constants.GL_FRAMEBUFFER, id)
    }

    override fun unbind() {
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

    override fun delete() {
        // Release resources
        gl.deleteFrameBuffers(id)
        rbo.delete()
    }

    override fun dispose() {
        delete()
    }

    private fun checkComplete() {
        val status = gl.checkFramebufferStatus(Constants.GL_FRAMEBUFFER)
        check(status == Constants.GL_FRAMEBUFFER_COMPLETE) {
            "Framebuffer is not complete!"
        }
    }
}