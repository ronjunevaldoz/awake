package demo

import androidx.compose.ui.graphics.Color
import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.getPlatform
import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.graphics.Drawable
import io.github.ronjunevaldoz.awake.core.graphics.Renderer
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL
import scene.DemoColoredTriangle
import scene.DemoTexture
import scene.DemoTriangle
import scene.TransformTriangle
import kotlin.native.concurrent.ThreadLocal
import kotlin.random.Random

@ThreadLocal
object DemoApplication : Renderer {

    private var drawables = emptyList<Drawable>()
    val drawableLabels: List<String> = listOf(
        "Triangle",
        "Texture",
        "Colored",
        "Transform"
    )

    var drawableIndex: Int = 0
    var color = 0f
    var colorObject = Color.Green
    var colorVelocity = 1f / 60f


    override fun create() {
        drawables =
            listOf(
                DemoTriangle(),
                DemoTexture(),
                DemoColoredTriangle(),
                TransformTriangle()
            )
    }

    private var totalElapsedTime = 0f
    override fun update(delta: Float) {
        totalElapsedTime += delta
        // Redraw background color
        if (color > 1 || color < 0) {
            colorVelocity = -colorVelocity
        }
        color += colorVelocity
//        gl.clearColor(Color.Green)
        gl.clearColor(color * 0.5f, color, color, 1f)
        gl.clear(OpenGL.BufferBit.Color.value or OpenGL.BufferBit.Depth.value)

        if (totalElapsedTime >= 1f) {
            if (!getPlatform().isMobile) {
                drawableIndex = Random.nextInt(0, drawables.size)
            }
            totalElapsedTime = 0f
        }
        drawables[drawableIndex].draw()
    }

    override fun pause() {
    }

    override fun resume() {
    }

    override fun resize(x: Int, y: Int, width: Int, height: Int) {
        gl.viewport(x, y, width, height)
    }

    override fun dispose() {
        drawables.filterIsInstance<Disposable>().forEach { it.dispose() }
    }
}