import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.padding
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.KeyboardArrowRight
import androidx.compose.material3.Button
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import demo.DemoDrawer
import demo.DemoRenderer
import demo.DemoScene
import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.Greeting

@Composable
fun App() {
    MaterialTheme {
        var greetingText by remember { mutableStateOf("Hello, World!") }
        // init awake context
        AwakeContext.init()
        val items = remember { mutableStateOf(DemoRenderer.drawableLabels) }
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
            DemoScene {
                colorObject = Color.LightGray
            }
        }
    }
}