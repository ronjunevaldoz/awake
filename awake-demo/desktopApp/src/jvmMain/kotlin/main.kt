import demo.DemoApplication
import io.github.ronjunevaldoz.awake.core.application.glfwWindow

//fun main() = application {
//    Window(onCloseRequest = ::exitApplication) {
//        MainView()
//    }
//}

fun main() {
    val application = DemoApplication
    glfwWindow(
        onInit = { window, width, height ->
            application.create()
        },
        onResize = { width, height ->
            application.resize(0, 0, width, height)
        },
        onUpdate = { time ->
            application.update(time)
        }
    )
}