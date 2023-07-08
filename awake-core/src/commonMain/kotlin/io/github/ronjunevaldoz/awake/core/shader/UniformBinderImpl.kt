package io.github.ronjunevaldoz.awake.core.shader

import io.github.ronjunevaldoz.awake.core.AwakeContext
import io.github.ronjunevaldoz.awake.core.math.Matrix4f
import io.github.ronjunevaldoz.awake.core.math.Vec3f
import io.github.ronjunevaldoz.awake.core.math.Vec4f
import io.github.ronjunevaldoz.awake.core.utils.BufferUtils

class UniformBinderImpl(val program: Int) : UniformBinder {
    private val uniforms: MutableMap<String, Int> = mutableMapOf()
    override fun getLocation(name: String): Int {
        return checkNotNull(if (uniforms.containsKey(name)) {
            uniforms[name]
        } else {
            uniforms.getOrPut(name) {
                AwakeContext.gl.getUniformLocation(program, name)
            }
        }) {
            "Uniform `$name` not found"
        }
    }

    override fun set(location: Int, value: Int) {
        return AwakeContext.gl.uniform(location, value)
    }

    override fun set(location: Int, value: Float) {
        return AwakeContext.gl.uniform(location, value)
    }

    override fun set(location: Int, x: Float, y: Float, z: Float) {
        return AwakeContext.gl.uniform(location, x, y, z)
    }

    override fun set(location: Int, x: Float, y: Float, z: Float, w: Float) {
        return AwakeContext.gl.uniform(location, x, y, z, w)
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
        val buffer = BufferUtils.allocateFloat(16)
        buffer.put(value.data)
        AwakeContext.gl.uniformMatrix4fv(location, 0, false, buffer)
    }

    override fun set(location: Int, matrices: List<Matrix4f>) {
        val buffer = BufferUtils.allocateFloat(16 * matrices.size)
        matrices.forEachIndexed { i, mat ->
            mat[16 * i, buffer]
        }
        AwakeContext.gl.uniformMatrix4fv(location, 0, false, buffer)
    }
}