#version 450 // Frag Shader

uniform sampler2D diffuse_texture;
uniform vec3 lightDirection;

//in vec2 final_texture_coodinates;
in vec3 vNormal;

out vec4 final_color;

void main()
{
	//make sure normal and light direction is normalised
	vec3 N = normalize(vNormal);
	vec3 L = normalize(lightDirection);
	
	float lambertTerm = max(0,min(1,dot(N,-L)));
    //final_color = texture(diffuse_texture, final_texture_coodinates); //	FOR TEXTURE
	final_color = vec4(lambertTerm,lambertTerm,lambertTerm, 1.0);
}