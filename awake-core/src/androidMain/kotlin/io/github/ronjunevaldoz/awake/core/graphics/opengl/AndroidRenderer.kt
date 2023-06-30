package io.github.ronjunevaldoz.awake.core.graphics.opengl

import android.opengl.GLSurfaceView
import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.graphics.Renderer
import io.github.ronjunevaldoz.awake.core.utils.Time
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class AndroidRenderer(private val renderer: Renderer) : GLSurfaceView.Renderer {
    private var previousFrameTime = 0L
    private var desiredFrameRate = AwakeContext.config.fps
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        // Set the background frame color
        renderer.create()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        // Set the viewport to the size of the view.
        renderer.resize(0, 0, width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        // Get the current time
        val currentFrameTime = System.nanoTime()
        // Calculate the delta time in seconds
        val deltaTime = (currentFrameTime - previousFrameTime) / 1000000000f

        // Update previous frame time for the next frame
        previousFrameTime = currentFrameTime
        Time.Delta = deltaTime.toDouble()
        // Your rendering logic goes here
        renderer.update(deltaTime)
        Time.Fps = 1.0 / deltaTime

        // Limit the frame rate to 60 frames per second (approximately)
        val desiredFrameTime = 1.0 / desiredFrameRate
        val desiredFrameTimeNanos = (desiredFrameTime * 1000000000).toLong()

        // Calculate the time to sleep to maintain the desired frame rate
        val sleepTimeNanos = desiredFrameTimeNanos - (System.nanoTime() - currentFrameTime)
        if (sleepTimeNanos > 0) {
            Thread.sleep(sleepTimeNanos / 1000000, (sleepTimeNanos % 1000000).toInt())
        }
    }
}