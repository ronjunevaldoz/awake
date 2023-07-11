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

    fun scale(x: Float, y: Float, z: Float): Mat4f {
        val scaleMatrix = obtain()
        scaleMatrix.identity()
        scaleMatrix.m00 = x
        scaleMatrix.m11 = y
        scaleMatrix.m22 = z

        this * scaleMatrix

        recycle(scaleMatrix)
        return this
    }

    fun translate(x: Float, y: Float, z: Float): Mat4f {
        val translationMatrix = obtain()
        translationMatrix.identity()
        translationMatrix.m03 = x
        translationMatrix.m13 = y
        translationMatrix.m23 = z

        this * translationMatrix

        recycle(translationMatrix)

        return this
    }

    // Rotate around the x-axis
    fun rotateX(angleRad: Float): Mat4f {
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

        return this
    }

    // Rotate around the y-axis
    fun rotateY(angleRad: Float): Mat4f {
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

        return this
    }

    // Rotate around the z-axis
    fun rotateZ(angleRad: Float): Mat4f {
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

        return this
    }

    fun frustum(
        left: Float,
        right: Float,
        bottom: Float,
        top: Float,
        near: Float,
        far: Float
    ): Mat4f {
        identity()

        val width = right - left
        val height = top - bottom
        val depth = far - near

        m00 = 2.0f * near / width
        m11 = 2.0f * near / height
        m20 = (right + left) / width
        m21 = (top + bottom) / height
        m22 = -(far + near) / depth
        m23 = -1.0f
        m32 = -2.0f * far * near / depth

        return this
    }

    fun setLookAt(
        eyeX: Float,
        eyeY: Float,
        eyeZ: Float,
        centerX: Float,
        centerY: Float,
        centerZ: Float,
        upX: Float,
        upY: Float,
        upZ: Float
    ): Mat4f {
        return setLookAt(
            Vec3f(eyeX, eyeY, eyeZ),
            Vec3f(centerX, centerY, centerZ),
            Vec3f(upX, upY, upZ)
        )
    }

    fun setLookAt(
        eye: Vec3f, center: Vec3f, up: Vec3f
    ): Mat4f {
        identity()

        val f = (center - eye).normalize() // forward
        val s = f.cross(up).normalize() // side
        val u = s.cross(f) // up

        m00 = s.x
        m01 = s.y
        m02 = s.z
        m10 = u.x
        m11 = u.y
        m12 = u.z
        m20 = -f.x
        m21 = -f.y
        m22 = -f.z
        m30 = -s.dot(eye)
        m31 = -u.dot(eye)
        m32 = f.dot(eye)

        return this
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