package io.github.ronjunevaldoz.awake.core.shader

import io.github.ronjunevaldoz.awake.core.AwakeContext

class AttributeBinderImpl(private val programId: Int) : AttributeBinder {
    private val attributes: MutableMap<String, Int> = mutableMapOf()
    private var nextAvailableLocation: Int = 0
    override fun bind(name: String, location: Int) {
        if (location != nextAvailableLocation) {
            throw IllegalArgumentException("Attribute location $location for `$name` is not incremental. Expected value `${nextAvailableLocation}`")
        }
        attributes[name] = location
        AwakeContext.gl.bindAttribLocation(programId, location, name)
        nextAvailableLocation++
    }

    override fun getLocation(name: String): Int {
        return attributes[name]
            ?: throw IllegalArgumentException(
                "Attribute location not found: `$name`"
            )
    }
}