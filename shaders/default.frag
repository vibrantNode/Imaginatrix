#version 330 core

in vec3 fragPos; // Input from vertex shader
out vec4 FragColor;

void main()
{
    // Create a dynamic red color effect based on the position of the fragment in space
    float red = (fragPos.x + 1.0) * 0.5;   // Normalize x to be between 0 and 1
    
    // Set the color to different shades of red
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);  // Red with no green or blue
}
