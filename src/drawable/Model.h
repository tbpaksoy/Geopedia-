#ifndef MODEL_H
#define MODEL_H
#include "IDrawable.h"
#include <GL/glew.h>
class Model : public IDrawable
{
private:
    GLuint VAO, VBO, EBO;

protected:
    float *vertices;
    unsigned int *indices;
    unsigned int vertexCount;
    unsigned int indexCount;

public:
    Model(float *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);
    ~Model();
    void Draw(Shader *shader) override;
    float *GetVertexData(unsigned int &size) const override;
    unsigned int *GetIndexData(unsigned int &size) const override;
    void SetVertexData(float *vertices, unsigned int vertexCount);
    void SetIndexData(unsigned int *indices, unsigned int indexCount);

    friend void CombineModel(Model **models, unsigned int modelCount, Model *&result);
    friend void CombineModel(Model **models, unsigned int modelCount, GLuint &vao, GLuint &vbo, GLuint &ebo);
};
void CombineModel(Model **models, unsigned int modelCount, Model *&result);
void CombineModel(Model **models, unsigned int modelCount, GLuint &vao, GLuint &vbo, GLuint &ebo);
#endif