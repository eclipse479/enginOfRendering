#version 450 // Frag Shader

uniform sampler2D diffuse_texture; 		//FOR TEXTURE
uniform vec3 lightDirection; 			// FOR LIGHTING
uniform vec3 ambientLight; 				// FOR LIGHTING
uniform vec3 diffuseLight; 				// FOR LIGHTING
uniform vec3 specularLight; 			// FOR LIGHTING

uniform vec3 Ka; 						// FOR LIGHTING
uniform vec3 Kd; 						// FOR LIGHTING
uniform vec3 Ks; 						// FOR LIGHTING
uniform float specularPower = 10; 		// FOR LIGHTING

uniform vec3 cameraPosition; 			// FOR LIGHTING
in vec4 vPosition;						// FOR LIGHTING
in vec3 vNormal; 						// FOR LIGHTING
in vec2 final_texture_coodinates; 		//	FOR TEXTURE

out vec4 final_color;

void main()
{
	//make sure normal and light direction is normalised
	vec3 N = normalize(vNormal); 										// FOR LIGHTING
	vec3 L = normalize(lightDirection); 								// FOR LIGHTING
	
	float lambertTerm = max(0,min(1,dot(N,-L))); 						// FOR LIGHTING
	
	vec3 V = normalize(cameraPosition - vPosition.xyz); 				// FOR LIGHTING
	vec3 R = reflect( L, N ); // FOR LIGHTING
	// calculate specular term
	float specularTerm = pow( max( 0, dot( R, V ) ), specularPower ); 	// FOR LIGHTING
    
	vec3 ambient = ambientLight * Ka; 									// FOR LIGHTING
	vec3 diffuse = (diffuseLight * Kd * lambertTerm); 					// FOR LIGHTING
	vec3 specular = specularLight * Ks * specularTerm; 					// FOR LIGHTING
	//final_color = texture(diffuse_texture, final_texture_coodinates); // FOR TEXTURE
	final_color = vec4(ambient + diffuse + specular, 1.0); 				// FOR LIGHTING
}