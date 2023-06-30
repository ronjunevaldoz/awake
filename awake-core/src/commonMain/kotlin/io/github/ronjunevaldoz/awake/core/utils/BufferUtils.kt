package io.github.ronjunevaldoz.awake.core.utils

import io.github.ronjunevaldoz.awake.core.memory.ByteBuf
import io.github.ronjunevaldoz.awake.core.memory.FloatBuf
import io.github.ronjunevaldoz.awake.core.memory.IntBuf
import io.github.ronjunevaldoz.awake.core.memory.ShortBuf
import io.github.ronjunevaldoz.awake.core.memory.createByteBuffer
import io.github.ronjunevaldoz.awake.core.memory.createFloatBuffer
import io.github.ronjunevaldoz.awake.core.memory.createIntBuffer
import io.github.ronjunevaldoz.awake.core.memory.createShortBuffer

object BufferUtils {
    fun byteBuffer(size: Int) : ByteBuf = createByteBuffer(ByteArray(size))
    fun shortBuffer(size: Int) : ShortBuf = createShortBuffer(ShortArray(size))
    fun intBuffer(size: Int) : IntBuf = createIntBuffer(IntArray(size))
    fun floatBuffer(size: Int) : FloatBuf = createFloatBuffer(FloatArray(size))
    fun byteBuffer(data: ByteArray) : ByteBuf = createByteBuffer(data)
    fun shortBuffer(data: ShortArray) : ShortBuf = createShortBuffer(data)
    fun intBuffer(data: IntArray): IntBuf = createIntBuffer(data)
    fun floatBuffer(data: FloatArray) : FloatBuf = createFloatBuffer(data)
}