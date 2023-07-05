package scene

import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.graphics.Drawable
import io.github.ronjunevaldoz.awake.core.graphics.SimpleShader
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants.GL_FLOAT
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants.GL_TEXTURE0
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants.GL_TEXTURE_2D
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants.GL_UNSIGNED_BYTE
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL
import io.github.ronjunevaldoz.awake.core.graphics.use
import io.github.ronjunevaldoz.awake.core.isMobile
import io.github.ronjunevaldoz.awake.core.utils.AssetUtils
import io.github.ronjunevaldoz.awake.core.utils.BufferUtils


class Attribute(val location: Int, val data: FloatArray, val size: Int)

class Texture : Drawable, Disposable {
    private val shader = SimpleShader(
        vertFile = if (isMobile) "text.mobile.vert" else "text.vert",
        fragFile = if (isMobile) "text.mobile.frag" else "text.frag"
    )

    private val aPosition by lazy { shader.position }
    private val aColor by lazy { shader.color }
    private val aTexCoords by lazy { shader.texCoords }

    private var vao = -1
    private var vbo = -1
    private var ebo = -1

    private val attributes: List<Attribute>
    private val indices = byteArrayOf(
        0, 1, 2, // first triangle
        0, 3, 2  // second triangle
    )

    init {
        shader.compile()
        AssetUtils.loadTexture(textureKey, "assets/fonts/calibri.png")
        attributes = listOf(
            Attribute(
                aPosition, floatArrayOf(
                    0.5f, 0.5f, 0.0f,
                    0.5f, -0.5f, 0.0f,
                    -0.5f, -0.5f, 0.0f,
                    -0.5f, 0.5f, 0.0f
                ), 3
            ),
            Attribute(
                aColor, floatArrayOf(
                    1.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 1.0f,
                    1.0f, 1.0f, 0.0f
                ), 3
            ),
            Attribute(
                aTexCoords, floatArrayOf(
                    1.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 1.0f
                ), 2
            )
        )
        createBuffers()
    }

    private fun createBuffers() {
        // VAO
        vao = gl.genVertexArrays()
        gl.bindVertexArray(vao)

        // VBO
        vbo = gl.genBuffers()
        gl.bindBuffer(OpenGL.BufferType.Array, vbo)
        val numComponents =
            8 * Float.SIZE_BYTES // total number of components (3 position, 3 color, 2 uv)
        val vertices = mutableListOf<Float>()
        for (attribute in attributes) {
            vertices.addAll(attribute.data.toList())
        }
        val bufferSize = vertices.size * numComponents
        val buffer = BufferUtils.floatBuffer(bufferSize)
        buffer.put(vertices.toFloatArray())

        gl.bufferData(
            OpenGL.BufferType.Array,
            bufferSize.toLong(),
            buffer,
            OpenGL.DrawType.Static
        )
        var offset = 0
        for (attribute in attributes) {
            gl.enableVertexAttribArray(attribute.location)
            // stride is ignore if using attribute class
            gl.vertexAttribPointer(attribute.location, attribute.size, GL_FLOAT, false, 0, offset)
            offset += attribute.data.size * Float.SIZE_BYTES
        }
        // EBO
        ebo = gl.genBuffers()
        gl.bindBuffer(OpenGL.BufferType.ElementArray, ebo)
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
        // unbind VAO
        gl.bindVertexArray(0)
        // unbind VBO
        gl.bindBuffer(OpenGL.BufferType.Array, 0)
        // unbind EBO
        gl.bindBuffer(OpenGL.BufferType.ElementArray, 0)
        // disable attributes
        gl.disableVertexAttribArray(aPosition)
        gl.disableVertexAttribArray(aColor)
        gl.disableVertexAttribArray(aTexCoords)
    }

    override fun draw() {
        shader.use {
            gl.bindVertexArray(vao)

            gl.activeTexture(GL_TEXTURE0)
            gl.bindTexture(GL_TEXTURE_2D, AssetUtils.getTexture(textureKey))
            gl.drawElements(
                OpenGL.DrawMode.Triangles,
                indices.size,
                GL_UNSIGNED_BYTE,
                null
            )

            gl.bindTexture(GL_TEXTURE_2D, 0)
            gl.bindVertexArray(0)
        }
    }

    override fun dispose() {
        shader.delete()
        gl.deleteVertexArrays(vao)
        gl.deleteBuffers(vbo)
        gl.deleteBuffers(ebo)
        AssetUtils.removeTexture(textureKey)
    }

    companion object {
        const val textureKey = "texture"
    }
}