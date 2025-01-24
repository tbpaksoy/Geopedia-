#ifndef DIRECT_LIGHT_H
#define DIRECT_LIGHT_H
#include "Light.h"

namespace geo
{
    class DirectLight : public Light
    {
    private:
        glm::vec3 direction;

    public:
        DirectLight();
        DirectLight(glm::vec3 direction, glm::vec3 color, float intensity);
        ~DirectLight();
        unsigned int GetTypeIndex() const override;
        void SetDirection(glm::vec3 direction);
        glm::vec3 GetDirection() const;
        void SetUniforms(Shader *shader, int index, const char *arrayName) override;
    };
}
#endif