

import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.interop.UIKitView
import io.github.ronjunevaldoz.awake.core.graphics.Renderer
import io.github.ronjunevaldoz.awake.core.graphics.opengl.GameView
import platform.UIKit.UIScreen

@Composable
actual fun AwakeCanvas(
    modifier: Modifier,
    renderer: Renderer,
) {
    val gameView = remember {
        { GameView(UIScreen.mainScreen.bounds, renderer) }
    }
    UIKitView(
        factory = gameView,
        modifier = modifier,
//        onResize = { uiView, frame ->
//            val width = CGRectGetWidth(frame)
//            val height = CGRectGetHeight(frame)
//            renderer.resize(0,0, width.toInt(), height.toInt())
//            uiView.setFrame(frame)
//        },
        onRelease = { uiView ->
            uiView.renderer.dispose()
        },
        interactive = false
    )
}