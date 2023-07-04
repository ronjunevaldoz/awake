package scene

import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.graphics.Drawable
import io.github.ronjunevaldoz.awake.core.graphics.SimpleShader
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL
import io.github.ronjunevaldoz.awake.core.graphics.use
import io.github.ronjunevaldoz.awake.core.isMobile
import io.github.ronjunevaldoz.awake.core.utils.BufferUtils


class ColoredTriangle : Drawable, Disposable {

    private val shader = SimpleShader(
        vertFile =  if(isMobile) "colored-triangle.mobile.vert" else "colored-triangle.vert",
        fragFile =  if(isMobile) "colored-triangle.mobile.frag" else "colored-triangle.frag"
    )

    val aPosition  by lazy { shader.position  }
    val aColor  by lazy { shader.color }


    data class Vertex(
        var x: Float,
        var y: Float,
        var z: Float,
        var r: Float,
        var g: Float,
        var b: Float,
        var a: Float,
    )

    val vertices = listOf(
        Vertex(x = 1f, y = -1f, z = 0f, r = 1f, g = 0f, b = 0f, a = 1f),
        Vertex(x = 1f, y = 1f, z = 0f, r = 0f, g = 1f, b = 0f, a = 1f),
        Vertex(x = -1f, y = 1f, z = 0f, r = 0f, g = 0f, b = 1f, a = 1f),
        Vertex(x = -1f, y = -1f, z = 0f, r = 0f, g = 0f, b = 0f, a = 1f),
    )
    val indices = byteArrayOf(
        0, 1, 2,
        2, 3, 0
    )

    val vao = BufferUtils.intBuffer(1)
    val vbo = BufferUtils.intBuffer(1)
    val ebo = BufferUtils.intBuffer(1)

    init {
        shader.compile()
        createBuffers()
    }

    private fun createBuffers() {
        val stride =
            7 * Float.SIZE_BYTES // Stride: 7 elements per vertex (3 for position, 4 for color), 4 bytes per element
        val colorOffset: Int =
            Float.SIZE_BYTES * 3 // Offset: Skip position (3 for position), 4 bytes  per element

        // VAO
        gl.genVertexArrays(1, vao)
        gl.bindVertexArray(vao[0])
        // VBO
        gl.genBuffers(1, vbo)
        gl.bindBuffer(OpenGL.BufferType.Array, vbo[0])
        val bufferSize = vertices.size * stride
        val buffer = BufferUtils.floatBuffer(bufferSize)
        for (i in vertices.indices) {
            val vertex = vertices[i]
            buffer[i * 7] = vertex.x
            buffer[i * 7 + 1] = vertex.y
            buffer[i * 7 + 2] = vertex.z
            buffer[i * 7 + 3] = vertex.r
            buffer[i * 7 + 4] = vertex.g
            buffer[i * 7 + 5] = vertex.b
            buffer[i * 7 + 6] = vertex.a
        }
        // set vertices
        gl.bufferData(
            OpenGL.BufferType.Array,
            bufferSize.toLong(),
            buffer,
            OpenGL.DrawType.Static
        )
        // Enable the vertex attributes

        // POSITION
        gl.enableVertexAttribArray(aPosition)
        gl.vertexAttribPointer(
            aPosition,
            3,// Number of components per vertex attribute (x, y, z)
            Constants.GL_FLOAT,
            false,
            stride,
            0
        )

        // COLOR
        gl.enableVertexAttribArray(aColor)
        gl.vertexAttribPointer(
            aColor,
            4,// Number of components per vertex attribute (r, g, b, a)
            Constants.GL_FLOAT,
            false,
            stride,
            colorOffset
        )
        // End VBO

        // EBO
        gl.genBuffers(1, ebo)
        gl.bindBuffer(OpenGL.BufferType.ElementArray, ebo[0])
        // fill buffer
        val indicesBuffer = BufferUtils.byteBuffer(indices.size)
        for (i in indices.indices) {
            indicesBuffer[i] = indices[i]
        }
        gl.bufferData(
            OpenGL.BufferType.ElementArray,
            indices.size.toLong(),
            indicesBuffer,
            OpenGL.DrawType.Static
        )
        gl.bindVertexArray(0)
        // End EBO

        gl.bindBuffer(OpenGL.BufferType.Array, 0)
        gl.bindBuffer(OpenGL.BufferType.ElementArray, 0)
    }

//    override fun dispose() {
//        // Disable the vertex attribute arrays
//        gl.disableVertexAttribArray(aPosition)
//        gl.disableVertexAttribArray(aColor)
//
//        // Delete the vertex array object (VAO)
//        gl.deleteVertexArrays(1, vao)
//
//        // Delete the vertex buffer object (VBO)
//        gl.deleteBuffers(1, vbo)
//
//        // Delete the element buffer object (EBO)
//        gl.deleteBuffers(1, ebo)
//
//        // Delete the shader program
//        gl.deleteProgram(program)
//        program = -1
//    }

    override fun draw() {
        shader.use {
            gl.bindVertexArray(vao[0])
            gl.drawElements(
                OpenGL.DrawMode.Triangles,
                indices.size,
                Constants.GL_UNSIGNED_BYTE,
                null
            )
            gl.bindVertexArray(0)
        }
    }

    override fun dispose() {
        shader.delete()
    }
}