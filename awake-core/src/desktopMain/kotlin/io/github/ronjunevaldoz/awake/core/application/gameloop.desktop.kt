package io.github.ronjunevaldoz.awake.core.application

import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.utils.Time

object DesktopGameLoop : GameLoop {
    private var desiredFrameTimeNanos: Long = 0
    private var previousFrameTime: Long = 0

    override fun initTime() {
        val desiredFrameRate = AwakeContext.config.fps
        desiredFrameTimeNanos = (1e9 / desiredFrameRate).toLong()
        previousFrameTime = System.currentTimeMillis()
    }

    override fun startLoop(onUpdate: (deltaTime: Double) -> Unit) {
        val currentFrameTime = System.currentTimeMillis()
        val deltaTime = (currentFrameTime - previousFrameTime) / 1000.0

        previousFrameTime = currentFrameTime
        Time.Delta = deltaTime
        onUpdate(deltaTime)
        Time.Fps = 1.0 / deltaTime

        val sleepTimeNanos = desiredFrameTimeNanos - (System.currentTimeMillis() - currentFrameTime)
        if (sleepTimeNanos > 0) {
            Thread.sleep(sleepTimeNanos / 1_000_000, (sleepTimeNanos % 1_000_000).toInt())
        }
    }
}