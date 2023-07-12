#if defined(GL_ES)
precision mediump float;
#else
#endif

// Input variables
in vec3 v_Color;
//in vec2 v_TexCoords;

// Uniforms
//uniform sampler2D u_Texture;

// Output
layout (location = 0) out vec4 fragColor;

void main() {
    // Sample the texture using the provided texture coordinates
    //    vec4 texColor = texture(u_Texture, v_TexCoords);

    // Multiply the color with the texture color
    vec4 finalColor =  vec4(v_Color, 1.0);
    // Output the interpolated color
    fragColor = finalColor;
}