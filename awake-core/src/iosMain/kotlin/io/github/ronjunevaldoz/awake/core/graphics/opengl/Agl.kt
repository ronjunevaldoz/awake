package io.github.ronjunevaldoz.awake.core.graphics.opengl

import io.github.ronjunevaldoz.awake.core.graphics.image.Bitmap
import io.github.ronjunevaldoz.awake.core.memory.Buffer
import io.github.ronjunevaldoz.awake.core.memory.ByteBuffer
import io.github.ronjunevaldoz.awake.core.memory.FloatBuf
import io.github.ronjunevaldoz.awake.core.memory.FloatBuffer
import io.github.ronjunevaldoz.awake.core.memory.IntBuf
import io.github.ronjunevaldoz.awake.core.memory.IntBuffer
import io.github.ronjunevaldoz.awake.core.memory.ShortBuffer
import kotlinx.cinterop.ByteVar
import kotlinx.cinterop.FloatVar
import kotlinx.cinterop.IntVar
import kotlinx.cinterop.ShortVar
import kotlinx.cinterop.cValuesOf
import kotlinx.cinterop.cstr
import kotlinx.cinterop.memScoped
import kotlinx.cinterop.refTo
import kotlinx.cinterop.toCPointer
import platform.gles2.GL_FALSE
import platform.gles2.GL_INFO_LOG_LENGTH
import platform.gles2.GL_RGBA
import platform.gles2.GL_TRUE
import platform.gles2.GL_UNSIGNED_BYTE
import platform.gles2.glActiveTexture
import platform.gles2.glAttachShader
import platform.gles2.glBindAttribLocation
import platform.gles2.glBindBuffer
import platform.gles2.glBindTexture
import platform.gles2.glBindVertexArrayOES
import platform.gles2.glBufferData
import platform.gles2.glClear
import platform.gles2.glClearColor
import platform.gles2.glCompileShader
import platform.gles2.glCreateProgram
import platform.gles2.glCreateShader
import platform.gles2.glDeleteBuffers
import platform.gles2.glDeleteProgram
import platform.gles2.glDeleteShader
import platform.gles2.glDeleteTextures
import platform.gles2.glDeleteVertexArraysOES
import platform.gles2.glDisableVertexAttribArray
import platform.gles2.glDrawArrays
import platform.gles2.glDrawElements
import platform.gles2.glEnableVertexAttribArray
import platform.gles2.glGenBuffers
import platform.gles2.glGenTextures
import platform.gles2.glGenVertexArraysOES
import platform.gles2.glGetAttribLocation
import platform.gles2.glGetError
import platform.gles2.glGetProgramInfoLog
import platform.gles2.glGetProgramiv
import platform.gles2.glGetShaderInfoLog
import platform.gles2.glGetShaderiv
import platform.gles2.glGetUniformLocation
import platform.gles2.glLinkProgram
import platform.gles2.glShaderSource
import platform.gles2.glTexImage2D
import platform.gles2.glTexParameteri
import platform.gles2.glUniform1f
import platform.gles2.glUniform1i
import platform.gles2.glUniformMatrix4fv
import platform.gles2.glUseProgram
import platform.gles2.glVertexAttribPointer
import platform.gles2.glViewport

internal actual object Agl : OpenGL {

    override fun clearColor(r: Float, g: Float, b: Float, a: Float) {
        glClearColor(r, g, b, a)
    }

    override fun clear(mask: Int) {
//        val bitMask = mask.fold(0) { acc, m -> acc or m.value }
        glClear(mask.toUInt())
    }

    override fun viewport(x: Int, y: Int, width: Int, height: Int) {
        glViewport(x, y, width, height)
    }

    override fun createShader(type: OpenGL.ShaderType): Int {
        return glCreateShader(type.value.toUInt()).toInt()
    }

    override fun shaderSource(shader: Int, content: String) {
        memScoped {
            glShaderSource(shader.toUInt(), 1, cValuesOf(content.cstr.ptr), null)
        }
    }

    override fun compileShader(shader: Int) {
        glCompileShader(shader.toUInt())
    }

    override fun getShaderInfoLog(shader: Int): String {
        val logLengthBuffer = IntArray(1)
        glGetShaderiv(shader.toUInt(), GL_INFO_LOG_LENGTH, logLengthBuffer.refTo(0))
        val logLength = logLengthBuffer[0]

        return if (logLength > 0) {
            val logBuffer = ByteArray(logLength)
            glGetShaderInfoLog(shader.toUInt(), logLength, null, logBuffer.refTo(0))
            logBuffer.decodeToString()
        } else {
            ""
        }
    }

    override fun getShaderiv(shader: Int, status: OpenGL.Status, buffer: IntBuf) {
        glGetShaderiv(shader.toUInt(), status.value.toUInt(), buffer.get())
    }

    override fun createProgram(): Int {
        return glCreateProgram().toInt()
    }

    override fun attachShader(program: Int, shader: Int) {
        glAttachShader(program.toUInt(), shader.toUInt())
    }

    override fun linkProgram(program: Int) {
        glLinkProgram(program.toUInt())
    }

    override fun getProgramInfoLog(program: Int): String {
        val logLengthBuffer = IntArray(1)
        glGetProgramiv(program.toUInt(), GL_INFO_LOG_LENGTH, logLengthBuffer.refTo(0))
        val logLength = logLengthBuffer[0]

        val logBuffer = ByteArray(logLength)
        glGetProgramInfoLog(program.toUInt(), logLength, null, logBuffer.refTo(0))
        return logBuffer.decodeToString()
    }

    override fun getProgramiv(program: Int, status: OpenGL.Status, buffer: IntBuf) {
        glGetProgramiv(program.toUInt(), status.value.toUInt(), buffer.get())
    }

    override fun deleteShader(shader: Int) {
        glDeleteShader(shader.toUInt())
    }

    override fun useProgram(program: Int) {
        glUseProgram(program.toUInt())
    }

    override fun deleteProgram(program: Int) {
        glDeleteProgram(program.toUInt())
    }

    override fun getUniformLocation(program: Int, name: String): Int {
        return glGetUniformLocation(program.toUInt(), name).also { location ->
            if (location == -1) throw Exception("Invalid value")
        }
    }

    override fun bindAttribLocation(program: ProgramId, index: Int, name: String) {
        glBindAttribLocation(program.toUInt(), index.toUInt(), name)
    }

    override fun getAttribLocation(program: Int, name: String): Int {
        return glGetAttribLocation(program.toUInt(), name).also { location ->
            if (location == -1) throw Exception("Invalid value")
        }
    }

    override fun vertexAttribPointer(
        index: Int,
        size: Int,
        type: Int,
        normalized: Boolean,
        stride: Int,
        ptr: Buffer?
    ) {
        val pointer = ptr?.get() ?:  0.toLong().toCPointer<ByteVar>()
        glVertexAttribPointer(
            indx = index.toUInt(),
            size = size,
            type = type.toUInt(),
            normalized = if (normalized) GL_TRUE.toUByte() else GL_FALSE.toUByte(),
            stride = stride,
            ptr = pointer
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
            indx = index.toUInt(),
            size = size,
            type = type.toUInt(),
            normalized = if (normalized) GL_TRUE.toUByte() else GL_FALSE.toUByte(),
            stride = stride,
            ptr = offset.toLong().toCPointer<ByteVar>()
        )
    }

    override fun enableVertexAttribArray(index: Int) {
        glEnableVertexAttribArray(index.toUInt())
    }

    override fun drawArrays(mode: Int, first: Int, count: Int) {
        glDrawArrays(mode.toUInt(), first, count)
    }

    override fun disableVertexAttribArray(index: Int) {
        glDisableVertexAttribArray(index.toUInt())
    }

    override fun genBuffers(n: Int, buffers: IntBuf) {
        glGenBuffers(n, buffers.get())
    }

    override fun bindBuffer(target: OpenGL.BufferType, buffer: BufferId) {
        glBindBuffer(target.value.toUInt(), buffer.toUInt())
    }

    override fun bufferData(target: OpenGL.BufferType, size: Long, data: Buffer, usage: OpenGL.DrawType) {
        val buffer = when(data) {
            is ByteBuffer -> data.get<ByteVar>()
            is ShortBuffer -> data.get<ShortVar>()
            is IntBuffer -> data.get<IntVar>()
            is FloatBuffer -> data.get<FloatVar>()
            else -> throw Exception("Buffer not supported")
        }
        glBufferData(target.value.toUInt(), size, buffer, usage.value.toUInt())
    }

    override fun deleteBuffers(n: Int, buffers: IntBuf) {
        glDeleteBuffers(n, buffers.get())
    }

    override fun deleteVertexArrays(n: Int, arrays: IntBuf) {
        glDeleteVertexArraysOES(n, arrays.get())
    }

    override fun deleteTextures(n: Int, textures: IntBuf) {
        glDeleteTextures(n, textures.get())
    }

    override fun genVertexArrays(n: Int, arrays: IntBuf) {
        glGenVertexArraysOES(n, arrays.get())
    }

    override fun bindVertexArray(array: ArrayId) {
        glBindVertexArrayOES(array.toUInt())
    }

    override fun drawElements(mode: OpenGL.DrawMode, count: Int, type: Int, indices: Buffer?) {
        val buffer = indices?.get() ?: 0.toLong().toCPointer<ByteVar>()

        glDrawElements(mode.value.toUInt(), count, type.toUInt(), buffer)
    }

    override fun genTextures(n: Int, textures: IntBuf) {
        glGenTextures(n, textures.get())
    }

    override fun bindTexture(target: Int, texture: Int) {
        glBindTexture(target.toUInt(), texture.toUInt())
    }

    override fun activeTexture(texture: Int) {
        glActiveTexture(texture.toUInt())
    }

    override fun texImage2D(target: Int, level: Int, bitmap: Bitmap, border: Int) {
        glTexImage2D(
            target = target.toUInt(),
            level = level,
            internalformat = GL_RGBA,
            width = bitmap.width,
            height = bitmap.height,
            border = 0,
            format = GL_RGBA,
            type = GL_UNSIGNED_BYTE,
            pixels = bitmap.pixels.refTo(0)
        )
    }

    override fun texParameteri(target: Int, pname: Int, param: Int) {
        glTexParameteri(target.toUInt(), pname.toUInt(), param)
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
        glUniformMatrix4fv(location, count, if (transpose) GL_TRUE.toUByte() else GL_FALSE.toUByte(), value.get())
    }

    override fun getError(): Int {
        return glGetError().toInt()
    }
}