/*
 * Awake
 * Awake.awake-demo.shared.iosMain
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



import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.interop.UIKitView
import io.github.ronjunevaldoz.awake.core.graphics.Application
import io.github.ronjunevaldoz.awake.core.graphics.opengl.GameView
import platform.UIKit.UIScreen

@Composable
actual fun AwakeCanvas(
    modifier: Modifier,
    renderer: Application,
    vulkan: Boolean
) {
    val gameView = remember {
        { GameView(UIScreen.mainScreen.bounds, renderer) }
    }
    UIKitView(
        factory = gameView,
        modifier = modifier,
//        onResize = { uiView, frame ->
//            val width = CGRectGetWidth(frame)
//            val height = CGRectGetHeight(frame)
//            renderer.resize(0,0, width.toInt(), height.toInt())
//            uiView.setFrame(frame)
//        },
        onRelease = { uiView ->
            uiView.renderer.dispose()
        },
        interactive = false
    )
}