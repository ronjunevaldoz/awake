package io.github.ronjunevaldoz.awake.core.application

import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.graphics.opengl.GlfwWindow
import io.github.ronjunevaldoz.awake.core.utils.Time


fun glfwWindow(
    onInit: (window: GlfwWindow, width: Int, height: Int) -> Unit,
    onResize: (width: Int, height: Int) -> Unit,
    onUpdate: (delta: Float) -> Unit
) {
    AwakeContext.init()
    val window = GlfwWindow(640, 480, "Desktop")
    onInit(window, 640, 480)
    window.listener = object : GlfwWindow.WindowListener {
        override fun resize(width: Int, height: Int) {
            onResize(width, height)
        }
    }
    // Set the desired frame rate
    val desiredFrameRate = AwakeContext.config.fps
    val desiredFrameTimeNanos = (1e9 / desiredFrameRate).toLong()

    var previousFrameTime = System.currentTimeMillis()

    while (!window.shouldClose()) {
        val currentFrameTime = System.currentTimeMillis()
        val deltaTime = (currentFrameTime - previousFrameTime) / 1000.0

        previousFrameTime = currentFrameTime
        Time.Delta = deltaTime
        onUpdate(deltaTime.toFloat()) // TODO use double instead to better precision
        Time.Fps = 1.0 / deltaTime

        val sleepTimeNanos = desiredFrameTimeNanos - (System.currentTimeMillis() - currentFrameTime)
        if (sleepTimeNanos > 0) {
            Thread.sleep(sleepTimeNanos / 1_000_000, (sleepTimeNanos % 1_000_000).toInt())
        }
        // swap buffer
        window.swap()
    }
    window.dispose()
}