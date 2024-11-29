#include <iostream>
#ifndef BUFFER_CPP
#define BUFFER_CPP
#include "Buffer.h"
#include <numeric>
Buffer::Buffer(GLenum type, GLenum usage)
{
    this->type = type;
    this->usage = usage;
    glGenVertexArrays(1, &vao);
    this->vertexData = nullptr;
    this->indexSize = 0;
    this->vbo = 0;
    this->ebo = 0;
}

Buffer::~Buffer()
{
}

// En: Returns the VAO
// Tr: VAO döndürür
GLuint Buffer::GetVAO() const
{
    return vao;
}

// En: Binds the VAO
// Tr: VAO'yu bağlar
void Buffer::Bind()
{
    glBindVertexArray(vao);
}

void Buffer::BindFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

// En: Generates and binds the VBO
// Tr: VBO oluşturur ve bağlar
void Buffer::CreateVBO()
{
    Bind();
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

// En: Generates and binds the EBO
// Tr: EBO oluşturur ve bağlar
void Buffer::CreateEBO()
{
    Bind();
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

// En: Generates and binds the FBO
// `colorAttachmentsCount` is the count of the color attachments.
// `width` is the width of the color attachments.
// `height` is the height of the color attachments.
// Tr: FBO oluşturur ve bağlar
// `colorAttachmentsCount` renk eklerinin sayısıdır.
// `width` renk eklerinin genişliğidir.
// `height` renk eklerinin yüksekliğidir.
void Buffer::CreateFBO(unsigned int colorAttachmentsCount, unsigned int width, unsigned int height)
{
    Bind();

    if (fbo)
        glDeleteFramebuffers(1, &fbo);

    if (colorAttachments)
        delete[] colorAttachments;

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    colorAttachmentSize = colorAttachmentsCount;
    colorAttachments = new GLuint[colorAttachmentsCount];

    glGenTextures(colorAttachmentsCount, colorAttachments);

    for (int i = 0; i < colorAttachmentsCount; i++)
    {
        glBindTexture(GL_TEXTURE_2D, colorAttachments[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F,
                     width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorAttachments[i], 0);
    }
}

// En: Links the VBO, if you attach external VBO.
// `vbo` is the external VBO.
// Tr: Eğer dışarıdan VBO eklemek isterseniz bağlar.
// `vbo` dışarıdan eklenen VBO'dur.
void Buffer::LinkVBO(GLuint vbo)
{
    this->vbo = vbo;
}

// En: Links the EBO, if you attach external EBO.
// `ebo` is the external EBO.
// Tr: Eğer dışarıdan EBO eklemek isterseniz bağlar.
// `ebo` dışarıdan eklenen EBO'dur.
void Buffer::LinkEBO(GLuint ebo)
{
    this->ebo = ebo;
}

// En : Draws accordintg to type of buffer.
// Tr : Buffer'ın tipine göre çizme işlemi yapar.
void Buffer::Draw()
{
    switch (type)
    {
    case GL_ELEMENT_ARRAY_BUFFER:
        DrawEBO();
        break;
    case GL_FRAMEBUFFER:
        // TODO: Implement this part after implementing the frame buffer.
        break;
    case GL_VERTEX_ARRAY:
        // TODO: Implement this part after implementing the vertex array.
        std::cout << "Not implemented yet!" << std::endl;
        break;
    default:
        std::cout << "Unknown type!" << glGetString(type) << std::endl;
        break;
    };
}

// En: Renders the buffer (elements wise).
// Tr: Buffer'ı renderlar (element bazlı).
void Buffer::DrawEBO()
{
    if (ebo && vbo && indexSize)
    {
        glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
    }
}

// En: Retuns true if the buffer has shader, else false.
// Tr: Buffer'ın shader'ı varsa true döndürür, yoksa false.
bool Buffer::HasShader() const
{
    return shaders != nullptr && shaders[0] != nullptr;
}

// En: Sets the shader of the buffer.
// `shader` is the shader to set.
// Tr: Buffer'ın shader'ını ayarlar.
// `shader` ayarlanacak shader.
void Buffer::SetShader(Shader *shader)
{
    this->shaders = new Shader *[1]{shader};
    this->shaderSize = 1;
}

// En: Sets the shaders of the buffer.
// `shaders` is the shaders to set.
// `size` is the size of the shaders.
// Tr: Buffer'ın shader'larını ayarlar.
// `shaders` ayarlanacak shaderlar.
// `size` shader sayısı.
void Buffer::SetShaders(Shader **shaders, unsigned int size)
{
    this->shaders = shaders;
    this->shaderSize = size;
}

// En: Uses the shader of the buffer.
// Tr: Buffer'ın shader'ını kullanır.
void Buffer::UseShader(unsigned int index)
{
    if (shaders && shaders[0])
    {
        shaders[index]->Use();
    }
}

// En: Returns the size of the buffer, this points the index size.
// Tr: Buffer'ın boyutunu döndürür, bu index boyutunu gösterir.
unsigned int Buffer::GetSize() const
{
    return indexSize;
}

// En: Returns the data of the buffer, vertex Data.
// Tr: Buffer'ın verisini döndürür, vertex verisi.
float *Buffer::GetData() const
{
    return vertexData;
}

// En: Sets the vertex data of the buffer.
// `data` is the vertex data to set.
// `size` is the size of the vertex data with all attributes.
// Tr: Buffer'ın vertex verisini ayarlar.
// `data` ayarlanacak vertex verisi.
// `size` tüm attribute'lar ile birlikte vertex verisinin boyutudur.
void Buffer::SetVertexData(float *data, unsigned int size)
{
    this->vertexSize = size;
    this->vertexData = data;
    Bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertexData, GL_STATIC_DRAW);
}

// En: Sets the index data of the buffer.
// `data` is the index data to set.
// `size` is the size of the index data.
// Tr: Buffer'ın index verisini ayarlar.
// `data` ayarlanacak index verisi.
// `size` index verisinin boyutudur.
void Buffer::SetIndexData(unsigned int *data, unsigned int size)
{
    this->indexSize = size;
    this->indexData = data;
    Bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), indexData, GL_STATIC_DRAW);
}

// En: Activates the attributes of the buffer.
// Tr: Buffer'ın attribute'larını etkinleştirir.
void Buffer::ActivateAttributes()
{
    unsigned int offset = 0;
    for (unsigned int i = 0; i < attributes.size(); i++)
    {
        Bind();
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE, stride, (void *)(offset * sizeof(float)));

        offset += attributes[i];
    }
}

// En: Adds an attribute to the buffer.
// `size` is the size of the attribute.
// Tr: Buffer'a bir attribute ekler.
// `size` attribute'ın boyutudur.
void Buffer::AddAttribute(unsigned int size)
{
    attributes.push_back(size);
    stride += size * sizeof(float);
}
#endif