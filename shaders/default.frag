#version 330 core

out vec4 FragColor;   // Final fragment color output

in vec3 ourColor;     // Color from vertex shader
in vec2 TexCoord;     // Texture coordinates from vertex shader

uniform sampler2D ourTexture; // Texture uniform

void main()
{
    // Use the texture sampled color and combine it with the vertex color
    FragColor = texture(ourTexture, TexCoord);
}
