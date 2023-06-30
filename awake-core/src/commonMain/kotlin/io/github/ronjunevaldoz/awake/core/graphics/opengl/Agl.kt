package io.github.ronjunevaldoz.awake.core.graphics.opengl

import io.github.ronjunevaldoz.awake.core.graphics.image.Bitmap
import io.github.ronjunevaldoz.awake.core.memory.Buffer
import io.github.ronjunevaldoz.awake.core.memory.FloatBuf
import io.github.ronjunevaldoz.awake.core.memory.IntBuf


internal expect object Agl : OpenGL
internal object AglDebuggable : OpenGL {
    override fun clearColor(r: Float, g: Float, b: Float, a: Float) {
        Agl.clearColor(r, g, b, a)
        checkGL()
    }

    override fun clear(mask: Int) {
        Agl.clear(mask)
        checkGL()
    }

    override fun viewport(x: Int, y: Int, width: Int, height: Int) {
        Agl.viewport(x, y, width, height)
        checkGL()
    }

    override fun createShader(type: OpenGL.ShaderType): Int {
        return Agl.createShader(type).apply {
            checkGL()
        }
    }

    override fun shaderSource(shader: ShaderId, content: String) {
        Agl.shaderSource(shader, content)
        checkGL()
    }

    override fun compileShader(shader: ShaderId) {
        Agl.compileShader(shader)
        checkGL()
    }

    override fun getShaderInfoLog(shader: ShaderId): String {
        return Agl.getShaderInfoLog(shader).apply {
            checkGL()
        }
    }

    override fun getShaderiv(shader: ShaderId, status: OpenGL.Status, buffer: IntBuf) {
        Agl.getShaderiv(shader, status, buffer)
        checkGL()
    }

    override fun createProgram(): ProgramId {
        return Agl.createProgram().apply {
            checkGL()
        }
    }

    override fun attachShader(program: ProgramId, shader: ShaderId) {
        Agl.attachShader(program, shader)
        checkGL()
    }

    override fun linkProgram(program: ProgramId) {
        Agl.linkProgram(program)
        checkGL()
    }

    override fun getProgramInfoLog(program: ProgramId): String {
        return Agl.getProgramInfoLog(program).apply {
            checkGL()
        }
    }

    override fun getProgramiv(program: ProgramId, status: OpenGL.Status, buffer: IntBuf) {
        Agl.getProgramiv(program, status, buffer)
        checkGL()
    }

    override fun deleteShader(shader: ShaderId) {
        Agl.deleteShader(shader)
        checkGL()
    }

    override fun useProgram(program: ProgramId) {
        Agl.useProgram(program)
        checkGL()
    }

    override fun deleteProgram(program: ProgramId) {
        Agl.deleteProgram(program)
        checkGL()
    }

    override fun getUniformLocation(program: ProgramId, name: String): Int {
        return Agl.getUniformLocation(program, name).apply {
            checkGL()
        }
    }

    override fun bindAttribLocation(program: ProgramId, index: Int, name: String) {
        Agl.bindAttribLocation(program, index, name)
        checkGL()
    }

    override fun getAttribLocation(program: ProgramId, name: String): Int {
        return Agl.getAttribLocation(program, name).apply {
            checkGL()
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
        Agl.vertexAttribPointer(index, size, type, normalized, stride, ptr)
        checkGL()
    }

    override fun vertexAttribPointer(
        index: Int,
        size: Int,
        type: Int,
        normalized: Boolean,
        stride: Int,
        offset: Int
    ) {
        Agl.vertexAttribPointer(index, size, type, normalized, stride, offset)
        checkGL()
    }

    override fun enableVertexAttribArray(index: Int) {
        Agl.enableVertexAttribArray(index)
        checkGL()
    }

    override fun drawArrays(mode: Int, first: Int, count: Int) {
        Agl.drawArrays(mode, first, count)
        checkGL()
    }

    override fun disableVertexAttribArray(index: Int) {
        Agl.disableVertexAttribArray(index)
        checkGL()
    }

    override fun genBuffers(n: Int, buffers: IntBuf) {
        Agl.genBuffers(n, buffers)
        checkGL()
    }

    override fun bindBuffer(target: OpenGL.BufferType, buffer: BufferId) {
        Agl.bindBuffer(target, buffer)
        checkGL()
    }

    override fun bufferData(
        target: OpenGL.BufferType,
        size: Long,
        data: Buffer,
        usage: OpenGL.DrawType
    ) {
        Agl.bufferData(target, size, data, usage)
        checkGL()
    }

    override fun deleteBuffers(n: Int, buffers: IntBuf) {
        Agl.deleteBuffers(n, buffers)
        checkGL()
    }

    override fun deleteVertexArrays(n: Int, arrays: IntBuf) {
        Agl.deleteVertexArrays(n, arrays)
        checkGL()
    }

    override fun deleteTextures(n: Int, textures: IntBuf) {
        Agl.deleteTextures(n, textures)
        checkGL()
    }

    override fun genVertexArrays(n: Int, arrays: IntBuf) {
        Agl.genVertexArrays(n, arrays)
        checkGL()
    }

    override fun bindVertexArray(array: ArrayId) {
        Agl.bindVertexArray(array)
        checkGL()
    }

    override fun drawElements(mode: OpenGL.DrawMode, count: Int, type: Int, indices: Buffer?) {
        Agl.drawElements(mode, count, type, indices)
        checkGL()
    }

    override fun genTextures(n: Int, textures: IntBuf) {
        Agl.genTextures(n, textures)
        checkGL()
    }

    override fun bindTexture(target: Int, texture: Int) {
        Agl.bindTexture(target, texture)
        checkGL()
    }

    override fun activeTexture(texture: Int) {
        Agl.activeTexture(texture)
        checkGL()
    }

    override fun texImage2D(target: Int, level: Int, bitmap: Bitmap, border: Int) {
        Agl.texImage2D(target, level, bitmap, border)
        checkGL()
    }

    override fun texParameteri(target: Int, pname: Int, param: Int) {
        Agl.texParameteri(target, pname, param)
        checkGL()
    }

    override fun uniform1(location: Int, x: Int) {
        Agl.uniform1(location, x)
        checkGL()
    }

    override fun uniform1(location: Int, x: Float) {
        Agl.uniform1(location, x)
        checkGL()
    }

    override fun uniformMatrix4fv(location: Int, count: Int, transpose: Boolean, value: FloatBuf) {
        Agl.uniformMatrix4fv(location, count, transpose, value)
        checkGL()
    }

    override fun getError(): Int {
        return Agl.getError()
    }
}