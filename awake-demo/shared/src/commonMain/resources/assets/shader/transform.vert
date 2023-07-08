#version 300 es

// Input attributes
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

// Uniforms
uniform mat4 u_TransformMatrix;

// Output variables
out vec4 v_Color;

void main() {
    // Apply transformation
    vec4 transformedPosition = u_TransformMatrix * vec4(a_Position, 1.0);

    // Pass the color to the fragment shader
    v_Color = a_Color;

    // Set the final position for the vertex
    gl_Position = transformedPosition;
}