#version 330 core

out vec4 FragColor;


struct PointLight 
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 lightColor;

    float range;
    float attenuation;
};

in VS_OUT 
{
    vec3 FragPos;
    vec3 Normal;
    vec3 LightSpacePos;
} fs_in;

uniform PointLight pointLight;
uniform vec3 viewPos;

void main()
{
    float dist = length(pointLight.position - fs_in.FragPos);
    if(dist > pointLight.range)
        FragColor = pointLight.ambient;
    else
    {
        vec3 norm = normalize(fs_in.Normal);
        vec3 lightDir = normalize(pointLight.position - fs_in.FragPos);
        float dist = length(pointLight.position - fs_in.FragPos);
        float attenuation = pointLight.attenuation * dist / pointLight.range;
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 result = pointLight.lightColor * diff * attenuation + vec3(pointLight.ambient);
        FragColor = vec4(result, 1.0);
    }
}