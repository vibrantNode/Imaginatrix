#version 330 core

layout (location = 0) in vec3 aPos; // Vertex position
out vec3 fragPos; // Output position to pass to the fragment shader

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); // Transform vertex position
    fragPos = aPos; // Pass position to the fragment shader
}