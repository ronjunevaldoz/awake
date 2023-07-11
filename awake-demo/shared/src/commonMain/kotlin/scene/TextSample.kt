package scene

import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.geometry.Attribute
import io.github.ronjunevaldoz.awake.core.getPlatform
import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.graphics.Drawable
import io.github.ronjunevaldoz.awake.core.graphics.image.createTextTexture
import io.github.ronjunevaldoz.awake.core.graphics.opengl.CommonGL
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL
import io.github.ronjunevaldoz.awake.core.math.Mat4f
import io.github.ronjunevaldoz.awake.core.math.Vec3f
import io.github.ronjunevaldoz.awake.core.math.Vec4f
import io.github.ronjunevaldoz.awake.core.math.angleDeg
import io.github.ronjunevaldoz.awake.core.rendering.Texture
import io.github.ronjunevaldoz.awake.core.rendering.VertexArrayObject
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

    private var modelViewMatrix = Mat4f.obtain()
    private var isUpdateNeeded = true
    private var totalElapsedTime = 0f

    private var updateCamera = true

    init {
        shader.compile()
        fontTexture = createTextTexture(
            "Ron June Valdoz",
            100f
        )
        createBuffers()
    }

    override fun draw() {
        updateCamera()
        totalElapsedTime += Time.Delta.toFloat()
        if (totalElapsedTime >= 0.25f) {
            calculateTexCoordinates(modelViewMatrix, Frame.width, Frame.height)
            totalElapsedTime = 0f
        }
        shader.use {
            fontTexture?.let { texture ->
                vao.use {
                    gl.disable(CommonGL.GL_CULL_FACE)
                    gl.enable(CommonGL.GL_BLEND)
                    gl.blendFunc(CommonGL.GL_ONE, CommonGL.GL_ONE_MINUS_SRC_ALPHA)
                    gl.activeTexture(CommonGL.GL_TEXTURE0)
                    gl.bindTexture(
                        CommonGL.GL_TEXTURE_2D, texture.id
                    )
                    gl.drawArrays(OpenGL.DrawMode.TriangleStrip, 0, 4)
                    gl.bindTexture(
                        CommonGL.GL_TEXTURE_2D, 0
                    )
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
                    val ratio = (Frame.width.toFloat() / Frame.height.toFloat())
                    shader.projectionViewMatrix =
                        Mat4f().frustum(-ratio, ratio, -1f, 1f, 0.1f, 100.0f)
                    val eye = Vec3f(0.0f, 0.0f, 1.0f)
                    val target = Vec3f(0.0f, 0.0f, 0.0f)
                    val up = Vec3f(0.0f, 1.0f, 0.0f)
                    shader.modelViewMatrix = Mat4f()
                        .rotateZ(45.angleDeg)
                        .scale(
                            (fontTexture!!.width.toFloat() / fontTexture!!.height.toFloat()),
                            1f,
                            1f
                        )
                        .translate(0f, 0f, 0f)
                        .setLookAt(
                            eye,
                            target,
                            up
                        )
                }
            }
            updateCamera = false
        }
    }

    private fun calculateTexCoordinates(
        mMVPMatrix: Mat4f,
        viewportWidth: Int,
        viewportHeight: Int
    ) {
        if (!isUpdateNeeded) return
        // 1. Calculate bounding box in screen coordinates with current matrices
        val cLT = Vec4f(-0.5f, -0.5f, 0.0f, 1.0f)
        val cLB = Vec4f(-0.5f, 0.5f, 0.0f, 1.0f)
        val cRT = Vec4f(0.5f, -0.5f, 0.0f, 1.0f)
        val cRB = Vec4f(0.5f, 0.5f, 0.0f, 1.0f)
        // Instead of calculating matrices again lets reuse ones which were already calculated
        // for rendering purpose. One important thing is the update() method must be called
        // after render() method
        cLT.makePixelCoords(mMVPMatrix, viewportWidth, viewportHeight)
        cLB.makePixelCoords(mMVPMatrix, viewportWidth, viewportHeight)
        cRT.makePixelCoords(mMVPMatrix, viewportWidth, viewportHeight)
        cRB.makePixelCoords(mMVPMatrix, viewportWidth, viewportHeight)
        // 2. Evaluate font size based on the height of bounding box corners
        val vl = cLB - cLT
        val vr = cRB - cRT
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
            attributes.forEach(::addVertexBuffer)
        }
    }
}