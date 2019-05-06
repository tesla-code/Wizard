#version 330 core

in vec3 ourColor;
out vec4 fs_color;

void main()
{
    fs_color = vec4(ourColor, 1.0);

} 