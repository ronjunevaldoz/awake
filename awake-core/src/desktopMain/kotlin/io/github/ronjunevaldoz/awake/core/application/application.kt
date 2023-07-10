package io.github.ronjunevaldoz.awake.core.application

import io.github.ronjunevaldoz.awake.core.graphics.opengl.GlfwWindow


fun glfwWindow(
    onInit: (window: GlfwWindow, width: Int, height: Int) -> Unit,
    onResize: (width: Int, height: Int) -> Unit,
    onUpdate: (delta: Float) -> Unit,
    onDispose: () -> Unit
) {
    val window = GlfwWindow(640, 480, "Desktop")
    onInit(window, 640, 480)
    window.listener = object : GlfwWindow.WindowListener {
        override fun resize(width: Int, height: Int) {
            onResize(width, height)
        }
    }
    // Set the desired frame rate
    DesktopGameLoop.initTime()

    while (!window.shouldClose()) {
        DesktopGameLoop.startLoop { deltaTime ->
            onUpdate(deltaTime.toFloat())
        }
        // swap buffer
        window.swap()
    }
    onDispose()
    window.dispose()
}