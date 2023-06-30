package io.github.ronjunevaldoz.awake.core.graphics.opengl

import kotlinx.coroutines.CoroutineDispatcher
import org.lwjgl.glfw.GLFW
import java.util.concurrent.BlockingQueue
import java.util.concurrent.LinkedBlockingQueue
import java.util.concurrent.atomic.AtomicBoolean
import kotlin.coroutines.CoroutineContext

class GlfwCoroutineDispatcher : CoroutineDispatcher() {

    private val tasks: BlockingQueue<Runnable> = LinkedBlockingQueue()
    private val isStopped = AtomicBoolean(false)

    fun runLoop() {
        while (!isStopped.get()) {
            val runnable = tasks.take()
            if (!isStopped.get()) {
                runnable.run()
            }
            GLFW.glfwWaitEvents()
        }
    }

    fun stop() {
        isStopped.set(true)
    }

    override fun dispatch(context: CoroutineContext, block: Runnable) {
        tasks.offer(block)
        GLFW.glfwPostEmptyEvent()
    }
}