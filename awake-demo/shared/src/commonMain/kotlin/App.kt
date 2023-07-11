import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.KeyboardArrowRight
import androidx.compose.material3.Button
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import demo.DemoApplication
import demo.DemoDrawer
import demo.DemoScene
import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.Greeting
import io.github.ronjunevaldoz.awake.core.utils.Time
import kotlinx.coroutines.delay

@Composable
fun App() {
    MaterialTheme {
        var greetingText by remember { mutableStateOf("Hello, World!") }
        var fpsText by remember { mutableStateOf("") }
        val items = remember { mutableStateOf(DemoApplication.drawableLabels) }
        LaunchedEffect(Unit) {
            while (true) {
                delay(16)
                fpsText = "Fps: ${Time.FpsString}"
            }
        }
        // init awake context
        AwakeContext.init()
        DemoDrawer(items.value) {
            Button(onClick = {
                greetingText = Greeting().greet()
            }) {
                Text(greetingText)
            }
            Row(verticalAlignment = Alignment.CenterVertically) {
                Text(text = "Swipe right to open drawer samples")
                Icon(
                    imageVector = Icons.Default.KeyboardArrowRight,
                    contentDescription = "Double Arrow",
                    modifier = Modifier.padding(start = 8.dp)
                )
            }
            Box(modifier = Modifier.fillMaxSize()) {
                DemoScene {
                    colorObject = Color.LightGray
                }
                Text(
                    text = fpsText,
                    modifier = Modifier.fillMaxWidth(),
                    color = Color.White
                )
            }
        }
    }
}