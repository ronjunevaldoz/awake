package io.github.ronjunevaldoz.awake.core.graphics

import org.lwjgl.stb.STBImage
import java.nio.ByteBuffer
import java.nio.ByteOrder


class DesktopBitmap(
    override val width: Int,
    override val height: Int,
    override val channel: Int,
    override val pixels: IntArray
) : Bitmap

actual fun createBitmap(bytes: ByteArray): Bitmap {
    return decodeBitmap(bytes)
}

typealias LwjglBufferUtils = org.lwjgl.BufferUtils

fun decodeBitmap(bytes: ByteArray): Bitmap {
    // Create a ByteBuffer from the byte array
    val buffer = ByteBuffer.allocateDirect(bytes.size).apply {
        order(ByteOrder.nativeOrder())
        put(bytes)
        position(0)
    }

    STBImage.stbi_set_flip_vertically_on_load(true) // Adjust this based on your image's orientation
    // Create buffers for image properties
    val widthBuffer = LwjglBufferUtils.createIntBuffer(1)
    val heightBuffer = LwjglBufferUtils.createIntBuffer(1)
    val channelBuffer = LwjglBufferUtils.createIntBuffer(1)
    // Load the image using stb_image
    val components =
        STBImage.stbi_load_from_memory(buffer, widthBuffer, heightBuffer, channelBuffer, 4)
            ?: throw Exception("Invalid bitmap parameters")

    // Retrieve image properties
    val width = widthBuffer.get(0)
    val height = heightBuffer.get(0)
    val channel = channelBuffer.get(0)

    // Allocate memory for pixel data conversion
    val pixelBuffer = LwjglBufferUtils.createIntBuffer(width * height)

    // Copy the pixel data to the IntArray
    for (i in 0 until width * height) {
        val offset = i * 4
        val r = components[offset].toInt() and 0xFF
        val g = components[offset + 1].toInt() and 0xFF
        val b = components[offset + 2].toInt() and 0xFF
        val a = components[offset + 3].toInt() and 0xFF
        pixelBuffer.put(i, (a shl 24) or (r shl 16) or (g shl 8) or b)
    }

    // Free the image data
    STBImage.stbi_image_free(components)

    // Convert the pixel data to an IntArray
    val pixels = IntArray(width * height)
    pixelBuffer.get(pixels)
    return DesktopBitmap(width, height, channel, pixels)
}