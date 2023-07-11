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
    private val define: String = "",
) : DefaultShader() {

    private val shaderDir = "assets/shader"

    var transformMatrix by uniform
    var modelViewMatrix by uniform
    var projectionViewMatrix by uniform

    @OptIn(ExperimentalResourceApi::class)
    override fun getVertexSource(): String {
        val vertString = resource("$shaderDir/$vertFile").let {
            runBlocking { it.readBytes().decodeToString() }
        }
        return define + vertString
    }

    @OptIn(ExperimentalResourceApi::class)
    override fun getFragmentSource(): String {
        val fragString = resource("$shaderDir/$fragFile").let {
            runBlocking { it.readBytes().decodeToString() }
        }
        return define + fragString
    }
}