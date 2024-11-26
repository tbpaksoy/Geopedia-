#ifndef SHADER_CPP
#define SHADER_CPP
#include <GL/glew.h>
#include "Shader.h"
#include <fstream>

// En: Constructor and destructor
// Tr: Yapıcı ve yıkıcı fonksiyonlar

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode, fragmentCode;
    std::ifstream vertexFile, fragmentFile;

    vertexFile.open(vertexPath);
    for (std::string line; std::getline(vertexFile, line);)
        vertexCode += line + '\n';
    vertexFile.close();

    fragmentFile.open(fragmentPath);
    for (std::string line; std::getline(fragmentFile, line);)
        fragmentCode += line + '\n';
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