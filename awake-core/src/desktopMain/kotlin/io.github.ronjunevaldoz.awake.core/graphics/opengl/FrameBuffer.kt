package io.github.ronjunevaldoz.awake.core.graphics.opengl

import io.github.ronjunevaldoz.awake.core.graphics.Drawable
import org.lwjgl.glfw.GLFW.glfwGetCurrentContext
import org.lwjgl.glfw.GLFW.glfwSwapBuffers
import org.lwjgl.opengl.GL30.GL_COLOR_ATTACHMENT0
import org.lwjgl.opengl.GL30.GL_COLOR_BUFFER_BIT
import org.lwjgl.opengl.GL30.GL_DEPTH24_STENCIL8
import org.lwjgl.opengl.GL30.GL_DEPTH_STENCIL_ATTACHMENT
import org.lwjgl.opengl.GL30.GL_FRAMEBUFFER
import org.lwjgl.opengl.GL30.GL_FRAMEBUFFER_COMPLETE
import org.lwjgl.opengl.GL30.GL_LINEAR
import org.lwjgl.opengl.GL30.GL_RENDERBUFFER
import org.lwjgl.opengl.GL30.GL_RGB
import org.lwjgl.opengl.GL30.GL_RGBA
import org.lwjgl.opengl.GL30.GL_TEXTURE_2D
import org.lwjgl.opengl.GL30.GL_TEXTURE_MAG_FILTER
import org.lwjgl.opengl.GL30.GL_TEXTURE_MIN_FILTER
import org.lwjgl.opengl.GL30.GL_UNSIGNED_BYTE
import org.lwjgl.opengl.GL30.glBindFramebuffer
import org.lwjgl.opengl.GL30.glBindRenderbuffer
import org.lwjgl.opengl.GL30.glBindTexture
import org.lwjgl.opengl.GL30.glCheckFramebufferStatus
import org.lwjgl.opengl.GL30.glClear
import org.lwjgl.opengl.GL30.glClearColor
import org.lwjgl.opengl.GL30.glDeleteFramebuffers
import org.lwjgl.opengl.GL30.glDeleteRenderbuffers
import org.lwjgl.opengl.GL30.glDeleteTextures
import org.lwjgl.opengl.GL30.glFramebufferRenderbuffer
import org.lwjgl.opengl.GL30.glFramebufferTexture2D
import org.lwjgl.opengl.GL30.glGenFramebuffers
import org.lwjgl.opengl.GL30.glGenRenderbuffers
import org.lwjgl.opengl.GL30.glGenTextures
import org.lwjgl.opengl.GL30.glGetTexImage
import org.lwjgl.opengl.GL30.glRenderbufferStorage
import org.lwjgl.opengl.GL30.glTexImage2D
import org.lwjgl.opengl.GL30.glTexParameteri
import org.lwjgl.opengl.GL30.glViewport
import java.nio.ByteBuffer
import java.nio.ByteOrder

/**
 *
 */
class Framebuffer(private val width: Int, private val height: Int) {
    private var framebuffer: Int = 0
    private var texture: Int = 0
    private var renderbuffer: Int = 0

    init {
        createFramebuffer()
    }

    private fun createFramebuffer() {
        // Create and bind the framebuffer
        framebuffer = glGenFramebuffers()
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer)

        // Create a texture for rendering
        texture = glGenTextures()
        glBindTexture(GL_TEXTURE_2D, texture)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, null as ByteBuffer?)

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
        glBindTexture(GL_TEXTURE_2D, 0)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0)

        // Create a renderbuffer for depth and stencil
        renderbuffer = glGenRenderbuffers()
        glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer)
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height)
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer)

        // Check if the framebuffer is complete
        val status = glCheckFramebufferStatus(GL_FRAMEBUFFER)
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            throw RuntimeException("Framebuffer is not complete!")
        }

        // Unbind the framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0)
    }

    fun bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer)
    }

    fun unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0)
    }

    fun drawTriangle(drawable: Drawable) {
        // Set viewport to match framebuffer size
        glViewport(0, 0, width, height)

        // Clear the framebuffer
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f)
        glClear(GL_COLOR_BUFFER_BIT)

        // Perform rendering here (e.g., render your triangle using OpenGL commands)
        drawable.draw()

        // Swap buffers (if using double buffering)
        glfwSwapBuffers(glfwGetCurrentContext())
    }

    fun retrievePixelData(): ByteBuffer {
        val pixelData = ByteBuffer.allocateDirect(width * height * 4).order(ByteOrder.nativeOrder()) // 3 components (RGB)
        glBindTexture(GL_TEXTURE_2D, texture)
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData)
        return pixelData
    }

    fun cleanup() {
        // Release resources
        glDeleteFramebuffers(framebuffer)
        glDeleteTextures(texture)
        glDeleteRenderbuffers(renderbuffer)
    }
}
