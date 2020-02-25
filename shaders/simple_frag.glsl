#version 450 // Frag Shader

uniform sampler2D diffuse_texture;
uniform vec3 lightDirection;
uniform float time;

in vec2 final_texture_coodinates;
in vec3 vNormal;

out vec4 final_color;

void main()
{
    final_color = texture(diffuse_texture, final_texture_coodinates);
	//final_color = vec4(final_texture_coordinates, 0.0, 1.0);
}