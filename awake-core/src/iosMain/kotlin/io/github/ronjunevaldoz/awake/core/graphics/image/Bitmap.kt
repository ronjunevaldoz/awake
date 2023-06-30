package io.github.ronjunevaldoz.awake.core.graphics.image

import kotlinx.cinterop.allocArrayOf
import kotlinx.cinterop.get
import kotlinx.cinterop.memScoped
import platform.CoreFoundation.CFDataGetBytePtr
import platform.CoreFoundation.CFRelease
import platform.CoreGraphics.CGDataProviderCopyData
import platform.CoreGraphics.CGImageGetDataProvider
import platform.CoreGraphics.CGImageGetHeight
import platform.CoreGraphics.CGImageGetWidth
import platform.Foundation.NSData
import platform.Foundation.create
import platform.UIKit.UIImage

class AppleBitmap(
    override val width: Int,
    override val height: Int,
    override val channel: Int,
    override val pixels: IntArray
) : Bitmap

actual fun createBitmap(bytes: ByteArray): Bitmap {
    val nsData = memScoped {
        NSData.create(bytes = allocArrayOf(bytes), length = bytes.size.toULong())
    }
    val image = UIImage.imageWithData(nsData) ?: throw Exception("Invalid bitmap data")
    val width = CGImageGetWidth(image.CGImage).toInt()
    val height = CGImageGetHeight(image.CGImage).toInt()
    val pixelData = CGDataProviderCopyData(CGImageGetDataProvider(image.CGImage))
    val data = CFDataGetBytePtr(pixelData)!!

    val pixelArray = IntArray(width * height)
    for (y in 0 until height) {
        val flippedY = height - y - 1 // Flip the y-coordinate

        for (x in 0 until width) {

            val pixelInfo: Int = (width * flippedY + x) * 4 // The image is in PNG format
            val red = data[pixelInfo].toInt()         // If you need this info, enable it
            val green = data[pixelInfo + 1].toInt()   // If you need this info, enable it
            val blue = data[pixelInfo + 2].toInt()    // If you need this info, enable it
            val alpha = data[pixelInfo + 3].toInt()   // I need only this info for my maze game

            // Convert RGBA to ARGB format
            val argbPixel = (alpha shl 24) or (red shl 16) or (green shl 8) or blue

            // Store the pixel in the pixel array
            pixelArray[y * width + x] = argbPixel
        }
    }

    CFRelease(pixelData)
    return AppleBitmap(
        width = width,
        height = height,
        channel = 4,
        pixels = pixelArray
    )
}