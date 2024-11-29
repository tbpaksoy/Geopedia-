#ifndef IDRAWABLE_H
#define IDRAWABLE_H
#include "../Shader.h"
class IDrawable
{
public:
    virtual void Draw(Shader *shader) = 0;
    virtual float *GetVertexData(unsigned int &size) const = 0;
    virtual unsigned int *GetIndexData(unsigned int &size) const = 0;
};
#endif