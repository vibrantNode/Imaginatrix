#version 330 core

layout (location = 0) in vec3 aPos;      // Vertex position
layout (location = 1) in vec3 aColor;    // Vertex color
layout (location = 2) in vec2 aTexCoord; // Vertex texture coordinate

out vec3 ourColor;    // Pass color to fragment shader
out vec2 TexCoord;    // Pass texture coordinates to fragment shader

// Uniforms for transformations
uniform mat4 model;       // Model transformation matrix
uniform mat4 view;        // View (camera) transformation matrix
uniform mat4 projection;  // Projection transformation matrix

void main()
{
    // Apply transformations: Model -> View -> Projection
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    // Pass other attributes to the fragment shader
    ourColor = aColor;
    TexCoord = aTexCoord;
}