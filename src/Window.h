#ifndef WINDOW_H
#define WINDOW_H

#include "Shader.h"
#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>

class Window
{
private:
    // En : Window properties
    // Tr : Pencere özellikleri

    GLFWwindow *window;
    unsigned int width, height;
    const char *title;
    std::function<void()> update;
    float deltaTime = 0.0f;

    // En : Render properties
    // Tr : Render özellikleri

    std::function<void()> style = []()
    {
        ImGui::StyleColorsClassic();
    };
    std::vector<Shader *> defaultShaders;

public:
    // En : Constructor and Destructor
    // Tr : Yapıcı ve Yıkıcı

    Window(const char *title, unsigned int width, unsigned int height);
    ~Window();

    // En : Window functions
    // Tr : Pencere fonksiyonları

    const char *GetTitle() const;
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    GLFWwindow *GetWindow() const;
    float GetDeltaTime() const;
    void Run();

    // En : Render functions
    // Tr : Render fonksiyonları

    void SetUpdate(std::function<void()> update);
    void SetStyle(std::function<void()> style);
    void SetDefaultShaders(std::vector<Shader *> shaders);
};

#endif