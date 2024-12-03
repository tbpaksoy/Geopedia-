#ifndef IDRAWABLE_H
#define IDRAWABLE_H
#include "../Shader.h"
class IDrawable
{
public:
    virtual void Draw(Shader *shader) {}
    virtual void Draw() {}
    virtual void Bind() {}
};
#endif