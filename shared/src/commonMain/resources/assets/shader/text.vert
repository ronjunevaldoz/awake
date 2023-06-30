#version 150 core

in vec4 a_Position;
in vec3 a_Color;
in vec2 a_TexCoords;
out vec2 vTexCoords;
out vec3 vColor;

void main() {
    gl_Position = a_Position;
    vTexCoords = a_TexCoords;
    vColor = a_Color;
}