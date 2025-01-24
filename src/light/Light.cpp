#ifndef LIGHT_CPP
#define LIGHT_CPP
#include "Light.h"
namespace geo
{
    void Light::SetColor(glm::vec3 color)
    {
        this->color = color;
    }
    void Light::SetIntensity(float intensity)
    {
        this->intensity = intensity;
    }
    glm::vec3 Light::GetColor() const
    {
        return color;
    }
    float Light::GetIntensity() const
    {
        return intensity;
    }
}
#endif