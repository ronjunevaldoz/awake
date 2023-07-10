package io.github.ronjunevaldoz.awake.core.graphics.opengl

import androidx.compose.runtime.Composable
import androidx.compose.ui.ComposeScene
import androidx.compose.ui.unit.Constraints
import androidx.compose.ui.unit.Density
import org.jetbrains.skia.BackendRenderTarget
import org.jetbrains.skia.Color
import org.jetbrains.skia.ColorSpace
import org.jetbrains.skia.DirectContext
import org.jetbrains.skia.FramebufferFormat
import org.jetbrains.skia.Surface
import org.jetbrains.skia.SurfaceColorFormat
import org.jetbrains.skia.SurfaceOrigin
import org.jetbrains.skiko.FrameDispatcher
import org.lwjgl.glfw.Callbacks
import org.lwjgl.glfw.GLFW
import org.lwjgl.glfw.GLFWErrorCallback
import org.lwjgl.opengl.GL
import org.lwjgl.opengl.GL11
import org.lwjgl.opengl.GL30
import org.lwjgl.system.MemoryStack
import java.nio.IntBuffer


fun createCompose(window: Long, width: Int, height: Int, content: @Composable () -> Unit) {
    val context = DirectContext.makeGL()
    var surface =
        createSurface(width, height, context) // Skia Surface, bound to the OpenGL framebuffer

    val glfwDispatcher =
        GlfwCoroutineDispatcher() // a custom coroutine dispatcher, in which Compose will run


    GLFW.glfwSetWindowCloseCallback(window) {
        glfwDispatcher.stop()
    }

    var width = width
    var height = height

    lateinit var composeScene: ComposeScene

    fun render() {
        surface.canvas.clear(Color.WHITE)
        composeScene.constraints = Constraints(maxWidth = width, maxHeight = height)
        composeScene.render(surface.canvas, System.nanoTime())
        context.flush()
        GLFW.glfwSwapBuffers(window)
    }

    val frameDispatcher = FrameDispatcher(glfwDispatcher) { render() }

    val density = Density(windowDensity(window))
    composeScene =
        ComposeScene(glfwDispatcher, density, invalidate = frameDispatcher::scheduleFrame)
    GLFW.glfwSetWindowSizeCallback(window) { _, windowWidth, windowHeight ->
        width = windowWidth * 2
        height = windowHeight * 2
        surface.close()
        surface = createSurface(width, height, context)

        GLFW.glfwSwapInterval(0)
        render()
        GLFW.glfwSwapInterval(1)
    }

    composeScene.subscribeToGLFWEvents(window)
    composeScene.setContent(content)

    glfwDispatcher.runLoop()

    composeScene.close()
}

private fun createSurface(width: Int, height: Int, context: DirectContext): Surface {
    val fbId = GL11.glGetInteger(GL30.GL_FRAMEBUFFER_BINDING)
    val renderTarget = BackendRenderTarget.makeGL(
        width, height, 0, 8, fbId,
        FramebufferFormat.GR_GL_RGBA8
    )
    return Surface.makeFromBackendRenderTarget(
        context,
        renderTarget,
        SurfaceOrigin.BOTTOM_LEFT,
        SurfaceColorFormat.RGBA_8888,
        ColorSpace.sRGB
    ) ?: throw Exception("Unable to create surface")
}

private fun windowDensity(window: Long): Float {
    val array = FloatArray(1)
    GLFW.glfwGetWindowContentScale(window, array, FloatArray(1))
    return array[0]
}

class GlfwWindow(width: Int, height: Int, title: String) {

    val window: Long

    interface WindowListener {
        fun resize(width: Int, height: Int)
    }

    var listener: WindowListener? = null

    init {
        initGlfw()
        window = createWindow(width, height, title)
        initOpenGL()
    }


    private fun initGlfw() {
        GLFWErrorCallback.createPrint(System.err).set()
        check(GLFW.glfwInit()) { "Unable to initialize GLFW" }

        // Configure GLFW
        GLFW.glfwDefaultWindowHints() // optional, the current window hints are already the default
        GLFW.glfwWindowHint(
            GLFW.GLFW_VISIBLE,
            GLFW.GLFW_FALSE
        ) // the window will stay hidden after creation
        GLFW.glfwWindowHint(GLFW.GLFW_RESIZABLE, GLFW.GLFW_TRUE) // the window will be resizable
        GLFW.glfwWindowHint(GLFW.GLFW_CONTEXT_VERSION_MAJOR, 3)
        GLFW.glfwWindowHint(GLFW.GLFW_CONTEXT_VERSION_MINOR, 3)
        GLFW.glfwWindowHint(GLFW.GLFW_OPENGL_PROFILE, GLFW.GLFW_OPENGL_CORE_PROFILE)
        GLFW.glfwWindowHint(GLFW.GLFW_OPENGL_FORWARD_COMPAT, GLFW.GLFW_TRUE)
    }

    private fun createWindow(width: Int, height: Int, title: String): Long {
        val window = GLFW.glfwCreateWindow(width, height, title, 0, 0)

        // add listeners here
        GLFW.glfwSetKeyCallback(
            window
        ) { _: Long, key: Int, scancode: Int, action: Int, mods: Int ->
            if (key == GLFW.GLFW_KEY_ESCAPE && action == GLFW.GLFW_RELEASE) GLFW.glfwSetWindowShouldClose(
                window,
                true
            ) // We will detect this in the rendering loop
        }
        GLFW.glfwSetFramebufferSizeCallback(window) { _: Long, w: Int, h: Int ->
            listener?.resize(w, h)
        }
        MemoryStack.stackPush().use { stack ->
            val pWidth: IntBuffer = stack.mallocInt(1) // int*
            val pHeight: IntBuffer = stack.mallocInt(1) // int*

            // Get the window size passed to glfwCreateWindow
            GLFW.glfwGetWindowSize(window, pWidth, pHeight)

            // Get the resolution of the primary monitor
            val vidMode = GLFW.glfwGetVideoMode(GLFW.glfwGetPrimaryMonitor())

            // Center the window
            GLFW.glfwSetWindowPos(
                window,
                (vidMode!!.width() - pWidth.get(0)) / 2,
                (vidMode.height() - pHeight.get(0)) / 2
            )
        }

        // Make the OpenGL context current
        GLFW.glfwMakeContextCurrent(window)
        // Enable v-sync
        GLFW.glfwSwapInterval(1)
        // Make the window visible
        GLFW.glfwShowWindow(window)
        return window
    }


    private fun initOpenGL() {
        GL.createCapabilities()
        GL11.glClearColor(0.0f, 0.0f, 0.0f, 1.0f)
    }

    fun shouldClose(): Boolean {
        return GLFW.glfwWindowShouldClose(window)
    }

    fun time(): Double {
        return GLFW.glfwGetTime()
    }

    fun swap() {
        GLFW.glfwSwapBuffers(window)
        GLFW.glfwPollEvents()
    }

    fun dispose() {
        // Free the window callbacks and destroy the window
        Callbacks.glfwFreeCallbacks(window)
        GLFW.glfwDestroyWindow(window)

        GLFW.glfwTerminate()
        GLFW.glfwSetErrorCallback(null)!!.free()
    }
}