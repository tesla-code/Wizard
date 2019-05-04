#version 330 core

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;

out vec4 fs_color;

uniform sampler2D textureGround;

void main()
{
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	fs_color = texture( textureGround, vs_texcoord);

} 