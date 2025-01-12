#version 330 core
layout (location = 0) in vec3 aPos;      // Vertex position
layout (location = 1) in vec3 aColor;    // Vertex color
layout (location = 2) in vec2 aTexCoord; // Vertex texture coordinate

out vec3 ourColor;    // Pass color to fragment shader
out vec2 TexCoord;    // Pass texture coordinates to fragment shader

uniform mat4 view;    // View transformation matrix
uniform mat4 projection; // Projection transformation matrix

void main()
{
    // Apply transformations to the vertex position
    gl_Position = projection * view * vec4(aPos, 1.0);
    ourColor = aColor;            // Pass color data
    TexCoord = aTexCoord;         // Pass texture coordinates
}