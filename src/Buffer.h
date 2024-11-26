#ifndef BUFFER_H
#define BUFFER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>

#include "Shader.h"

class Buffer
{
private:
    // En: Related to Rendering
    // Tr: Renderlama ile ilgili

    GLuint vao, vbo, ebo, fbo;
    GLuint *colorAttachments = nullptr;
    GLenum type;
    GLenum usage;
    Shader *shader = nullptr;

    // En: Related to Data
    // Tr: Veri ile ilgili

    float *vertexData;
    unsigned int *indexData;
    unsigned int indexSize, vertexSize, colorAttachmentSize;

    // En: Related to internal data
    // Tr: Dahili veri ile ilgili

    unsigned int attributeSize = 0;
    unsigned int stride = 0;
    std::vector<unsigned int> attributes;

public:
    // En: Constructor and Destructor
    // Tr: Yapıcı ve Yıkıcı

    Buffer(GLenum type, GLenum usage);
    ~Buffer();

    // En: Related to Rendering
    // Tr: Renderlama ile ilgili

    GLuint GetVAO() const;
    void Bind();
    void CreateVBO();
    void CreateEBO();
    void CreateFBO(unsigned int colorAttachmentCount, unsigned int width, unsigned int height);
    void LinkVBO(GLuint vbo);
    void LinkEBO(GLuint ebo);
    void LinkFBO(GLuint fbo);
    void DrawElement();
    bool HasShader() const;
    void SetShader(Shader *shader);
    void UseShader();

    // En: Related to Data
    // Tr: Veri ile ilgili

    unsigned int GetSize() const;
    float *GetData() const;
    void SetVertexData(float *data, unsigned int size);
    void SetIndexData(unsigned int *data, unsigned int size);
    void ActivateAttributes();
    void AddAttribute(unsigned int size);
};

#endif