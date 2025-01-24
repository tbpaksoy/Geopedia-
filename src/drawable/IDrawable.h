#ifndef IDRAWABLE_H
#define IDRAWABLE_H
#include "../Shader.h"

namespace geo
{
    class IDrawable
    {
    public:
        virtual void Draw(geo::Shader *shader) {}
        virtual void Draw() {}
        virtual void Bind() {}
    };
}
#endif