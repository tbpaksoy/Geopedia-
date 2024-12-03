#ifndef SHADER_CPP
#define SHADER_CPP
#include <GL/glew.h>
#include "Shader.h"
#include <fstream>
#include <iostream>
static std::map<std::string, GLint> attributesSizes =
    {
        {"float", 1},
        {"int", 1},
        {"bool", 1},
        {"vec2", 2},
        {"vec3", 3},
        {"vec4", 4},
        {"mat2", 4},
        {"mat3", 9},
        {"mat4", 16}};

// En: Constructor and destructor
// Tr: Yapıcı ve yıkıcı fonksiyonlar

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode, fragmentCode;
    std::ifstream vertexFile, fragmentFile;

    vertexFile.open(vertexPath);
    for (std::string line; std::getline(vertexFile, line);)
    {
        vertexCode += line + '\n';
        if (line.find("layout") != std::string::npos)
        {
            int begin = line.find("in") + 2, end = line.find(";", begin);
            for (auto it : attributesSizes)
            {
                if (line.find(it.first, begin) != std::string::npos)
                {
                    std::string name = line.substr(begin, end - begin);
                    while (name[0] == ' ')
                        name = name.substr(1);
                    while (name[name.size() - 1] == ' ')
                        name = name.substr(0, name.size() - 1);
                    GLint size = it.second;
                    name = name.substr(std::string(it.first).size() + 1);
                    attributes[name] = size;
                    break;
                }
            }
        }
    }

    vertexFile.close();

    fragmentFile.open(fragmentPath);
    for (std::string line; std::getline(fragmentFile, line);)
    {
        fragmentCode += line + '\n';
    }
    fragmentFile.close();

    const char *vertexSource = vertexCode.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    const char *fragmentSource = fragmentCode.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(program);
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::Activate()
{
    glUseProgram(program);
    unsigned int offset = 0, stride = 0;
    for (auto it : attributes)
    {
        stride += it.second;
    }
    for (auto it : attributes)
    {
        GLint loc = glGetAttribLocation(program, it.first.c_str());
        if (loc > -1)
        {
            glEnableVertexAttribArray(loc);
            glVertexAttribPointer(loc, it.second, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(offset * sizeof(float)));
        }
        offset += it.second;
        std::cout << offset << std::endl;
    }
}

// En: Use the shader
// Tr: Shader'ı kullan
void Shader::Use()
{
    glUseProgram(program);
}

// En: Set uniform variables
// `name` is the name of the uniform variable
// `value` is the value of the uniform variable
// Tr: Uniform değişkenlerini ayarla
// `name` uniform değişkenin adıdır
// `value` uniform değişkenin değeridir
void Shader::Set(const char *name, float value)
{
    glUniform1f(glGetUniformLocation(program, name), value);
}
// En: Set uniform variables
// `name` is the name of the uniform variable
// `value` is the value of the uniform variable
// Tr: Uniform değişkenlerini ayarla
// `name` uniform değişkenin adıdır
// `value` uniform değişkenin değeridir
void Shader::Set(const char *name, int value)
{
    glUniform1i(glGetUniformLocation(program, name), value);
}
// En: Set uniform variables
// `name` is the name of the uniform variable
// `value` is the value of the uniform variable
// Tr: Uniform değişkenlerini ayarla
// `name` uniform değişkenin adıdır
// `value` uniform değişkenin değeridir
void Shader::Set(const char *name, bool value)
{
    glUniform1i(glGetUniformLocation(program, name), value);
}
// En: Set uniform variables
// `name` is the name of the uniform variable
// `value` is the value of the uniform variable
// Tr: Uniform değişkenlerini ayarla
// `name` uniform değişkenin adıdır
// `value` uniform değişkenin değeridir
void Shader::Set(const char *name, glm::vec2 value)
{
    glUniform2fv(glGetUniformLocation(program, name), 1, &value[0]);
}
// En: Set uniform variables
// `name` is the name of the uniform variable
// `value` is the value of the uniform variable
// Tr: Uniform değişkenlerini ayarla
// `name` uniform değişkenin adıdır
// `value` uniform değişkenin değeridir
void Shader::Set(const char *name, glm::vec3 value)
{
    glUniform3fv(glGetUniformLocation(program, name), 1, &value[0]);
}
// En: Set uniform variables
// `name` is the name of the uniform variable
// `value` is the value of the uniform variable
// Tr: Uniform değişkenlerini ayarla
// `name` uniform değişkenin adıdır
// `value` uniform değişkenin değeridir
void Shader::Set(const char *name, glm::vec4 value)
{
    glUniform4fv(glGetUniformLocation(program, name), 1, &value[0]);
}
// En: Set uniform variables
// `name` is the name of the uniform variable
// `value` is the value of the uniform variable
// Tr: Uniform değişkenlerini ayarla
// `name` uniform değişkenin adıdır
// `value` uniform değişkenin değeridir
void Shader::Set(const char *name, glm::mat2 value)
{
    glUniformMatrix2fv(glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0]);
}
// En: Set uniform variables
// `name` is the name of the uniform variable
// `value` is the value of the uniform variable
// Tr: Uniform değişkenlerini ayarla
// `name` uniform değişkenin adıdır
// `value` uniform değişkenin değeridir
void Shader::Set(const char *name, glm::mat3 value)
{
    glUniformMatrix3fv(glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0]);
}
// En: Set uniform variables
// `name` is the name of the uniform variable
// `value` is the value of the uniform variable
// Tr: Uniform değişkenlerini ayarla
// `name` uniform değişkenin adıdır
// `value` uniform değişkenin değeridir
void Shader::Set(const char *name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0]);
}

#endif