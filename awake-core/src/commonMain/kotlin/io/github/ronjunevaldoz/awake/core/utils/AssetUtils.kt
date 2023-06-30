package io.github.ronjunevaldoz.awake.core.utils

import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.graphics.image.Bitmap
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Constants
import io.github.ronjunevaldoz.awake.core.memory.IntBuf
import kotlinx.coroutines.runBlocking
import org.jetbrains.compose.resources.ExperimentalResourceApi
import org.jetbrains.compose.resources.resource

/**
 * TODO move to AwakeCompose library
 */
object AssetUtils : Disposable {
    private val textures: MutableMap<String, IntBuf> = mutableMapOf()

    @OptIn(ExperimentalResourceApi::class)
    fun loadTexture(textureName: String, texturePath: String) {
        resource(texturePath).let {
            runBlocking {
                loadTextureBitmap(textureName, BitmapUtils.decode(it.readBytes()))
            }
        }
    }

    fun loadTextureBitmap(textureName: String, bitmap: Bitmap) {
        val tbo = BufferUtils.intBuffer(1)
        textures[textureName] = tbo
        gl.genTextures(1, tbo)
        gl.bindTexture(Constants.GL_TEXTURE_2D, tbo[0])
        gl.texParameteri(
            Constants.GL_TEXTURE_2D,
            Constants.GL_TEXTURE_WRAP_S,
            Constants.GL_REPEAT
        )
        gl.texParameteri(
            Constants.GL_TEXTURE_2D,
            Constants.GL_TEXTURE_WRAP_T,
            Constants.GL_REPEAT
        )
        gl.texParameteri(
            Constants.GL_TEXTURE_2D,
            Constants.GL_TEXTURE_MAG_FILTER,
            Constants.GL_LINEAR
        )
        gl.texParameteri(
            Constants.GL_TEXTURE_2D,
            Constants.GL_TEXTURE_MIN_FILTER,
            Constants.GL_LINEAR
        )
        gl.texImage2D(Constants.GL_TEXTURE_2D, 0, bitmap, 0)
        gl.bindTexture(Constants.GL_TEXTURE_2D, 0)
    }

    fun getTexture(textureName: String): Int {
        return checkNotNull(textures[textureName]?.get(0)) {
            "Texture name `$textureName` not found."
        }
    }

    fun removeTexture(textureName: String) {
        val textureId = textures.remove(textureName)
        if (textureId != null) {
            gl.deleteTextures(1, textureId)
        }
    }

    private fun disposeAllTextures() {
        for (textureId in textures.values) {
            gl.deleteTextures(1, textureId)
        }
        textures.clear()
    }

    override fun dispose() {
        disposeAllTextures()
    }
}