package io.github.ronjunevaldoz.awake.core.utils

import io.github.ronjunevaldoz.awake.core.graphics.Disposable
import io.github.ronjunevaldoz.awake.core.graphics.image.Bitmap
import io.github.ronjunevaldoz.awake.core.rendering.Texture
import kotlinx.coroutines.runBlocking
import org.jetbrains.compose.resources.ExperimentalResourceApi
import org.jetbrains.compose.resources.resource

object TextureLoader {
    private val textures: MutableMap<String, Texture> = mutableMapOf()

    @OptIn(ExperimentalResourceApi::class)
    fun load(textureName: String, texturePath: String) {
        resource(texturePath).let {
            runBlocking {
                load(textureName, BitmapUtils.decode(it.readBytes()))
            }
        }
    }

    fun load(textureName: String, bitmap: Bitmap) {
        textures[textureName] = Texture.load(bitmap)
    }

    fun get(textureName: String): Int {
        return checkNotNull(textures[textureName]?.id) {
            "Texture name `$textureName` not found."
        }
    }

    fun remove(textureName: String) {
        if (textures.containsKey(textureName)) {
            textures.remove(textureName)
            textures[textureName]?.delete()
        }
    }

    fun disposeAllTextures() {
        for (texture in textures.values) {
            texture.delete()
        }
        textures.clear()
    }
}

/**
 * TODO move to AwakeCompose library
 */
object AssetUtils : Disposable {
    val texture = TextureLoader

    override fun dispose() {
        texture.disposeAllTextures()
    }
}