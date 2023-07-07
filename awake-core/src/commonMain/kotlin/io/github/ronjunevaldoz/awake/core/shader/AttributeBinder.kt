package io.github.ronjunevaldoz.awake.core.shader

import io.github.ronjunevaldoz.awake.core.AwakeContext

class AttributeBinder(private val programId: Int) {
    private val attributes: MutableMap<String, Int> = mutableMapOf()
    var nextAvailableLocation: Int = 0
    fun put(key: String, location: Int) {
        if (location != nextAvailableLocation) {
            throw IllegalArgumentException("Attribute location $location for `$key` is not incremental. Expected value `${nextAvailableLocation}`")
        }
        attributes[key] = location
        AwakeContext.gl.bindAttribLocation(programId, location, key)
        nextAvailableLocation++
    }

    fun get(key: String): Int {
        return attributes[key]
            ?: throw IllegalArgumentException(
                "Attribute location not found: `$key`"
            )
    }
}