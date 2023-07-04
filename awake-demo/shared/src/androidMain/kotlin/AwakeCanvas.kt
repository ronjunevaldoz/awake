import android.opengl.GLSurfaceView
import android.view.View
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalLifecycleOwner
import androidx.compose.ui.viewinterop.AndroidView
import androidx.lifecycle.Lifecycle
import androidx.lifecycle.LifecycleEventObserver
import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.graphics.Renderer
import io.github.ronjunevaldoz.awake.core.graphics.opengl.AndroidRenderer
import io.github.ronjunevaldoz.awake.core.graphics.opengl.GameView
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL
import org.jetbrains.compose.components.resources.BuildConfig

@Composable
actual fun AwakeCanvas(modifier: Modifier, renderer: Renderer) {
    val lifecycleOwner = LocalLifecycleOwner.current
    AndroidView(
        modifier = modifier,
        factory = { context ->
            GameView(context).apply {
                setEGLContextClientVersion(
                    when (AwakeContext.config.glVersion) {
                        OpenGL.Version.ES1 -> 1
                        OpenGL.Version.ES2 -> 2
                        OpenGL.Version.ES3 -> 3
                    }
                )
                if (BuildConfig.DEBUG) {
                    debugFlags = GLSurfaceView.DEBUG_CHECK_GL_ERROR
                }
                setRenderer(AndroidRenderer(renderer))
                val observer = LifecycleEventObserver { _, event ->
                    when (event) {
                        Lifecycle.Event.ON_PAUSE -> renderer.pause()
                        Lifecycle.Event.ON_RESUME -> renderer.resume()
                        Lifecycle.Event.ON_DESTROY -> {
                            renderer.dispose()
                        }
                        else -> {}
                    }
                }

                val lifecycle = lifecycleOwner.lifecycle

                addOnAttachStateChangeListener(object : View.OnAttachStateChangeListener {
                    override fun onViewAttachedToWindow(v: View) {
                        lifecycle.addObserver(observer)
                    }

                    override fun onViewDetachedFromWindow(v: View) {
                        renderer.dispose()
                        lifecycle.removeObserver(observer)
                    }
                })
            }
        }
    )
}