#version 450

uniform vec4 color = vec4(1,1,1,1);



out vec4 final_color;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	float ambientStrength = 0.5f;
	vec3 ambient = ambientStrength * lightColor * objectColor;
 
   final_color =vec4(ambient,1.0f);
}