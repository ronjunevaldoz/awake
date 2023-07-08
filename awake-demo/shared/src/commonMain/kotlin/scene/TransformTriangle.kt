package scene

import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.geometry.Attribute
import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.graphics.Drawable
import io.github.ronjunevaldoz.awake.core.graphics.opengl.CommonGL
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL
import io.github.ronjunevaldoz.awake.core.math.Matrix4f
import io.github.ronjunevaldoz.awake.core.math.degreesToRadians
import io.github.ronjunevaldoz.awake.core.math.translateAndRotate
import io.github.ronjunevaldoz.awake.core.rendering.VertexArrayObject
import io.github.ronjunevaldoz.awake.core.rendering.addIndexBuffer
import io.github.ronjunevaldoz.awake.core.rendering.addVertexBuffer
import io.github.ronjunevaldoz.awake.core.rendering.createVAO
import io.github.ronjunevaldoz.awake.core.rendering.use
import io.github.ronjunevaldoz.awake.core.shader.SimpleShader
import io.github.ronjunevaldoz.awake.core.shader.use

class TransformTriangle : Drawable, Disposable {

    private val shader = SimpleShader(
        vertFile = "transform.vert",
        fragFile = "transform.frag"
    )

    private val aPosition by lazy { shader.position }
    private val aColor by lazy { shader.color }
    private val attributes by lazy {
        listOf(
            Attribute(
                aPosition, floatArrayOf(
                    1f, -1f, 0f,
                    1f, 1f, 0f,
                    -1f, 1f, 0f,
                    -1f, -1f, 0f
                ), 3
            ),
            Attribute(
                aColor, floatArrayOf(
                    1f, 0f, 0f, 1f,
                    0f, 1f, 0f, 1f,
                    0f, 0f, 1f, 1f,
                    0f, 0f, 0f, 1f,
                ), 4
            ),
        )
    }

    private val indices = byteArrayOf(
        0, 1, 2,
        2, 3, 0
    )
    private lateinit var vao: VertexArrayObject

    init {
        shader.compile()
        shader.use {
            val angleInDegrees = 45.0f
            val angleInRadians = degreesToRadians(angleInDegrees)
            shader.transformMatrix =
                Matrix4f().apply { translateAndRotate(1f, 1f, 1f, angleInRadians) }
            println(shader.transformMatrix)
        }
        createBuffers()
    }

    override fun draw() {
        shader.use {
            vao.use {
                AwakeContext.gl.drawElements(
                    OpenGL.DrawMode.Triangles,
                    indices.size,
                    CommonGL.GL_UNSIGNED_BYTE,
                    null
                )
            }
        }
    }

    override fun dispose() {
        shader.delete()
        vao.delete()
    }


    private fun createBuffers() {
        vao = createVAO {
            addIndexBuffer(indices)
            attributes.forEach(::addVertexBuffer)
        }
    }
}