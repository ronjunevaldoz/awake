package io.github.ronjunevaldoz.awake.core.math

import io.github.ronjunevaldoz.awake.core.memory.FloatBuf

class Matrix4f {
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

    operator fun get(i: Int, buffer: FloatBuf) {
        for (j in 0 until 16) {
            buffer[16 * i + j] = data[j]
        }
    }
}

fun degreesToRadians(degrees: Float): Float {
    return degrees * (kotlin.math.PI.toFloat() / 180.0f)
}

fun Matrix4f.translateAndRotate(x: Float, y: Float, z: Float, angle: Float) {
    val translationMatrix = Matrix4f()
    translationMatrix.identity()
    translationMatrix.m30 = x
    translationMatrix.m31 = y
    translationMatrix.m32 = z

    val rotationMatrix = Matrix4f()
    rotationMatrix.identity()
    val cos = kotlin.math.cos(angle)
    val sin = kotlin.math.sin(angle)
    rotationMatrix.m00 = cos
    rotationMatrix.m01 = -sin
    rotationMatrix.m10 = sin
    rotationMatrix.m11 = cos

    val resultMatrix = Matrix4f()

    // Multiply the current matrix by the translation matrix
    resultMatrix.m00 =
        this.m00 * translationMatrix.m00 + this.m10 * translationMatrix.m01 + this.m20 * translationMatrix.m02 + this.m30 * translationMatrix.m03
    resultMatrix.m01 =
        this.m01 * translationMatrix.m00 + this.m11 * translationMatrix.m01 + this.m21 * translationMatrix.m02 + this.m31 * translationMatrix.m03
    resultMatrix.m02 =
        this.m02 * translationMatrix.m00 + this.m12 * translationMatrix.m01 + this.m22 * translationMatrix.m02 + this.m32 * translationMatrix.m03
    resultMatrix.m03 =
        this.m03 * translationMatrix.m00 + this.m13 * translationMatrix.m01 + this.m23 * translationMatrix.m02 + this.m33 * translationMatrix.m03

    resultMatrix.m10 =
        this.m00 * translationMatrix.m10 + this.m10 * translationMatrix.m11 + this.m20 * translationMatrix.m12 + this.m30 * translationMatrix.m13
    resultMatrix.m11 =
        this.m01 * translationMatrix.m10 + this.m11 * translationMatrix.m11 + this.m21 * translationMatrix.m12 + this.m31 * translationMatrix.m13
    resultMatrix.m12 =
        this.m02 * translationMatrix.m10 + this.m12 * translationMatrix.m11 + this.m22 * translationMatrix.m12 + this.m32 * translationMatrix.m13
    resultMatrix.m13 =
        this.m03 * translationMatrix.m10 + this.m13 * translationMatrix.m11 + this.m23 * translationMatrix.m12 + this.m33 * translationMatrix.m13

    resultMatrix.m20 =
        this.m00 * translationMatrix.m20 + this.m10 * translationMatrix.m21 + this.m20 * translationMatrix.m22 + this.m30 * translationMatrix.m23
    resultMatrix.m21 =
        this.m01 * translationMatrix.m20 + this.m11 * translationMatrix.m21 + this.m21 * translationMatrix.m22 + this.m31 * translationMatrix.m23
    resultMatrix.m22 =
        this.m02 * translationMatrix.m20 + this.m12 * translationMatrix.m21 + this.m22 * translationMatrix.m22 + this.m32 * translationMatrix.m23
    resultMatrix.m23 =
        this.m03 * translationMatrix.m20 + this.m13 * translationMatrix.m21 + this.m23 * translationMatrix.m22 + this.m33 * translationMatrix.m23

    resultMatrix.m30 =
        this.m00 * translationMatrix.m30 + this.m10 * translationMatrix.m31 + this.m20 * translationMatrix.m32 + this.m30 * translationMatrix.m33
    resultMatrix.m31 =
        this.m01 * translationMatrix.m30 + this.m11 * translationMatrix.m31 + this.m21 * translationMatrix.m32 + this.m31 * translationMatrix.m33
    resultMatrix.m32 =
        this.m02 * translationMatrix.m30 + this.m12 * translationMatrix.m31 + this.m22 * translationMatrix.m32 + this.m32 * translationMatrix.m33
    resultMatrix.m33 =
        this.m03 * translationMatrix.m30 + this.m13 * translationMatrix.m31 + this.m23 * translationMatrix.m32 + this.m33 * translationMatrix.m33

    // Assign the result matrix to the current matrix
    for (i in 0 until 16) {
        this.data[i] = resultMatrix.data[i]
    }
}