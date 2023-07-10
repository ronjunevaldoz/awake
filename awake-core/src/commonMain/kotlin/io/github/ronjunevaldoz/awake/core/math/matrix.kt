package io.github.ronjunevaldoz.awake.core.math

import io.github.ronjunevaldoz.awake.core.memory.FloatBuf
import kotlin.math.cos
import kotlin.math.sin

class Mat4f {
    val data: FloatArray = FloatArray(16)

    var m00: Float
        get() = data[0]
        set(value) {
            data[0] = value
        }

    var m01: Float
        get() = data[1]
        set(value) {
            data[1] = value
        }

    var m02: Float
        get() = data[2]
        set(value) {
            data[2] = value
        }

    var m03: Float
        get() = data[3]
        set(value) {
            data[3] = value
        }

    var m10: Float
        get() = data[4]
        set(value) {
            data[4] = value
        }

    var m11: Float
        get() = data[5]
        set(value) {
            data[5] = value
        }

    var m12: Float
        get() = data[6]
        set(value) {
            data[6] = value
        }

    var m13: Float
        get() = data[7]
        set(value) {
            data[7] = value
        }

    var m20: Float
        get() = data[8]
        set(value) {
            data[8] = value
        }

    var m21: Float
        get() = data[9]
        set(value) {
            data[9] = value
        }

    var m22: Float
        get() = data[10]
        set(value) {
            data[10] = value
        }

    var m23: Float
        get() = data[11]
        set(value) {
            data[11] = value
        }

    var m30: Float
        get() = data[12]
        set(value) {
            data[12] = value
        }

    var m31: Float
        get() = data[13]
        set(value) {
            data[13] = value
        }

    var m32: Float
        get() = data[14]
        set(value) {
            data[14] = value
        }

    var m33: Float
        get() = data[15]
        set(value) {
            data[15] = value
        }

    init {
        identity()
    }

    fun identity() {
        for (i in 0 until 16) {
            data[i] = if (i % 5 == 0) 1.0f else 0.0f
        }
    }

    fun translate(x: Float, y: Float, z: Float) {
        val translationMatrix = obtain()
        translationMatrix.identity()
        translationMatrix.m30 = x
        translationMatrix.m31 = y
        translationMatrix.m32 = z

        this * translationMatrix

        recycle(translationMatrix)
    }

    fun rotate(angleRad: Float) {
        val rotationMatrix = obtain()
        rotationMatrix.identity()
        val cos = cos(angleRad)
        val sin = sin(angleRad)
        rotationMatrix.m00 = cos
        rotationMatrix.m01 = -sin
        rotationMatrix.m10 = sin
        rotationMatrix.m11 = cos

        this * rotationMatrix

        recycle(rotationMatrix)
    }

    // Rotate around the x-axis
    fun rotateX(angleRad: Float) {
        val rotationMatrix = obtain()
        rotationMatrix.identity()
        val sin = sin(angleRad)
        val cos = cos(angleRad)

        rotationMatrix.m11 = cos
        rotationMatrix.m12 = sin
        rotationMatrix.m21 = -sin
        rotationMatrix.m22 = cos

        this * rotationMatrix

        recycle(rotationMatrix)
    }

    // Rotate around the y-axis
    fun rotateY(angleRad: Float) {
        val rotationMatrix = obtain()
        rotationMatrix.identity()
        val sin = sin(angleRad)
        val cos = cos(angleRad)

        rotationMatrix.m00 = cos
        rotationMatrix.m02 = -sin
        rotationMatrix.m20 = sin
        rotationMatrix.m22 = cos

        this * rotationMatrix

        recycle(rotationMatrix)
    }

    // Rotate around the z-axis
    fun rotateZ(angleRad: Float) {
        val rotationMatrix = obtain()
        rotationMatrix.identity()
        val sin = sin(angleRad)
        val cos = cos(angleRad)

        rotationMatrix.m00 = cos
        rotationMatrix.m01 = -sin
        rotationMatrix.m10 = sin
        rotationMatrix.m11 = cos

        this * rotationMatrix

        recycle(rotationMatrix)
    }

    fun translateAndRotate(x: Float, y: Float, z: Float, angleRad: Float) {
        translate(x, y, z)
        rotate(angleRad)
    }

    operator fun get(i: Int, buffer: FloatBuf) {
        for (j in 0 until 16) {
            buffer[16 * i + j] = data[j]
        }
    }

    operator fun Mat4f.times(other: Mat4f): Mat4f {
        for (i in 0 until 4) {
            for (j in 0 until 4) {
                data[i * 4 + j] =
                    this.data[i * 4] * other.data[j] +
                            this.data[i * 4 + 1] * other.data[j + 4] +
                            this.data[i * 4 + 2] * other.data[j + 8] +
                            this.data[i * 4 + 3] * other.data[j + 12]
            }
        }
        return this
    }

    companion object {
        private val pool: MutableList<Mat4f> = mutableListOf()

        fun obtain(): Mat4f {
            return if (pool.isNotEmpty()) {
                pool.removeAt(pool.lastIndex).apply {
                    identity()
                }
            } else {
                Mat4f()
            }
        }

        fun recycle(matrix: Mat4f) {
            matrix.identity()
            pool.add(matrix)
        }
    }
}