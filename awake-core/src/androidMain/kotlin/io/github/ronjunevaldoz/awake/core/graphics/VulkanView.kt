/*
 * Awake
 * Awake.awake-core.main
 *
 * Copyright (c) ronjunevaldoz 2023.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package io.github.ronjunevaldoz.awake.core.graphics

import android.content.Context
import android.view.SurfaceHolder
import android.view.SurfaceView
import io.github.ronjunevaldoz.awake.core.application.AndroidGameLoop
import io.github.ronjunevaldoz.awake.core.utils.Frame


class VulkanView(
    context: Context,
    private val application: Application
) : SurfaceView(context), SurfaceHolder.Callback2 {

    init {
        holder.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        Frame.width = width
        Frame.height = height
        application.create(holder.surface)
        AndroidGameLoop.startLoop { deltaTime ->
            application.update(deltaTime.toFloat())
        }
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        application.resize(0, 0, width, height)
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        application.dispose()
    }

    override fun surfaceRedrawNeeded(holder: SurfaceHolder) {
        //        TODO("Not yet implemented")
    }
}