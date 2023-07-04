#version 150 core

in vec3 a_Position;
in vec4 a_Color;

out vec4 v_Color;

void main() {
    gl_Position = vec4(a_Position, 1.0);
    v_Color = a_Color;
}