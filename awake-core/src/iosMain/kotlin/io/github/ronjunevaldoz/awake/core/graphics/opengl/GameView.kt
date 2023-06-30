package io.github.ronjunevaldoz.awake.core.graphics.opengl

import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.graphics.Renderer
import io.github.ronjunevaldoz.awake.core.utils.Time
import kotlinx.cinterop.CValue
import kotlinx.cinterop.ObjCAction
import platform.CoreFoundation.CFTimeInterval
import platform.CoreGraphics.CGRect
import platform.EAGL.EAGLContext
import platform.EAGL.kEAGLRenderingAPIOpenGLES1
import platform.EAGL.kEAGLRenderingAPIOpenGLES2
import platform.EAGL.kEAGLRenderingAPIOpenGLES3
import platform.Foundation.NSRunLoop
import platform.Foundation.NSRunLoopCommonModes
import platform.Foundation.NSSelectorFromString
import platform.GLKit.GLKView
import platform.GLKit.GLKViewDelegateProtocol
import platform.GLKit.GLKViewDrawableColorFormatRGBA8888
import platform.GLKit.GLKViewDrawableDepthFormat24
import platform.GLKit.GLKViewDrawableStencilFormat8
import platform.QuartzCore.CADisplayLink
import platform.UIKit.UIScreen


class GameView(frame: CValue<CGRect>, val renderer: Renderer) : GLKView(frame),
    GLKViewDelegateProtocol {

    var previousTimestamp: CFTimeInterval = 0.0
    private var displayLink: CADisplayLink

    init {
        val context = when (AwakeContext.config.glVersion) {
            OpenGL.Version.ES1 -> EAGLContext(kEAGLRenderingAPIOpenGLES1)
            OpenGL.Version.ES2 -> EAGLContext(kEAGLRenderingAPIOpenGLES2)
            OpenGL.Version.ES3 -> EAGLContext(kEAGLRenderingAPIOpenGLES3)
        }
        // create context from es version
        this.context = context
        EAGLContext.setCurrentContext(this.context)

        drawableColorFormat = GLKViewDrawableColorFormatRGBA8888
        drawableDepthFormat = GLKViewDrawableDepthFormat24
        drawableStencilFormat = GLKViewDrawableStencilFormat8

        renderer.create()
        // avoid redraw component on component update
        enableSetNeedsDisplay = false
        displayLink = UIScreen.mainScreen.displayLinkWithTarget(
            this,
            NSSelectorFromString("update:")
        )!!
        displayLink.preferredFramesPerSecond = AwakeContext.config.fps.toLong()
        displayLink.addToRunLoop(NSRunLoop.currentRunLoop, NSRunLoopCommonModes)
        delegate = this
    }

    @ObjCAction
    private fun update(displayLink: CADisplayLink) {
        val currentTimestamp = displayLink.timestamp
        var deltaTime = 0.0
        if (previousTimestamp > 0) {
            deltaTime = currentTimestamp - previousTimestamp
        }
        // Update previous timestamp for the next frame
        previousTimestamp = currentTimestamp
        Time.Delta = deltaTime
        display()
        Time.Fps = 1.0 / deltaTime
    }

    override fun glkView(view: GLKView, drawInRect: CValue<CGRect>) {
        renderer.update(Time.Delta.toFloat())
    }
}