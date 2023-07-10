package io.github.ronjunevaldoz.awake.core.application


interface GameLoop {
    fun initTime()
    fun startLoop(onUpdate: (deltaTime: Double) -> Unit)
}