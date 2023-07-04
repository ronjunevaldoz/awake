#version 150 core

in vec2 vTexCoords;
in vec3 vColor;
uniform sampler2D textureSampler;

out vec4 fragColor;

void main() {
    fragColor = texture(textureSampler, vTexCoords) * vec4(vColor, 1.0);
}