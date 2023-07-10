package io.github.ronjunevaldoz.awake.core

import io.github.aakira.napier.DebugAntilog
import io.github.aakira.napier.Napier
import io.github.ronjunevaldoz.awake.core.graphics.Config
import io.github.ronjunevaldoz.awake.core.graphics.opengl.Agl
import io.github.ronjunevaldoz.awake.core.graphics.opengl.AglDebuggable
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGL
import kotlin.native.concurrent.ThreadLocal

interface Context {
    val config: Config
    val gl: OpenGL
}

class AwakeContext(override val gl: OpenGL, override val config: Config) : Context {
    @ThreadLocal
    companion object {
        private var instance: Context? = null
        val gl: OpenGL
            get() = checkNotNull(instance?.gl) { "Awake Context not yet created!" }
        val config: Config
            get() = checkNotNull(instance?.config) { "Awake Context not yet created!" }

        fun init(debug: Boolean = false, config: Config.() -> Unit = {}): Context {
            Napier.base(DebugAntilog())
            Napier.i("Awake Context initiated")
            if (instance == null) {
                val gl = if (debug) Agl else AglDebuggable
                instance = AwakeContext(
                    gl = gl,
                    config = Config(
                        debug = debug
                    ).apply(config)
                )
            }
            return instance as Context
        }
    }
}