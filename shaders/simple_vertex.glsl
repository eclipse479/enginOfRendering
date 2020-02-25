#version 450
layout(location = 0) in vec3 local_position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture_coordinates;
layout(location = 3) in vec4 tangent;

out vec2 final_texture_coodinates;					//FOR TEXTURE
out vec4 vPosition;									//FOR LIGHTING
out vec3 vNormal; 									//FOR LIGHTING
out vec3 vTangent;
out vec3 vBiTangent;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;
uniform mat3 normalMatrix; 							//FOR LIGHTING

void main()
{
	final_texture_coodinates = texture_coordinates; //	FOR TEXTURE
	vPosition = model_matrix * vec4(local_position,1);
    vNormal = normalMatrix * normal.xyz; 			// FOR LIGHTING
vTangent = normalMatrix * tangent.xyz;
vBiTangent = cross(vNormal, vTangent) * tangent.w;
    gl_Position = (projection_view_matrix * model_matrix) * vec4(local_position, 1);
}