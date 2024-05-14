#version 460 core
out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform vec3 color;
uniform bool calculateLighting = true;

in vec3 Normal;
in vec3 FragPos;

float scatter = 2.5;
float specularStrength = .125;
float power = 128;

void main()
{
	if(calculateLighting){
		float ambient = 0.1;

		// Light and viewing inputs
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPos - FragPos);
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 lightReflect = reflect(-lightDir, norm);

		// Scattering approximation of Oren-Nayar lighting model (Credits: GPU Gems, 16.2)
		float scatter_diffuse = max(0, (dot(norm, lightDir) + scatter) / (1 + scatter));
		
		// Specular component
		float spec = pow(max(dot(viewDir, lightReflect), 0.0), 32);
		vec3 specular = spec * specularStrength * vec3(1.0, 1.0, 1.0); // Assume white light color

		vec3 result = color * (ambient + scatter_diffuse) + specular;
		FragColor = vec4(result, 0.75); // Set transparency of model here
	}
	else{
		FragColor = vec4(color, 1.0);
	}
}