package io.github.ronjunevaldoz.awake.core.graphics.opengl

import io.github.ronjunevaldoz.awake.core.graphics.image.Bitmap
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants.GL_RGBA
import io.github.ronjunevaldoz.awake.core.memory.Buffer
import io.github.ronjunevaldoz.awake.core.memory.ByteBuffer
import io.github.ronjunevaldoz.awake.core.memory.FloatBuf
import io.github.ronjunevaldoz.awake.core.memory.FloatBuffer
import io.github.ronjunevaldoz.awake.core.memory.IntBuf
import io.github.ronjunevaldoz.awake.core.memory.IntBuffer
import io.github.ronjunevaldoz.awake.core.memory.ShortBuffer
import io.github.ronjunevaldoz.awake.core.memory.createIntBuffer
import org.lwjgl.opengl.GL11.glDeleteTextures
import org.lwjgl.opengl.GL11.glGetError
import org.lwjgl.opengl.GL20.GL_UNSIGNED_BYTE
import org.lwjgl.opengl.GL20.glActiveTexture
import org.lwjgl.opengl.GL20.glAttachShader
import org.lwjgl.opengl.GL20.glBindAttribLocation
import org.lwjgl.opengl.GL20.glBindBuffer
import org.lwjgl.opengl.GL20.glBindTexture
import org.lwjgl.opengl.GL20.glBufferData
import org.lwjgl.opengl.GL20.glClear
import org.lwjgl.opengl.GL20.glClearColor
import org.lwjgl.opengl.GL20.glCompileShader
import org.lwjgl.opengl.GL20.glCreateProgram
import org.lwjgl.opengl.GL20.glCreateShader
import org.lwjgl.opengl.GL20.glDeleteBuffers
import org.lwjgl.opengl.GL20.glDeleteProgram
import org.lwjgl.opengl.GL20.glDeleteShader
import org.lwjgl.opengl.GL20.glDisableVertexAttribArray
import org.lwjgl.opengl.GL20.glDrawArrays
import org.lwjgl.opengl.GL20.glDrawElements
import org.lwjgl.opengl.GL20.glEnableVertexAttribArray
import org.lwjgl.opengl.GL20.glGenBuffers
import org.lwjgl.opengl.GL20.glGenTextures
import org.lwjgl.opengl.GL20.glGetAttribLocation
import org.lwjgl.opengl.GL20.glGetProgramInfoLog
import org.lwjgl.opengl.GL20.glGetProgramiv
import org.lwjgl.opengl.GL20.glGetShaderInfoLog
import org.lwjgl.opengl.GL20.glGetShaderiv
import org.lwjgl.opengl.GL20.glGetUniformLocation
import org.lwjgl.opengl.GL20.glLinkProgram
import org.lwjgl.opengl.GL20.glShaderSource
import org.lwjgl.opengl.GL20.glTexImage2D
import org.lwjgl.opengl.GL20.glTexParameteri
import org.lwjgl.opengl.GL20.glUniform1f
import org.lwjgl.opengl.GL20.glUniform1i
import org.lwjgl.opengl.GL20.glUniformMatrix4fv
import org.lwjgl.opengl.GL20.glUseProgram
import org.lwjgl.opengl.GL20.glVertexAttribPointer
import org.lwjgl.opengl.GL20.glViewport
import org.lwjgl.opengl.GL30.glBindVertexArray
import org.lwjgl.opengl.GL30.glDeleteVertexArrays
import org.lwjgl.opengl.GL30.glGenVertexArrays

internal actual object Agl : OpenGL {
    override fun clearColor(r: Float, g: Float, b: Float, a: Float) {
        glClearColor(r, g, b, a)
    }

    override fun clear(mask: Int) {
        glClear(mask)
    }

    override fun viewport(x: Int, y: Int, width: Int, height: Int) {
        glViewport(x, y, width, height)
    }

    override fun createShader(type: OpenGL.ShaderType): Int {
        return glCreateShader(type.value)
    }

    override fun shaderSource(shader: Int, content: String) {
        glShaderSource(shader, content)
    }

    override fun compileShader(shader: Int) {
        glCompileShader(shader)
    }

    override fun getShaderInfoLog(shader: Int): String {
        return glGetShaderInfoLog(shader)
    }

    override fun getShaderiv(shader: Int, status: OpenGL.Status, buffer: IntBuf) {
        glGetShaderiv(shader, status.value, buffer.get())
    }

    override fun createProgram(): Int {
        return glCreateProgram()
    }

    override fun attachShader(program: Int, shader: Int) {
        glAttachShader(program, shader)
    }

    override fun linkProgram(program: Int) {
        glLinkProgram(program)
    }

    override fun getProgramInfoLog(program: Int): String {
        return glGetProgramInfoLog(program)
    }

    override fun getProgramiv(program: Int, status: OpenGL.Status, buffer: IntBuf) {
        glGetProgramiv(program, status.value, buffer.get())
    }

    override fun deleteShader(shader: Int) {
        glDeleteShader(shader)
    }

    override fun useProgram(program: Int) {
        glUseProgram(program)
    }

    override fun deleteProgram(program: Int) {
        glDeleteProgram(program)
    }

    override fun getUniformLocation(program: Int, name: String): Int {
        return glGetUniformLocation(program, name)
    }

    override fun bindAttribLocation(program: ProgramId, index: Int, name: String) {
        glBindAttribLocation(program, index, name)
    }

    override fun getAttribLocation(program: Int, name: String): Int {
        return glGetAttribLocation(program, name)
    }

    override fun vertexAttribPointer(
        index: Int,
        size: Int,
        type: Int,
        normalized: Boolean,
        stride: Int,
        ptr: Buffer?
    ) {
        ptr?.`when`(
            byte = {
                glVertexAttribPointer(
                    index,
                    size,
                    type,
                    normalized,
                    stride,
                    this
                )
            },
            short = {
                glVertexAttribPointer(
                    index,
                    size,
                    type,
                    normalized,
                    stride,
                    this
                )
            },
            int = {
                glVertexAttribPointer(
                    index,
                    size,
                    type,
                    normalized,
                    stride,
                    this
                )
            },
            float = {
                glVertexAttribPointer(
                    index,
                    size,
                    type,
                    normalized,
                    stride,
                    this
                )
            }
        ) ?: glVertexAttribPointer(
            index,
            size,
            type,
            normalized,
            stride,
            0
        )
    }

    override fun vertexAttribPointer(
        index: Int,
        size: Int,
        type: Int,
        normalized: Boolean,
        stride: Int,
        offset: Int
    ) {
        glVertexAttribPointer(
            index,
            size,
            type,
            normalized,
            stride,
            offset.toLong()
        )
    }

    override fun enableVertexAttribArray(index: Int) {
        glEnableVertexAttribArray(index)
    }

    override fun drawArrays(mode: Int, first: Int, count: Int) {
        glDrawArrays(mode, first, count)
    }

    override fun disableVertexAttribArray(index: Int) {
        glDisableVertexAttribArray(index)
    }

    override fun genBuffers(n: Int, buffers: IntBuf) {
        glGenBuffers(buffers.get())
    }

    override fun bindBuffer(target: OpenGL.BufferType, buffer: BufferId) {
        glBindBuffer(target.value, buffer)
    }

    override fun bufferData(
        target: OpenGL.BufferType,
        size: Long,
        data: Buffer,
        usage: OpenGL.DrawType
    ) {
        data.`when`(
            byte = {
                glBufferData(
                    target.value,
                    this,
                    usage.value
                )
            },
            short = {
                glBufferData(
                    target.value,
                    this,
                    usage.value
                )
            },
            int = {
                glBufferData(
                    target.value,
                    this,
                    usage.value
                )
            },
            float = {
                glBufferData(
                    target.value,
                    this,
                    usage.value
                )
            }
        )
    }

    override fun deleteBuffers(n: Int, buffers: IntBuf) {
        glDeleteBuffers(buffers.get())
    }

    override fun deleteVertexArrays(n: Int, arrays: IntBuf) {
        glDeleteVertexArrays(arrays.get())
    }

    override fun deleteTextures(n: Int, textures: IntBuf) {
        glDeleteTextures(textures.get())
    }

    override fun genVertexArrays(n: Int, arrays: IntBuf) {
        glGenVertexArrays(arrays.get())
    }

    override fun bindVertexArray(array: ArrayId) {
        glBindVertexArray(array)
    }

    override fun drawElements(mode: OpenGL.DrawMode, count: Int, type: Int, indices: Buffer?) {
        indices?.`when`(
            byte = { glDrawElements(mode.value, this) },
            short = { glDrawElements(mode.value, this) },
            int = { glDrawElements(mode.value, this) }
        ) ?: glDrawElements(mode.value, count, type, 0)
    }

    override fun genTextures(n: Int, textures: IntBuf) {
        glGenTextures(textures.get())
    }

    override fun bindTexture(target: Int, texture: Int) {
        glBindTexture(target, texture)
    }

    override fun activeTexture(texture: Int) {
        glActiveTexture(texture)
    }

    override fun texImage2D(target: Int, level: Int, bitmap: Bitmap, border: Int) {
        val buffer = createIntBuffer(bitmap.pixels)
        buffer.`when`(
            byte = {
                glTexImage2D(
                    target,
                    level,
                    GL_RGBA,
                    bitmap.width,
                    bitmap.height,
                    border,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    this
                )
            },
            short = {
                glTexImage2D(
                    target,
                    level,
                    GL_RGBA,
                    bitmap.width,
                    bitmap.height,
                    border,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    this
                )
            },
            int = {
                glTexImage2D(
                    target,
                    level,
                    GL_RGBA,
                    bitmap.width,
                    bitmap.height,
                    border,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    this
                )
            },
            float = {
                glTexImage2D(
                    target,
                    level,
                    GL_RGBA,
                    bitmap.width,
                    bitmap.height,
                    border,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    this
                )
            }
        )
    }

    override fun texParameteri(target: Int, pname: Int, param: Int) {
        glTexParameteri(target, pname, param)
    }

    override fun uniform1(location: Int, x: Int) {
        glUniform1i(location, x)
    }

    override fun uniform1(location: Int, x: Float) {
        glUniform1f(location, x)
    }

    override fun uniformMatrix4fv(
        location: Int,
        count: Int,
        transpose: Boolean,
        value: FloatBuf
    ) {
        glUniformMatrix4fv(location, transpose, value.get())
    }

    override fun getError() : Int {
        return glGetError()
    }
}

fun Buffer.`when`(
    byte: java.nio.ByteBuffer.() -> Unit = {},
    short: java.nio.ShortBuffer.() -> Unit = {},
    int: java.nio.IntBuffer.() -> Unit = {},
    float: java.nio.FloatBuffer.() -> Unit = {},
) {
    when (this) {
        is ByteBuffer -> byte(get())
        is ShortBuffer -> short(get())
        is IntBuffer -> int(get())
        is FloatBuffer -> float(get())
    }
}