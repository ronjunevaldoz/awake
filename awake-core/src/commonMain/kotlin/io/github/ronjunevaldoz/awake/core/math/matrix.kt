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