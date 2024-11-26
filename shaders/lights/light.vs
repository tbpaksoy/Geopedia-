#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out VS_OUT 
{
    vec3 FragPos;
    vec3 Normal;
    vec3 LightSpacePos;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    vs_out.FragPos = vec3(model * vec4(position, 1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * normal;
    vs_out.LightSpacePos = vec3(lightSpaceMatrix * vec4(vs_out.FragPos, 1.0));

    gl_Position = projection * view * model * vec4(position, 1.0);
}