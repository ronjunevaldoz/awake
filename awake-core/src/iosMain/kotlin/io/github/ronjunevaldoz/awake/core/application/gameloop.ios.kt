package io.github.ronjunevaldoz.awake.core.application

@ThreadLocal
object IOSGameLoop : GameLoop {
    override fun startLoop(onUpdate: (deltaTime: Double) -> Unit) {
    }
}