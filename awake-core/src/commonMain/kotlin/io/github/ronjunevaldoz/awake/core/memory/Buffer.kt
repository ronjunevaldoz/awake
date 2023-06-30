package io.github.ronjunevaldoz.awake.core.memory

expect interface Buffer

interface ByteBuf : Buffer {
    operator fun get(index: Int): Byte
    operator fun set(index: Int, value: Byte)
}
interface ShortBuf : Buffer {
    operator fun get(index: Int): Short
    operator fun set(index: Int, value: Short)
}
interface IntBuf : Buffer {
    operator fun get(index: Int): Int
    operator fun set(index: Int, value: Int)
}
interface FloatBuf : Buffer {
    operator fun get(index: Int): Float
    operator fun set(index: Int, value: Float)
    fun put(data: FloatArray)
}

expect fun createByteBuffer(data: ByteArray) : ByteBuf
expect fun createShortBuffer(data: ShortArray) : ShortBuf
expect fun createIntBuffer(data: IntArray) : IntBuf
expect fun createFloatBuffer(data: FloatArray) : FloatBuf