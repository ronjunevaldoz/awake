package io.github.ronjunevaldoz.awake.core.graphics

import org.lwjgl.stb.STBImage.stbi_image_free
import org.lwjgl.stb.STBImage.stbi_load_from_memory
import org.lwjgl.stb.STBImage.stbi_set_flip_vertically_on_load
import org.lwjgl.system.MemoryStack.stackPush
import java.io.ByteArrayInputStream
import java.nio.ByteBuffer
import java.nio.ByteOrder
import javax.imageio.ImageIO

actual fun createBitmap(bytes: ByteArray): Bitmap {
    return decodeBitmap(bytes)
}

fun decodeBitmap(bytes: ByteArray): Bitmap {
    val bufferedImage = ImageIO.read(ByteArrayInputStream(bytes))
    val width = bufferedImage.width
    val height = bufferedImage.height
    val channel = bufferedImage.colorModel.numComponents
    val flipY = true
    val pixels = IntArray(width * height)
    for (y in 0 until height) {
        for (x in 0 until width) {
            val flippedY = if (flipY) height - 1 - y else y
            val color = bufferedImage.getRGB(x, flippedY)
            pixels[y * width + x] = color
        }
    }

    return DefaultBitmap(width, height, channel, pixels)
    // Create a ByteBuffer from the byte array
    val buffer = ByteBuffer.allocateDirect(bytes.size).apply {
        order(ByteOrder.nativeOrder())
        put(bytes)
        position(0)
    }

    return stackPush().use { stack ->
        // Load image file
        val widthBuffer = stack.mallocInt(1)
        val heightBuffer = stack.mallocInt(1)
        val channelBuffer = stack.mallocInt(1)

        stbi_set_flip_vertically_on_load(true) // Adjust this based on your image's orientation

        // Load the image using stb_image
        val byteBuffer = stbi_load_from_memory(buffer, widthBuffer, heightBuffer, channelBuffer, 4)
            ?: throw Exception("Invalid bitmap parameters")

        // Retrieve image properties
        val width = widthBuffer.get(0)
        val height = heightBuffer.get(0)
        val channel = channelBuffer.get(0)

        val pixels = IntArray(width * height)
        // Copy the pixel data to the IntArray
        for (i in 0 until width * height) {
            val offset = i * 4
            val r = byteBuffer[offset].toInt() and 0xFF
            val g = byteBuffer[offset + 1].toInt() and 0xFF
            val b = byteBuffer[offset + 2].toInt() and 0xFF
            val a = byteBuffer[offset + 3].toInt() and 0xFF
            pixels[i] = (a shl 24) or (r shl 16) or (g shl 8) or b
        }

        // free image buffer
        stbi_image_free(byteBuffer)
        DefaultBitmap(width, height, channel, pixels)
    }
}