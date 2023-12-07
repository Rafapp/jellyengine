#version 330 core
out vec4 FragColor;

uniform vec3 lightPos;

uniform vec3 color;
uniform bool calculateLighting = false;

in vec3 Normal;
in vec3 FragPos;

void main()
{
	if(calculateLighting){
		float ambient = 0.1;
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0); // Diffuse shading
		vec3 result = color * (ambient + diff);
		FragColor = vec4(result, 0.5);
	}
	else{
		FragColor = vec4(color, 1.0);
	}
}