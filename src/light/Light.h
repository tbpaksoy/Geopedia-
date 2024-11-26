#ifndef LIGHT_H
#define LIGHT_H
#include "../Object.h"
#include "../Shader.h"

class Light : public Object
{
protected:
    glm::vec3 color;
    float intensity;

public:
    virtual unsigned int GetTypeIndex() const = 0;
    void SetColor(glm::vec3 color);
    void SetIntensity(float intensity);
    glm::vec3 GetColor() const;
    float GetIntensity() const;
    virtual void SetUniforms(Shader *shader, int index, const char *arrayName) = 0;
};

#endif