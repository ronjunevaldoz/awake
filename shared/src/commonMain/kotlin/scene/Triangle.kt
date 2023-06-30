package scene

import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.graphics.Drawable
import io.github.ronjunevaldoz.awake.core.graphics.SimpleShader
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants.GL_TRIANGLES
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL
import io.github.ronjunevaldoz.awake.core.graphics.use
import io.github.ronjunevaldoz.awake.core.isMobile
import io.github.ronjunevaldoz.awake.core.utils.BufferUtils

class Triangle : Drawable, Disposable {
    private val shader = SimpleShader(
        vertFile = if (isMobile) "triangle.mobile.vert" else "triangle.vert",
        fragFile = if (isMobile) "triangle.mobile.frag" else "triangle.frag"
    )

    val aPosition by lazy { shader.position }

    var triangleVertices = floatArrayOf(
        0.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f
    )

    val vao = BufferUtils.intBuffer(1)
    val vbo = BufferUtils.intBuffer(1)

    init {
        shader.compile()
        createBuffers()
    }

    override fun dispose() {
        // Disable the vertex attribute arrays
        gl.disableVertexAttribArray(aPosition)
        // Delete the shader program
        shader.delete()
    }

    override fun draw() {
        shader.use {
            gl.bindVertexArray(vao[0])
            gl.drawArrays(
                GL_TRIANGLES,
                0,
                3
            )
        }
    }

    private fun createBuffers() {
        // VAO
        gl.genVertexArrays(1, vao)
        gl.bindVertexArray(vao[0])
        // VBO
        gl.genBuffers(1, vbo)
        gl.bindBuffer(OpenGL.BufferType.Array, vbo[0])
        val stride = 2 * Float.SIZE_BYTES // total component num
        val bufferSize = triangleVertices.size * stride
        val buffer = BufferUtils.floatBuffer(bufferSize)
        for (i in triangleVertices.indices) {
            val vertex = triangleVertices[i]
            buffer[i] = vertex
        }
        // set vertices
        gl.bufferData(
            OpenGL.BufferType.Array,
            bufferSize.toLong(),
            buffer,
            OpenGL.DrawType.Static
        )
        // Enable attribute position
        gl.enableVertexAttribArray(aPosition)
        gl.vertexAttribPointer(
            aPosition,
            2,// Number of components per vertex attribute (x, y, z)
            Constants.GL_FLOAT,
            false,
            stride,
            0
        )

        // clear
        gl.bindVertexArray(0)
        gl.bindBuffer(OpenGL.BufferType.Array, 0)
    }
}