#ifndef MODEL_CPP
#define MODEL_CPP
#include "Model.h"
#include <numeric>
namespace geo
{
    Model::Model(float *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->vertexCount = vertexCount;
        this->indexCount = indexCount;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }
    Model::Model()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }
    Model::~Model()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    void Model::Draw(Shader *shader)
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        shader->Use();
    }
    void Model::Bind()
    {
        glBindVertexArray(VAO);
    }
    float *Model::GetVertexData(unsigned int &size) const
    {
        size = vertexCount;
        return vertices;
    }
    unsigned int *Model::GetIndexData(unsigned int &size) const
    {
        size = indexCount;
        return indices;
    }
    void Model::SetVertexData(float *vertices, unsigned int vertexCount)
    {
        this->vertices = vertices;
        this->vertexCount = vertexCount;

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
    }
    void Model::SetIndexData(unsigned int *indices, unsigned int indexCount)
    {
        this->indices = indices;
        this->indexCount = indexCount;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }

    void CombineModel(Model **models, unsigned int modelCount, Model *&result)
    {
        unsigned int vertexCount = std::accumulate(models, models + modelCount, 0, [](unsigned int acc, Model *model)
                                                   { return acc + model->vertexCount; });
        unsigned int indexCount = std::accumulate(models, models + modelCount, 0, [](unsigned int acc, Model *model)
                                                  { return acc + model->indexCount; });
        float *vertices = new float[vertexCount];
        unsigned int *indices = new unsigned int[indexCount];
        for (int i = 0, j = 0; i < modelCount; i++)
        {
            for (int k = 0; k < models[i]->vertexCount; k++)
            {
                vertices[j++] = models[i]->vertices[k];
            }
        }
        for (int i = 0, j = 0, max = 0; i < modelCount; i++, max = *std::max_element(indices, indices + indexCount))
        {
            for (int k = 0; k < models[i]->indexCount; k++)
            {
                indices[j++] = models[i]->indices[k] + max;
            }
        }

        result = new Model(vertices, vertexCount, indices, indexCount);
    }
    void CombineModel(Model **models, unsigned int modelCount, GLuint &vao, GLuint &vbo, GLuint &ebo)
    {
        unsigned int vertexCount = std::accumulate(models, models + modelCount, 0, [](unsigned int acc, Model *model)
                                                   { return acc + model->vertexCount; });
        unsigned int indexCount = std::accumulate(models, models + modelCount, 0, [](unsigned int acc, Model *model)
                                                  { return acc + model->indexCount; });
        float *vertices = new float[vertexCount];
        unsigned int *indices = new unsigned int[indexCount];
        for (int i = 0, j = 0; i < modelCount; i++)
        {
            for (int k = 0; k < models[i]->vertexCount; k++)
            {
                vertices[j++] = models[i]->vertices[k];
            }
        }
        for (int i = 0, j = 0, max = 0; i < modelCount; i++, max = *std::max_element(indices, indices + indexCount))
        {
            for (int k = 0; k < models[i]->indexCount; k++)
            {
                indices[j++] = models[i]->indices[k] + max;
            }
        }

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
        glBindVertexArray(vao);
    }
}
#endif