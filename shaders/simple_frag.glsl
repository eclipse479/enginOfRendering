#version 450 // Frag Shader

uniform sampler2D diffuse_texture;
uniform vec3 lightDirection;
uniform vec3 ambientLight;
uniform vec3 diffuseLight;
uniform vec3 specularLight;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float specularPower;
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
	vec3 ambient = ambientLight * Ka;
	vec3 diffuse = (diffuseLight * Kd * lambertTerm);
	final_color = vec4(ambient + diffuse, 1.0);
}