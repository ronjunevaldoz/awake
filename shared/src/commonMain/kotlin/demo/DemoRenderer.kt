package demo

import androidx.compose.ui.graphics.Color
import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.graphics.Drawable
import io.github.ronjunevaldoz.awake.core.graphics.Renderer
import io.github.ronjunevaldoz.awake.core.graphics.Shader
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL
import scene.ColoredTriangle
import scene.Texture
import scene.Triangle
import kotlin.native.concurrent.ThreadLocal

@ThreadLocal
object DemoRenderer : Renderer {

    private var drawables = emptyList<Drawable>()
    val drawableLabels: List<String> = listOf(
        "Triangle",
        "Texture",
        "Colored",
    )

    var drawableIndex: Int = 0
    var color = 0f
    var colorObject = Color.Green
    var colorVelocity = 1f / 60f


    override fun create() {
        drawables =
            listOf(
                Triangle(),
                Texture(),
                ColoredTriangle()
            )
        drawables.filterIsInstance<Shader>().forEach { it.compile() }
    }

    override fun update(delta: Float) {
        // Redraw background color
        if (color > 1 || color < 0) {
            colorVelocity = -colorVelocity
        }
        color += colorVelocity
//        Agl.clearColor(colorObject)
        gl.clearColor(color * 0.5f, color, color, 1f)
        gl.clear(OpenGL.BufferBit.Color.value or OpenGL.BufferBit.Depth.value)
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