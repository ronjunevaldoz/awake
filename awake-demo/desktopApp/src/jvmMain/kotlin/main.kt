import demo.DemoApplication
import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.application.createFrame

//fun main() = application {
//    Window(onCloseRequest = ::exitApplication) {
//        MainView()
//    }
//}

fun main() {
    AwakeContext.init() // manually set
    val application = DemoApplication

    createFrame(
        width = 640,
        height = 480,
        onInit = {
            application.create()
        },
        onResize = { width, height ->
            application.resize(0, 0, width, height)
        },
        onUpdate = { time ->
            application.update(time)
        },
        onDispose = {
            application.dispose()
        }
    )
}