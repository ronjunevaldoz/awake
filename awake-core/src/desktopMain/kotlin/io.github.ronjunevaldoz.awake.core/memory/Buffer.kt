package io.github.ronjunevaldoz.awake.core.memory

import java.nio.Buffer
import java.nio.ByteBuffer
import java.nio.ByteOrder

class ByteBuffer(size: Int) : ByteBuf {
    private val buffer = ByteBuffer.allocateDirect(size).order(ByteOrder.nativeOrder())

    constructor(data: ByteArray) : this(data.size) {
        buffer.put(data)
        buffer.position(0)
    }

    constructor(data: Array<Byte>) : this(data.size) {
        buffer.put(data.toByteArray())
        buffer.position(0)
    }

    override fun get(index: Int): Byte {
        return buffer.get(index)
    }

    override fun set(index: Int, value: Byte) {
        buffer.put(index, value)
    }

    @Suppress("UNCHECKED_CAST")
    override fun <B : Buffer> get(): B = buffer as B
}

class ShortBuffer(size: Int) : ShortBuf {
    private val buffer = ByteBuffer
        .allocateDirect(size * Short.SIZE_BYTES)
        .order(ByteOrder.nativeOrder())
        .asShortBuffer()

    constructor(data: ShortArray) : this(data.size) {
        buffer.put(data)
        buffer.position(0)
    }

    constructor(data: Array<Short>) : this(data.size) {
        buffer.put(data.toShortArray())
        buffer.position(0)
    }

    override fun get(index: Int): Short {
        return buffer.get(index)
    }

    override fun set(index: Int, value: Short) {
        buffer.put(index, value)
    }
    @Suppress("UNCHECKED_CAST")
    override fun <B : Buffer> get(): B = buffer as B
}

class IntBuffer(size: Int) : IntBuf {
    private val buffer = ByteBuffer
        .allocateDirect(size * Int.SIZE_BYTES)
        .order(ByteOrder.nativeOrder())
        .asIntBuffer()

    constructor(data: IntArray) : this(data.size) {
        buffer.put(data)
        buffer.position(0)
    }

    constructor(data: Array<Int>) : this(data.size) {
        buffer.put(data.toIntArray())
        buffer.position(0)
    }

    override fun get(index: Int): Int {
        return buffer.get(index)
    }

    override fun set(index: Int, value: Int) {
        buffer.put(index, value)
    }

    @Suppress("UNCHECKED_CAST")
    override fun <B : Buffer> get(): B = buffer as B
}

class FloatBuffer(size: Int) : FloatBuf {
    private val buffer = ByteBuffer
        .allocateDirect(size * Float.SIZE_BYTES)
        .order(ByteOrder.nativeOrder())
        .asFloatBuffer()

    constructor(data: FloatArray) : this(data.size) {
        buffer.put(data)
        buffer.position(0)
    }

    constructor(data: Array<Float>) : this(data.size) {
        buffer.put(data.toFloatArray())
        buffer.position(0)
    }

    override fun get(index: Int): Float {
        return buffer.get(index)
    }

    override fun set(index: Int, value: Float) {
        buffer.put(index, value)
    }

    override fun put(data: FloatArray) {
        buffer.put(data)
        buffer.position(0)
    }

    @Suppress("UNCHECKED_CAST")
    override fun <B : Buffer> get(): B = buffer as B
}

actual interface Buffer {
    fun <B : Buffer> get() : B
}

actual fun createByteBuffer(data: ByteArray): ByteBuf {
    return ByteBuffer(data)
}

actual fun createShortBuffer(data: ShortArray): ShortBuf {
    return ShortBuffer(data)
}

actual fun createIntBuffer(data: IntArray): IntBuf {
    return IntBuffer(data)
}

actual fun createFloatBuffer(data: FloatArray): FloatBuf {
    return FloatBuffer(data)
}