attribute vec4 a_Position;
attribute vec3 a_Color;
attribute vec2 a_TexCoords;
varying vec2 vTexCoords;
varying vec3 vColor;

void main() {
    gl_Position = a_Position;
    vTexCoords = a_TexCoords;
    vColor = a_Color;
}