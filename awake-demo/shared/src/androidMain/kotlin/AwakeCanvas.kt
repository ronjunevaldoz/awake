/*
 * Awake
 * Awake.awake-demo.shared.main
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
import androidx.compose.ui.Modifier
import androidx.compose.ui.viewinterop.AndroidView
import io.github.ronjunevaldoz.awake.core.graphics.Application
import io.github.ronjunevaldoz.awake.core.graphics.VulkanView
import io.github.ronjunevaldoz.awake.core.graphics.opengl.AndroidRenderer
import io.github.ronjunevaldoz.awake.core.graphics.opengl.OpenGLView

@Composable
actual fun AwakeCanvas(
    modifier: Modifier,
    renderer: Application,
    vulkan: Boolean
) {
    AndroidView(
        modifier = modifier,
        factory = { context ->
            if (vulkan) {
                VulkanView(context, renderer)
            } else {
                OpenGLView(context, AndroidRenderer(renderer))
            }
        }
    )
}