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

void Shader::CheckProgramLinkErrors()
{
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cerr << "Error: Shader program failed to link\n"
                  << infoLog << std::endl;
    }
}
void Shader::CheckShaderCompileErrors(GLuint shader)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "Error: Shader failed to compile\n"
                  << infoLog << std::endl;
    }
}

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
            int begin = line.find("=") + 1, end = line.find(")");
            std::string attribute = line.substr(begin, end - begin);
            while (attribute.find(" ") != std::string::npos)
            {
                attribute.erase(attribute.find(" "), 1);
            }
            GLint loc = std::stoi(attribute);
            for (auto it : attributesSizes)
            {
                if (line.find(it.first) != std::string::npos)
                {
                    attributes[loc] = it.second;
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

    CheckShaderCompileErrors(vertexShader);

    const char *fragmentSource = fragmentCode.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    CheckShaderCompileErrors(fragmentShader);

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    CheckProgramLinkErrors();

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
    int max = 0;
    for (auto it : attributes)
    {
        stride += it.second;
        max = std::max(max, it.first);
    }
    for (int i = 0; i <= max; i++)
    {
        if (attributes.find(i) != attributes.end())
        {
            std::cout << i << std::endl;
            glEnableVertexAttribArray(i);
            GLenum error = glGetError();
            if (error != GL_NO_ERROR)
            {
                std::cerr << "Error: " << error << std::endl;
            }
            glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(offset * sizeof(float)));
            error = glGetError();
            if (error != GL_NO_ERROR)
            {
                std::cerr << "Error: " << error << std::endl;
            }
            offset += attributes[i];
        }
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