package demo

import AwakeCanvas
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier

@Composable
fun DemoScene(
    init: DemoApplication.() -> Unit
) {
    val renderer = remember {
        mutableStateOf(DemoApplication.apply(init))
    }
    AwakeCanvas(
        modifier = Modifier.fillMaxSize(),
        renderer = renderer.value
    )
}