import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import io.github.ronjunevaldoz.awake.core.graphics.Renderer

@Composable
expect fun AwakeCanvas(
    modifier: Modifier,
    renderer: Renderer
)