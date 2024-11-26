#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader
{
private:
    GLuint program;

public:
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();
    void Use();
    void Set(const char *name, float value);
    void Set(const char *name, int value);
    void Set(const char *name, bool value);
    void Set(const char *name, glm::vec2 value);
    void Set(const char *name, glm::vec3 value);
    void Set(const char *name, glm::vec4 value);
    void Set(const char *name, glm::mat2 value);
    void Set(const char *name, glm::mat3 value);
    void Set(const char *name, glm::mat4 value);
};

#endif