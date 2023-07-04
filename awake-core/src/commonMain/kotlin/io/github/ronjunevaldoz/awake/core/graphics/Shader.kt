package io.github.ronjunevaldoz.awake.core.graphics

import io.github.ronjunevaldoz.awake.core.AwakeContext.Companion.gl
import io.github.ronjunevaldoz.awake.core.graphics.opengl.tryCreateShader
import io.github.ronjunevaldoz.awake.core.utils.AwakeLogger
import kotlinx.coroutines.runBlocking
import org.jetbrains.compose.resources.ExperimentalResourceApi
import org.jetbrains.compose.resources.resource
import kotlin.properties.ReadWriteProperty
import kotlin.reflect.KProperty

interface Shader {
    val program: Int
    fun compile()
    fun use()
    fun delete()
}

fun Shader.use(shader: Shader.() -> Unit) {
    when {
        program > 0 -> {
            use()
            shader()
        }

        else -> AwakeLogger.warn("Invalid shader program id: $program")
    }
}

abstract class BaseShader : Shader {
    override var program = -1
    abstract fun getVertexSource(): String
    abstract fun getFragmentSource(): String
    override fun compile() {
        val (vertString, fragString) = getShaderSources()
        program = gl.tryCreateShader(
            vertex = vertString,
            fragment = fragString
        )
    }

    override fun use() {
        gl.useProgram(program)
    }

    override fun delete() {
        gl.deleteProgram(program)
    }

    private fun getShaderSources(): Pair<String, String> = with(this) {
        val vertString = getVertexSource()
        val fragString = getFragmentSource()
        return Pair(vertString, fragString)
    }
}

class AttributeBinder(val programId: Int) {
    val attributes: MutableMap<String, Int> = mutableMapOf()
    var nextAvailableLocation: Int = 0

}

abstract class DefaultShader : BaseShader() {

    protected val attributeBinder: AttributeBinder by lazy { AttributeBinder(program) }

    override fun compile() {
        super.compile()
        bindAttributes()
    }

    abstract fun bindAttributes()
    protected fun attribute(prefix: String = "a_"): ReadWriteProperty<Any?, Int> =
        object : ReadWriteProperty<Any?, Int> {
            override fun getValue(thisRef: Any?, property: KProperty<*>): Int {
                return attributeBinder.attributes[property.buildKey(prefix)]
                    ?: throw IllegalArgumentException(
                        "Attribute not found: ${
                            property.buildKey(
                                prefix
                            )
                        }"
                    )
            }

            override fun setValue(thisRef: Any?, property: KProperty<*>, value: Int) {
                val key = property.buildKey(prefix)
                if (value != attributeBinder.nextAvailableLocation) {
                    throw IllegalArgumentException("Attribute location $value for `$key` is not incremental. Expected value `${attributeBinder.nextAvailableLocation}`")
                }
                attributeBinder.attributes[key] = value
                gl.bindAttribLocation(attributeBinder.programId, value, key)
                attributeBinder.nextAvailableLocation++
            }

            private fun KProperty<*>.buildKey(prefix: String): String {
                return prefix + name.replaceFirstChar { if (it.isLowerCase()) it.titlecase() else it.toString() }
            }
        }
}

/**
 * TODO move to separate library AwakeCompose
 */
class SimpleShader(
    private val vertFile: String,
    private val fragFile: String,
): DefaultShader() {

    private val shaderDir = "assets/shader"
    var position by attribute()
    var color by attribute()
    var texCoords by attribute()
    override fun bindAttributes() {
        position = 0
        color = 1
        texCoords = 2
    }

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