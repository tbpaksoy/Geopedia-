#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform float diffStrength;
uniform float lightRange;
uniform float ambientStrength;
uniform float lightIntensity;

void main()
{
    vec3 ambient = ambientStrength * lightColor * lightIntensity;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * diffStrength * lightIntensity;

    float dist = length(lightPos - FragPos);


    vec3 result;

    if(dist > lightRange)
    {
        result = ambient * Color;
    }
    else
    {
        result =  diffuse * Color;
    }

    FragColor = vec4(result, 1.0);
}