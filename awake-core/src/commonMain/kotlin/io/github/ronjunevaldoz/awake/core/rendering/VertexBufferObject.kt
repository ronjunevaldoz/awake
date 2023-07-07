package io.github.ronjunevaldoz.awake.core.rendering

import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL
import io.github.ronjunevaldoz.awake.core.utils.BufferUtils

class VertexBufferObject(val data: VertexBufferData) : BufferObject {
    override var id: Int = -1

    override fun create() {
        id = AwakeContext.gl.genBuffers()
    }

    override fun bind() {
        AwakeContext.gl.bindBuffer(OpenGL.BufferType.Array, id)
    }

    override fun unbind() {
        AwakeContext.gl.bindBuffer(OpenGL.BufferType.Array, 0)
    }

    fun enableAttribute() {
        AwakeContext.gl.enableVertexAttribArray(data.index)
    }

    fun disableAttribute() {
        AwakeContext.gl.disableVertexAttribArray(data.index)
    }

    fun storeData() {
        with(data) {
            val stride = size * Float.SIZE_BYTES
            // TODO investigate why do I need to use stride here???
            val bufferSize = data.size * stride
            val buffer = BufferUtils.floatBuffer(bufferSize)
            buffer.put(data.toFloatArray())
            AwakeContext.gl.bufferData(
                OpenGL.BufferType.Array,
                bufferSize.toLong(),
                buffer,
                OpenGL.DrawType.Static
            )
            AwakeContext.gl.vertexAttribPointer(
                index,
                size,
                Constants.GL_FLOAT,
                false,
                stride,
                offset
            )
        }
    }

    override fun delete() {
        AwakeContext.gl.deleteBuffers(id)
    }
}