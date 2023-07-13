package scene

import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.geometry.Attribute
import io.github.ronjunevaldoz.awake.core.getPlatform
import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.graphics.Drawable
import io.github.ronjunevaldoz.awake.core.graphics.createTextTexture
import io.github.ronjunevaldoz.awake.core.graphics.opengl.CommonGL
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL
import io.github.ronjunevaldoz.awake.core.math.Mat4
import io.github.ronjunevaldoz.awake.core.math.Vec3
import io.github.ronjunevaldoz.awake.core.math.Vec4
import io.github.ronjunevaldoz.awake.core.math.times
import io.github.ronjunevaldoz.awake.core.rendering.Texture
import io.github.ronjunevaldoz.awake.core.rendering.VertexArrayObject
import io.github.ronjunevaldoz.awake.core.rendering.addIndexBuffer
import io.github.ronjunevaldoz.awake.core.rendering.addVertexBuffer
import io.github.ronjunevaldoz.awake.core.rendering.createVAO
import io.github.ronjunevaldoz.awake.core.rendering.use
import io.github.ronjunevaldoz.awake.core.shader.SimpleShader
import io.github.ronjunevaldoz.awake.core.shader.use
import io.github.ronjunevaldoz.awake.core.utils.Frame
import io.github.ronjunevaldoz.awake.core.utils.Time

class TextSample : Drawable, Disposable {

    private val shader = SimpleShader(
        vertFile = "fonttext.vert",
        fragFile = "fonttext.frag",
        define = if (getPlatform().isMobile) "#version 300 es\n" else "#version 330 core\n"
    )

    private val aPosition by lazy { shader.position }
    private val aTexCoords by lazy { shader.texCoords }
    private val aColor by lazy { shader.color }

    private var attributes: List<Attribute> = emptyList()
    private lateinit var vao: VertexArrayObject
    private var fontTexture: Texture? = null

    private var mvp = Mat4()
    private var isUpdateNeeded = true
    private var totalElapsedTime = 0f

    private var updateCamera = true
    private val indices = byteArrayOf(
        0, 2, 1, // first triangle
        1, 3, 2,  // second triangle
    )

    init {
        shader.compile()
        createBuffers()
    }

    override fun draw() {
        updateCamera()
        totalElapsedTime += Time.Delta.toFloat()
        if (totalElapsedTime >= 0.25f) {
            calculateTexCoordinates(mvp, Frame.width, Frame.height)
            totalElapsedTime = 0f
        }
        shader.use {
            fontTexture?.let { texture ->
                vao.use {
                    gl.disable(CommonGL.GL_CULL_FACE)
                    gl.enable(CommonGL.GL_BLEND)
                    gl.blendFunc(CommonGL.GL_ONE, CommonGL.GL_ONE_MINUS_SRC_ALPHA)
                    gl.activeTexture(CommonGL.GL_TEXTURE0)
                    texture.use {
                        gl.drawElements(
                            OpenGL.DrawMode.Triangles,
                            indices.size,
                            CommonGL.GL_UNSIGNED_BYTE,
                            null
                        )
                    }
                }
            }
        }
    }

    override fun dispose() {
        shader.delete()
        vao.delete()
    }

    private fun updateCamera() {
        if (updateCamera) {
            shader.use {
                if (Frame.width > 0 && Frame.height > 0) {
                    val width = Frame.width.toFloat()
                    val height = Frame.height.toFloat()
//                    val ratio = width / height
//                    val projection = Mat4f.frustum(-ratio, ratio, -1f, 1f, 0.1f, 100.0f)

                    val projection = Mat4.orthographic(
                        -1f, 1f, -1f, 1f, -1f, 20f
//                        left = 0f,
//                        right = width,
//                        bottom = 0f,
//                        top =  height,
//                        near = 0.1f,
//                        far = 100f
                    )
                    val textPosition = Vec3(0f, 0f, 0f)  // Position of the text
                    val textScale = 10f  // Dynamic font size

                    val eye = Vec3(textPosition.x, textPosition.y, 0f)  // Camera position
                    val center = Vec3(textPosition.x, textPosition.y, 0f)  // Target position

                    // Adjust the camera position based on the font size
                    eye.z += textScale

                    val viewMatrix = Mat4.setLookAt(
                        eye,
                        center,
                        Vec3.UP
                    )
                    shader.projectionViewMatrix = viewMatrix * projection
                    val modelMatrix = Mat4()
                        .translate(0f, 0f, 0f)
                        .apply {
                            if (fontTexture != null) {
//                                scale(
//                                    (fontTexture!!.width.toFloat() / fontTexture!!.height.toFloat()),
//                                    1f,
//                                    1f
//                                )
                            }
                        }
                    shader.modelViewMatrix = modelMatrix
                    mvp = projection * modelMatrix
                }
            }
            updateCamera = false
        }
    }

    private fun calculateTexCoordinates(
        transMatrix: Mat4,
        viewportWidth: Int,
        viewportHeight: Int
    ) {
//        if (!isUpdateNeeded) return
        // Calculate bounding box in screen coordinates with current matrices
        val rectangleLT = Vec4(-0.5f, -0.5f, 0.0f, 1.0f)
        val rectangleLB = Vec4(-0.5f, 0.5f, 0.0f, 1.0f)
        val rectangleRT = Vec4(0.5f, -0.5f, 0.0f, 1.0f)
        val rectangleRB = Vec4(0.5f, 0.5f, 0.0f, 1.0f)

//        val clipCoordsLT = transMatrix.transformPosition(rectangleLT)
//        val clipCoordsLB = transMatrix.transformPosition(rectangleLB)
//        val clipCoordsRT = transMatrix.transformPosition(rectangleRT)
//        val clipCoordsRB = transMatrix.transformPosition(rectangleRB)

        rectangleLT.makePixelCoords(viewportWidth, viewportHeight)
        rectangleLB.makePixelCoords(viewportWidth, viewportHeight)
        rectangleRT.makePixelCoords(viewportWidth, viewportHeight)
        rectangleRB.makePixelCoords(viewportWidth, viewportHeight)

        // 2. Evaluate font size based on the height of bounding box corners
        val vl = rectangleLB - rectangleLT
        val vr = rectangleRB - rectangleRT
        val textSize = (vl.length3() + vr.length3()) / 2.0f

        fontTexture = createTextTexture(Time.FpsString, textSize)
        isUpdateNeeded = false
    }


    private fun createBuffers() {
        attributes = listOf(
            Attribute(
                aPosition, floatArrayOf(
                    -0.5f, -0.5f, 0f,
                    -0.5f, 0.5f, 0f,
                    0.5f, -0.5f, 0f,
                    0.5f, 0.5f, 0f,
                ), 3
            ),
            Attribute(
                aTexCoords, floatArrayOf(
                    0.0f, 1.0f,
                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f,
                ), 2
            ),
            Attribute(
                aColor, floatArrayOf(
                    1f, 1f, 1f,
                    1f, 1f, 1f,
                    1f, 1f, 1f,
                    1f, 1f, 1f,
                ), 3
            ),
        )
        vao = createVAO {
            addIndexBuffer(indices)
            attributes.forEach(::addVertexBuffer)
        }
    }
}