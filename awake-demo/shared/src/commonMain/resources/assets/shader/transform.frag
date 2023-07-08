#version 300 es

precision mediump float;

// Input variables
in vec4 v_Color;

// Output
layout (location = 0) out vec4 fragColor;

void main() {
    // Output the interpolated color
    fragColor = v_Color;
}