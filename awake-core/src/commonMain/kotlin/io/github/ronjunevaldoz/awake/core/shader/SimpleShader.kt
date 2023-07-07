package io.github.ronjunevaldoz.awake.core.shader

import kotlinx.coroutines.runBlocking
import org.jetbrains.compose.resources.ExperimentalResourceApi
import org.jetbrains.compose.resources.resource

/**
 * TODO move to separate library AwakeCompose
 */
class SimpleShader(
    private val vertFile: String,
    private val fragFile: String,
) : DefaultShader() {

    private val shaderDir = "assets/shader"

    @OptIn(ExperimentalResourceApi::class)
    override fun getVertexSource(): String {
        val vertString = resource("$shaderDir/$vertFile").let {
            runBlocking { it.readBytes().decodeToString() }
        }
        return vertString
    }

    @OptIn(ExperimentalResourceApi::class)
    override fun getFragmentSource(): String {
        val fragString = resource("$shaderDir/$fragFile").let {
            runBlocking { it.readBytes().decodeToString() }
        }
        return fragString
    }
}