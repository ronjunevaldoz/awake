package io.github.ronjunevaldoz.awake.core.shader

import io.github.ronjunevaldoz.awake.core.math.Matrix4f
import io.github.ronjunevaldoz.awake.core.math.Vec3f
import io.github.ronjunevaldoz.awake.core.math.Vec4f
import kotlin.properties.ReadWriteProperty
import kotlin.reflect.KProperty

/**
 * @param name Uniform variable name otherwise use property name
 */

class Uniform(
    private val name: String = "",
    private val prefix: String = "u_"
) : ReadWriteProperty<DefaultShader, Any> {
    override fun getValue(thisRef: DefaultShader, property: KProperty<*>): Any {
        val variableName = name.ifEmpty { property.name }
        val key = if (variableName.startsWith(prefix)) variableName else property.buildKey(prefix)
        return thisRef.uBinder.getLocation(key)
    }

    override fun setValue(thisRef: DefaultShader, property: KProperty<*>, value: Any) {
        val variableName = name.ifEmpty { property.name }
        val key = if (variableName.startsWith(prefix)) variableName else property.buildKey(prefix)
        val location = thisRef.uBinder.getLocation(key)
        require(location > -1) { "Unable to set value to uniform `$key`, invalid location $location" }
        when (value) {
            is Int -> thisRef.uBinder.set(location, value)
            is Float -> thisRef.uBinder.set(location, value)
            is Vec3f -> thisRef.uBinder.set(location, value)
            is Vec4f -> thisRef.uBinder.set(location, value)
            is Matrix4f -> thisRef.uBinder.set(location, value)
            else -> throw Exception("Uniform value not yet supported ${value::class.simpleName} ")
        }
    }
}