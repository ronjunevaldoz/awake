import androidx.compose.foundation.Canvas
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.runtime.withFrameMillis
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.ImageBitmap
import androidx.compose.ui.graphics.drawscope.DrawScope
import androidx.compose.ui.graphics.toComposeImageBitmap
import io.github.ronjunevaldoz.awake.core.graphics.Application
import io.github.ronjunevaldoz.awake.core.rendering.FrameBuffer
import kotlinx.coroutines.delay
import java.awt.image.BufferedImage
import java.nio.ByteBuffer

@Composable
actual fun AwakeCanvas(modifier: Modifier, renderer: Application) {
    val scope = rememberCoroutineScope()
    renderer.create()
    LaunchedEffect(Unit) {
        // TODO "Fix Launch effect is not working mac m1 only??" using GlfwWindow
        renderer.create()
    }

    EachFrameUpdatingCanvas(Modifier.fillMaxSize()) { frameTime ->
//        val width = size.width.toInt()
//        val height = size.height.toInt()
//        val fbo = FrameBuffer(width, height)
//        fbo.bind()
//
//        gl.viewport(0, 0, size.width.toInt(), size.height.toInt())
//        renderer.update(0f)
//        fbo.unbind()
//        drawImage(createBitmap(fbo, width, height))
    }
}

private fun createBitmap(fbo: FrameBuffer, width: Int, height: Int): ImageBitmap {
    // stable
    val pixelBuffer = fbo.getPixelBuffer().get<ByteBuffer>().asIntBuffer()
    val pixels = IntArray(pixelBuffer.remaining())
    pixelBuffer.get(pixels)
    val image = BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB)
    // Flip rows
    for (y in 0 until height) {
        val row = pixels.sliceArray(y * width until (y + 1) * width)
        image.setRGB(0, height - 1 - y, width, 1, row, 0, width)
    }
    return image.toComposeImageBitmap()
}

@Composable
fun EachFrameUpdatingCanvas(modifier: Modifier, onDraw: DrawScope.(Long) -> Unit) {
    var frameTime by remember { mutableStateOf(0L) }
    LaunchedEffect(Unit) {
        // TODO "Fix Launch effect is not working mac m1 only??" using GlfwWindow
        while (true) {
            delay(16) // Delay to achieve ~60 FPS (1000ms / 60fps = ~16ms)
            frameTime = withFrameMillis { it }
        }
    }
    Canvas(modifier) {
        onDraw(frameTime)
    }
}