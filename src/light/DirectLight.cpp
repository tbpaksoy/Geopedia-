#ifndef DIRECT_LIGHT_CPP
#define DIRECT_LIGHT_CPP

#include <string>

#include "DirectLight.h"

namespace geo
{
    DirectLight::DirectLight()
    {
        direction = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    DirectLight::DirectLight(glm::vec3 direction, glm::vec3 color, float intensity)
    {
        this->direction = direction;
    }
    DirectLight::~DirectLight()
    {
    }
    unsigned int DirectLight::GetTypeIndex() const
    {
        return 1;
    }
    void DirectLight::SetDirection(glm::vec3 direction)
    {
        this->direction = direction;
    }
    glm::vec3 DirectLight::GetDirection() const
    {
        return direction;
    }
    void DirectLight::SetUniforms(Shader *shader, int index, const char *arrayName)
    {
        std::string str(arrayName);
        str += "[" + std::to_string(index) + "]";
        shader->Set((str + ".direction").c_str(), direction);
        shader->Set((str + ".color").c_str(), color);
        shader->Set((str + ".intensity").c_str(), intensity);
    }
}
#endif