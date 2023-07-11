package io.github.ronjunevaldoz.awake.core.math

import kotlin.math.sqrt

data class Vec3f(var x: Float = 1f, var y: Float = 1f, var z: Float = 1f) {
    fun length3(): Float {
        return sqrt(x * x + y * y + z * z)
    }

    fun normalize(): Vec3f {
        val length = length3()
        if (length != 0.0f) {
            val invLength = 1.0f / length
            x *= invLength
            y *= invLength
            z *= invLength
        }
        return this
    }

    fun dot(other: Vec3f): Float {
        return x * other.x + y * other.y + z * other.z
    }

    fun cross(other: Vec3f): Vec3f {
        return Vec3f(
            x = y * other.z - z * other.y,
            y = z * other.x - x * other.z,
            z = x * other.y - y * other.x
        )
    }

    operator fun minus(other: Vec3f): Vec3f {
        return Vec3f(
            x - other.x,
            y - other.y,
            z - other.z,
        )
    }
}

data class Vec4f(var x: Float = 1f, var y: Float = 1f, var z: Float = 1f, var w: Float = 1f) {
    operator fun set(x: Float, y: Float, z: Float, w: Float) {
        this.x = x
        this.y = y
        this.z = z
        this.w = w
    }

    fun normalize() {
        val length = length3()
        if (length != 0.0f) {
            val invLength = 1.0f / length
            x *= invLength
            y *= invLength
            z *= invLength
        }
    }

    fun dot(other: Vec4f): Float {
        return x * other.x + y * other.y + z * other.z + w * other.w
    }

    operator fun minus(other: Vec4f): Vec4f {
        return Vec4f(x - other.x, y - other.y, z - other.z, w - other.w)
    }

    operator fun times(scalar: Float): Vec4f {
        return Vec4f(x * scalar, y * scalar, z * scalar, w * scalar)
    }

    operator fun plus(other: Vec4f): Vec4f {
        return Vec4f(x + other.x, y + other.y, z + other.z, w + other.w)
    }

    fun length3(): Float {
        return sqrt(x * x + y * y + z * z)
    }

    fun transform(aMatrix: Mat4f) {
        val x = this.x
        val y = this.y
        val z = this.z
        val w = this.w

        val resultX = aMatrix.m00.times(x)
            ?.plus(aMatrix.m10.times(y))
            ?.plus(aMatrix.m20.times(z))
            ?.plus(aMatrix.m30.times(w))

        val resultY = aMatrix.m01?.times(x)
            ?.plus(aMatrix.m11.times(y))
            ?.plus(aMatrix.m21.times(z))
            ?.plus(aMatrix.m31.times(w))

        val resultZ = aMatrix?.m02?.times(x)
            ?.plus(aMatrix.m12.times(y))
            ?.plus(aMatrix.m22.times(z))
            ?.plus(aMatrix.m32.times(w))

        val resultW = aMatrix?.m03?.times(x)
            ?.plus(aMatrix.m13.times(y))
            ?.plus(aMatrix.m23.times(z))
            ?.plus(aMatrix.m33.times(w))

        this.x = resultX ?: 0.0f
        this.y = resultY ?: 0.0f
        this.z = resultZ ?: 0.0f
        this.w = resultW ?: 0.0f
    }

    fun makePixelCoords(
        aMatrix: Mat4f,
        aViewportWidth: Int,
        aViewportHeight: Int
    ) {
        transform(aMatrix)

        // Make coordinates as homogeneous
        x /= w
        y /= w
        z /= w
        w = 1.0f

        // Now the vector is normalized to the range [-1.0, 1.0]
        // Normalize values into NDC.
        x = (0.5f + x * 0.5f)
        y = (0.5f + y * 0.5f)
        z = 0.5f + z * 0.5f
        w = 1.0f

        // Currently the values are clipped to the [0.0, 1.0] range
        // Move coordinates into window space (in pixels)
        x *= aViewportWidth.toFloat()
        y *= aViewportHeight.toFloat()
    }
}