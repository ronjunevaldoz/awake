package io.github.ronjunevaldoz.awake.core.graphics.opengl

import android.opengl.GLES20.GL_RGBA
import android.opengl.GLES20.GL_UNSIGNED_BYTE
import android.opengl.GLES20.glActiveTexture
import android.opengl.GLES20.glAttachShader
import android.opengl.GLES20.glBindAttribLocation
import android.opengl.GLES20.glBindBuffer
import android.opengl.GLES20.glBindTexture
import android.opengl.GLES20.glBufferData
import android.opengl.GLES20.glClear
import android.opengl.GLES20.glClearColor
import android.opengl.GLES20.glCompileShader
import android.opengl.GLES20.glCreateProgram
import android.opengl.GLES20.glCreateShader
import android.opengl.GLES20.glDeleteBuffers
import android.opengl.GLES20.glDeleteProgram
import android.opengl.GLES20.glDeleteShader
import android.opengl.GLES20.glDeleteTextures
import android.opengl.GLES20.glDisableVertexAttribArray
import android.opengl.GLES20.glDrawArrays
import android.opengl.GLES20.glDrawElements
import android.opengl.GLES20.glEnableVertexAttribArray
import android.opengl.GLES20.glGenBuffers
import android.opengl.GLES20.glGenTextures
import android.opengl.GLES20.glGetAttribLocation
import android.opengl.GLES20.glGetError
import android.opengl.GLES20.glGetProgramInfoLog
import android.opengl.GLES20.glGetProgramiv
import android.opengl.GLES20.glGetShaderInfoLog
import android.opengl.GLES20.glGetShaderiv
import android.opengl.GLES20.glGetUniformLocation
import android.opengl.GLES20.glLinkProgram
import android.opengl.GLES20.glShaderSource
import android.opengl.GLES20.glTexImage2D
import android.opengl.GLES20.glTexParameteri
import android.opengl.GLES20.glUniform1f
import android.opengl.GLES20.glUniform1i
import android.opengl.GLES20.glUniformMatrix4fv
import android.opengl.GLES20.glUseProgram
import android.opengl.GLES20.glVertexAttribPointer
import android.opengl.GLES20.glViewport
import android.opengl.GLES30.glBindVertexArray
import android.opengl.GLES30.glDeleteVertexArrays
import android.opengl.GLES30.glGenVertexArrays
import io.github.ronjunevaldoz.awake.core.graphics.image.Bitmap
import io.github.ronjunevaldoz.awake.core.memory.Buffer
import io.github.ronjunevaldoz.awake.core.memory.FloatBuf
import io.github.ronjunevaldoz.awake.core.memory.IntBuf
import io.github.ronjunevaldoz.awake.core.memory.createIntBuffer

internal actual object Agl : OpenGL {
    override fun clearColor(r: Float, g: Float, b: Float, a: Float) {
        glClearColor(r, g, b, a)
    }

    override fun clear(mask: Int) {
//        val bitMask = mask.fold(0) { acc, m -> acc or m.value }
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
        if (ptr == null) {
            glVertexAttribPointer(
                index,
                size,
                type,
                normalized,
                stride,
                0
            )
        } else {
            glVertexAttribPointer(
                index,
                size,
                type,
                normalized,
                stride,
                ptr.get()
            )
        }
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
            offset
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
        glGenBuffers(n, buffers.get())
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
        glBufferData(
            target.value,
            size.toInt(),
            data.get(),
            usage.value
        )
    }

    override fun deleteBuffers(n: Int, buffers: IntBuf) {
        glDeleteBuffers(n, buffers.get())
    }

    override fun deleteVertexArrays(n: Int, arrays: IntBuf) {
        glDeleteVertexArrays(n, arrays.get())
    }

    override fun deleteTextures(n: Int, textures: IntBuf) {
        glDeleteTextures(n, textures.get())
    }

    override fun genVertexArrays(n: Int, arrays: IntBuf) {
        glGenVertexArrays(n, arrays.get())
    }

    override fun bindVertexArray(array: ArrayId) {
        glBindVertexArray(array)
    }

    override fun drawElements(mode: OpenGL.DrawMode, count: Int, type: Int, indices: Buffer?) {
        if (indices == null) {
            glDrawElements(mode.value, count, type, 0)
        } else {
            glDrawElements(mode.value, count, type, indices.get())
        }
    }

    override fun genTextures(n: Int, textures: IntBuf) {
        glGenTextures(n, textures.get())
    }

    override fun bindTexture(target: Int, texture: Int) {
        glBindTexture(target, texture)
    }

    override fun activeTexture(texture: Int) {
        glActiveTexture(texture)
    }

    override fun texImage2D(target: Int, level: Int, bitmap: Bitmap, border: Int) {
        val buffer = createIntBuffer(bitmap.pixels)
        glTexImage2D(
            target,
            level,
            GL_RGBA,
            bitmap.width,
            bitmap.height,
            border,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            buffer.get()
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
        glUniformMatrix4fv(location, count, transpose, value.get())
    }

    override fun getError(): Int {
        return glGetError()
    }
}