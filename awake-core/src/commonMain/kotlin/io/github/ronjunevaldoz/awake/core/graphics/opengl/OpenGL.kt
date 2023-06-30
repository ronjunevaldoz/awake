package io.github.ronjunevaldoz.awake.core.graphics.opengl

import io.github.ronjunevaldoz.awake.core.graphics.image.Bitmap
import io.github.ronjunevaldoz.awake.core.memory.Buffer
import io.github.ronjunevaldoz.awake.core.memory.FloatBuf
import io.github.ronjunevaldoz.awake.core.memory.IntBuf
import kotlin.jvm.JvmInline

typealias ProgramId = Int
typealias ShaderId = Int
typealias BufferId = Int
typealias ArrayId = Int

// treated as typealias
@JvmInline
value class Id(val value: Int)


interface OpenGL {
    enum class Version {
        ES1,
        ES2,
        ES3,
    }

    enum class Status(val value: Int) {
        Compile(Constants.GL_COMPILE_STATUS),
        Link(Constants.GL_LINK_STATUS),
        Delete(Constants.GL_DELETE_STATUS),
        Validate(Constants.GL_VALIDATE_STATUS)
    }

    enum class BufferBit(val value: Int) {
        Color(Constants.GL_COLOR_BUFFER_BIT),
        Depth(Constants.GL_DEPTH_BUFFER_BIT),
        Stencil(Constants.GL_STENCIL_BUFFER_BIT)
    }

    enum class DrawMode(val value: Int) {
        Triangles(Constants.GL_TRIANGLES)
    }

    enum class ShaderType(val value: Int) {
        Vertex(Constants.GL_VERTEX_SHADER),
        Fragment(Constants.GL_FRAGMENT_SHADER)
    }

    enum class BufferType(val value: Int) {
        Array(Constants.GL_ARRAY_BUFFER),
        ElementArray(Constants.GL_ELEMENT_ARRAY_BUFFER)
    }

    enum class DrawType(val value: Int) {
        Static(Constants.GL_STATIC_DRAW)
    }

    fun clearColor(r: Float, g: Float, b: Float, a: Float)
    fun clear(mask: Int)
    fun viewport(x: Int, y: Int, width: Int, height: Int)

    // shader
    fun createShader(type: ShaderType): Int
    fun shaderSource(shader: ShaderId, content: String)
    fun compileShader(shader: ShaderId)
    fun getShaderInfoLog(shader: ShaderId): String
    fun getShaderiv(shader: ShaderId, status: Status, buffer: IntBuf)
    fun createProgram(): ProgramId
    fun attachShader(program: ProgramId, shader: ShaderId)
    fun linkProgram(program: ProgramId)
    fun getProgramInfoLog(program: ProgramId): String
    fun getProgramiv(program: ProgramId, status: Status, buffer: IntBuf)
    fun deleteShader(shader: ShaderId)
    fun useProgram(program: ProgramId)
    fun deleteProgram(program: ProgramId)

    // Uniforms
    fun getUniformLocation(program: ProgramId, name: String): Int

    // Attributes
    fun bindAttribLocation(program: ProgramId, index: Int, name: String)
    fun getAttribLocation(program: ProgramId, name: String): Int
    fun vertexAttribPointer(
        index: Int,
        size: Int,
        type: Int,
        normalized: Boolean,
        stride: Int,
        ptr: Buffer? = null
    )

    fun vertexAttribPointer(
        index: Int,
        size: Int,
        type: Int,
        normalized: Boolean,
        stride: Int,
        offset: Int
    )

    fun enableVertexAttribArray(index: Int)
    fun drawArrays(mode: Int, first: Int, count: Int)
    fun disableVertexAttribArray(index: Int)

    // buffers
    fun genBuffers(n: Int, buffers: IntBuf)
    fun bindBuffer(target: BufferType, buffer: BufferId)
    fun bufferData(
        target: BufferType,
        size: Long,
        data: Buffer,
        usage: DrawType
    )

    fun deleteBuffers(n: Int, buffers: IntBuf)
    fun deleteVertexArrays(n: Int, arrays: IntBuf)
    fun deleteTextures(n: Int, textures: IntBuf)

    // available only for android gl 3.0 or up and for ios use EOS which available in 2.0
    fun genVertexArrays(n: Int, arrays: IntBuf)
    fun bindVertexArray(array: ArrayId)
    fun drawElements(mode: DrawMode, count: Int, type: Int, indices: Buffer? = null)

    fun genTextures(n: Int, textures: IntBuf)
    fun bindTexture(target: Int, texture: Int)
    fun activeTexture(texture: Int)
    fun texImage2D(target: Int, level: Int, bitmap: Bitmap, border: Int)
    fun texParameteri(target: Int, pname: Int, param: Int)
    fun uniform1(location: Int, x: Int)
    fun uniform1(location: Int, x: Float)
    fun uniformMatrix4fv(location: Int, count: Int, transpose: Boolean, value: FloatBuf)
    fun getError(): Int
}

