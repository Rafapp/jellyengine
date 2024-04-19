#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;

void main()
{
   vec4 worldPosition = transform * vec4(aPos, 1.0);
   gl_Position = projection * view * worldPosition;
   FragPos = vec3(worldPosition);

   // Normal matrix
   Normal = mat3(transpose(inverse(transform))) * aNormal;
}