package demo

import AwakeCanvas
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier

@Composable
fun DemoScene(
    init: DemoRenderer.() -> Unit
) {
    val renderer = remember {
        mutableStateOf(DemoRenderer.apply(init))
    }
    Box(Modifier.fillMaxWidth()) {
        AwakeCanvas(
            modifier = Modifier.fillMaxSize(),
            renderer = renderer.value
        )
    }
}