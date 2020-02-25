#version 450
layout(location = 0) in vec3 local_position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture_coordinates;


//out vec2 final_texture_coodinates;
out vec4 vPosition;
out vec3 vNormal;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;
uniform mat3 normalMatrix;

void main()
{
	//vPosition = model_matrix * local_position;
    vNormal = normalMatrix * normal.xyz;
    //final_texture_coodinates = texture_coordinates;
    gl_Position = (projection_view_matrix * model_matrix) * vec4(local_position, 1);
}