package io.github.ronjunevaldoz.awake.core.graphics.opengl

import android.content.Context
import android.opengl.GLSurfaceView
import io.github.ronjunevaldoz.awake.core.AwakeContext
import org.jetbrains.compose.components.resources.BuildConfig

class GameView(context: Context, private val renderer: AndroidRenderer) : GLSurfaceView(context) {
    init {
        setEGLContextClientVersion(
            when (AwakeContext.config.glVersion) {
                OpenGL.Version.ES1 -> 1
                OpenGL.Version.ES2 -> 2
                OpenGL.Version.ES3 -> 3
            }
        )
        if (BuildConfig.DEBUG) {
            debugFlags = DEBUG_CHECK_GL_ERROR
        }
        setRenderer(renderer)
    }

    override fun onPause() {
        super.onPause()
        renderer.pause()
    }

    override fun onResume() {
        super.onResume()
        renderer.resume()
    }

    override fun onDetachedFromWindow() {
        super.onDetachedFromWindow()
        renderer.dispose()
    }
}