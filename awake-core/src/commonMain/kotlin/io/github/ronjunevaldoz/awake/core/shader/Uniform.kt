package io.github.ronjunevaldoz.awake.core.shader

import kotlin.properties.ReadOnlyProperty
import kotlin.reflect.KProperty

/**
 * @param name Uniform variable name otherwise use property name
 */
class Uniform(private val name: String = "", private val prefix: String = "u_") :
    ReadOnlyProperty<Shader, Int> {
    override fun getValue(thisRef: Shader, property: KProperty<*>): Int {
        val variableName = name.ifEmpty { property.name }
        val finalName =
            if (variableName.startsWith(prefix)) variableName else "$prefix$variableName"
        return thisRef.getUniformLocation(finalName)
    }
}