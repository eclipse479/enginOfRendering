#version 450 // Frag Shader

uniform sampler2D textureDiffuse; 				//FOR TEXTURE
uniform sampler2D textureSpecular;				//FOR TEXTURE
uniform sampler2D textureNormal;				//FOR TEXTURE

uniform vec3 lightDirection; 					//FOR LIGHTING
uniform vec3 ambientLight; 						//FOR LIGHTING
uniform vec3 diffuseLight; 						//FOR LIGHTING
uniform vec3 specularLight; 					//FOR LIGHTING

uniform vec3 lightDirectionSun; 				// FOR SECOND LIGHT	
uniform vec3 ambientLightSun; 					// FOR SECOND LIGHT	
uniform vec3 diffuseLightSun; 					// FOR SECOND LIGHT	
uniform vec3 specularLightSun; 					// FOR SECOND LIGHT	

uniform vec3 Ka; //ambient material colour		//FOR LIGHTING
uniform vec3 Kd; //diffuse material colour		//FOR LIGHTING
uniform vec3 Ks; //specular material colour		//FOR LIGHTING
uniform float specularPower = 1; 				//FOR LIGHTING

uniform vec3 cameraPosition; 					//FOR LIGHTING
in vec4 vPosition;								//FOR LIGHTING
in vec3 vNormal; 								//FOR LIGHTING
in vec2 final_texture_coodinates; 				//FOR TEXTURE

in vec3 vTangent;
in vec3 vBiTangent;

out vec4 final_color;

void main()
{
	//make sure normal and light direction is normalised
	vec3 N = normalize(vNormal); 	// FOR LIGHTING
	vec3 T = normalize(vTangent);	
	vec3 B = normalize(vBiTangent);
	vec3 L = normalize(lightDirection); 								// FOR LIGHTING
	vec3 sunL = normalize(lightDirectionSun); 	// FOR SECOND LIGHT
	
	mat3 TBN =  mat3(T,B,N);
	
	vec3 texDifuse = texture(textureDiffuse,final_texture_coodinates).rgb;
	vec3 texSpecular = texture(textureSpecular,final_texture_coodinates).rgb;
	vec3 texNormal = texture(textureNormal, final_texture_coodinates).rgb;
	
	N = TBN * ((texNormal * 2) - 1);

	
	float lambertTerm =    max(0,min(1,dot(N,-L))); 	// FOR LIGHTING
	float lambertTermSun = max(0,min(1,dot(N,-sunL)));	// FOR SECOND LIGHT
	
	vec3 V = normalize(cameraPosition - vPosition.xyz); 				// FOR LIGHTING
	vec3 R = reflect( L, N ); 											// FOR LIGHTING
	vec3 sunR = reflect(sunL,N);										// FOR SECOND LIGHT
				// calculate specular term
	float specularTerm = pow( max( 0, dot( R, V ) ), specularPower ); 	// FOR LIGHTING
	float specularTermSun = pow( max( 0, dot( sunR, V ) ), specularPower ); 	// FOR SECOND LIGHT
	
    vec4 textureColour = texture(textureDiffuse, final_texture_coodinates);
	vec3 colourToAdd = vec3 (textureColour.x,textureColour.y,textureColour.z);
	
	vec3 ambient = ambientLight * Ka * colourToAdd; 											// FOR LIGHTING
	vec3 diffuse = (diffuseLight * Kd * lambertTerm * colourToAdd); 							// FOR LIGHTING
	vec3 specular = specularLight * Ks * specularTerm; 											// FOR LIGHTING
	
	vec3 sunAmbient = ambientLightSun * Ka * colourToAdd; 										// FOR SECOND LIGHT
	vec3 sunDiffuse = (diffuseLightSun * Kd * lambertTermSun * colourToAdd); 					// FOR SECOND LIGHT
	vec3 sunSpecular = specularLightSun * Ks * specularTermSun; 								// FOR SECOND LIGHT
	
	
	final_color = vec4((ambient + diffuse + specular) + (sunAmbient + sunDiffuse + sunSpecular), 1.0); 				// FOR LIGHTING
}