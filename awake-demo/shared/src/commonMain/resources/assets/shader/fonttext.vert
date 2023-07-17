// Input attributes
layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TexCoords;

// Uniforms
uniform mat4 u_ModelViewMatrix;
uniform mat4 u_ProjectionViewMatrix;

// Output variables
out vec3 v_Color;
out vec2 v_TexCoords;

void main() {
    // Apply transformation
    vec4 transformedPosition = u_ProjectionViewMatrix * u_ModelViewMatrix * vec4(a_Position, 0.0, 1.0);

    // Pass the color to the fragment shader
    v_Color = a_Color;

    // Pass the texture to the fragment shader
    v_TexCoords = a_TexCoords;

    // Set the final position for the vertex
    gl_Position = transformedPosition;
}