package io.github.ronjunevaldoz.awake.core.shader

import io.github.ronjunevaldoz.awake.core.math.Matrix4f
import io.github.ronjunevaldoz.awake.core.math.Vec3f
import io.github.ronjunevaldoz.awake.core.math.Vec4f

interface UniformBinder {
    fun getLocation(name: String): Int
    fun set(location: Int, value: Int)
    fun set(location: Int, value: Float)
    fun set(location: Int, x: Float, y: Float, z: Float)
    fun set(location: Int, x: Float, y: Float, z: Float, w: Float)
    fun set(location: Int, value: Vec3f)
    fun set(location: Int, value: Vec4f)
    fun set(location: Int, value: Boolean)
    fun set(location: Int, value: Matrix4f)
    fun set(location: Int, matrices: List<Matrix4f>)
}