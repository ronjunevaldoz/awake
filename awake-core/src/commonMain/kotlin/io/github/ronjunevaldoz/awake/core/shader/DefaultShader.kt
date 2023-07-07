package io.github.ronjunevaldoz.awake.core.shader

import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.math.Matrix4f
import io.github.ronjunevaldoz.awake.core.math.Vec3f
import io.github.ronjunevaldoz.awake.core.math.Vec4f
import io.github.ronjunevaldoz.awake.core.utils.BufferUtils

abstract class DefaultShader : BaseShader() {
    val attributeBinder: AttributeBinder by lazy { AttributeBinder(program) }
    var position by Attribute()
    var color by Attribute()
    var texCoords by Attribute()

    private val transMatrix by Uniform()

    override fun compile() {
        super.compile()
        bindAttributes()
    }

    private fun bindAttributes() {
        position = 0
        color = 1
        texCoords = 2
    }

    override fun getUniformLocation(name: String): Int {
        return gl.getUniformLocation(program, name)
    }

    override fun set(location: Int, value: Int) {
        return gl.uniform(location, value)
    }

    override fun set(location: Int, value: Float) {
        return gl.uniform(location, value)
    }

    override fun set(location: Int, x: Float, y: Float, z: Float) {
        return gl.uniform(location, x, y, z)
    }

    override fun set(location: Int, x: Float, y: Float, z: Float, w: Float) {
        return gl.uniform(location, x, y, z, w)
    }

    override fun set(location: Int, value: Vec3f) {
        set(location, value.x, value.y, value.z)
    }

    override fun set(location: Int, value: Vec4f) {
        set(location, value.x, value.y, value.z, value.w)
    }

    override fun set(location: Int, value: Boolean) {
        set(location, if (value) 1 else 0)
    }

    override fun set(location: Int, value: Matrix4f) {
        val buffer = BufferUtils.floatBuffer(16)
        buffer.put(value.data)
        gl.uniformMatrix4fv(location, 0, false, buffer)
    }

    override fun set(location: Int, matrices: List<Matrix4f>) {
        val buffer = BufferUtils.floatBuffer(16 * matrices.size)
        matrices.forEachIndexed { i, mat ->
            mat[16 * i, buffer]
        }
        gl.uniformMatrix4fv(location, 0, false, buffer)
    }
}