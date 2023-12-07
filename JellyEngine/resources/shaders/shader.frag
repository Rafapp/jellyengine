#version 330 core
out vec4 FragColor;

uniform vec3 color;
uniform bool calculateLighting = false;

void main()
{
	if(calculateLighting){
		float ambient = 0.1;
		vec3 result = color * ambient;

		FragColor = vec4(result, 1.0);
	}
	else{
		FragColor = vec4(color, 1.0);
	}
}