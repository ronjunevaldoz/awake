package io.github.ronjunevaldoz.awake.core.rendering

import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants

class RenderBufferObject : BufferObject {
    override var id: Int = -1

    override fun create() {
        id = AwakeContext.gl.genRenderBuffers()
    }

    override fun bind() {
        AwakeContext.gl.bindRenderBuffers(Constants.GL_RENDERBUFFER, id)
    }

    fun storeData(width: Int, height: Int) {
        AwakeContext.gl.renderBufferStorage(
            Constants.GL_RENDERBUFFER,
            Constants.GL_DEPTH24_STENCIL8,
            width,
            height
        )
        AwakeContext.gl.framebufferRenderBuffer(
            Constants.GL_FRAMEBUFFER,
            Constants.GL_DEPTH_STENCIL_ATTACHMENT,
            Constants.GL_RENDERBUFFER,
            id
        )
    }

    override fun unbind() {
        AwakeContext.gl.bindRenderBuffers(Constants.GL_RENDERBUFFER, 0)
    }

    override fun delete() {
        AwakeContext.gl.deleteRenderBuffers(id)
    }

}