import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.viewinterop.AndroidView
import io.github.ronjunevaldoz.awake.core.graphics.Application
import io.github.ronjunevaldoz.awake.core.graphics.VulkanView

@Composable
actual fun AwakeCanvas(
    modifier: Modifier,
    renderer: Application
) {
    AndroidView(
        modifier = modifier,
        factory = { context ->
//            GameView(context, AndroidRenderer(renderer))
            VulkanView(context)
        }
    )
}