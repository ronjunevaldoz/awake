precision mediump float;
varying vec2 vTexCoords;
varying vec3 vColor;
uniform sampler2D texture;

void main() {
    gl_FragColor = texture2D(texture, vTexCoords) * vec4(vColor, 1.0);
}