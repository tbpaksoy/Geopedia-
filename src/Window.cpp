#include <iostream>
#ifndef WINDOW_CPP
#define WINDOW_CPP
#include "Window.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
namespace geo
{
    // En : Constructor and deconsructor.
    // Tr : Yapıcı ve yıkıcı fonksiyonlar.

    Window::Window(const char *title, unsigned int width, unsigned int height) : title(title), width(width), height(height)
    {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);

        glfwMakeContextCurrent(window);

        glewExperimental = GL_TRUE;
        glewInit();

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }
    Window::~Window()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
    }

    // En : Window functions
    // Tr : Pencere fonksiyonları

    // En : Gets the title of the window.
    // Tr : Pencerenin başlığını döndürür.
    const char *Window::GetTitle() const
    {
        return title;
    }
    // En : Gets the width of the window.
    // Tr : Pencerenin genişliğini döndürür.
    unsigned int Window::GetWidth() const
    {
        return width;
    }
    // En : Gets the height of the window.
    // Tr : Pencerenin yüksekliğini döndürür.
    unsigned int Window::GetHeight() const
    {
        return height;
    }
    // En : Gets the window.
    // Tr : Pencereyi döndürür.
    GLFWwindow *Window::GetWindow() const
    {
        return window;
    }
    // En : Gets the delta time.
    // Tr : Delta zamanı döndürür.
    float Window::GetDeltaTime() const
    {
        return deltaTime;
    }
    // En : Runs the window.
    // Tr : Pencereyi çalıştırır.
    void Window::Run()
    {

        style();

        float lastFrame = 0.0f, currentFrame = 0.0f;
        start();
        while (!glfwWindowShouldClose(window))
        {
            ImGui_ImplGlfw_NewFrame();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();

            currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            update();

            ImGui::Render();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwPollEvents();
            glfwSwapBuffers(window);

            glClear(GL_COLOR_BUFFER_BIT);
        }
    }

    // En : Render functions
    // Tr : Render fonksiyonları

    // En : Sets the update function.
    //  `update` : Update function.
    //  Tr : Güncelleme fonksiyonunu ayarlar.
    //  `update` : Güncelleme fonksiyonu.
    void Window::SetUpdate(std::function<void()> update)
    {
        if (update)
            this->update = update;
    }
    // En : Sets the start function.
    // `start` : Start function.
    // Tr : Başlangıç fonksiyonunu ayarlar.
    // `start` : Başlangıç fonksiyonu.
    void Window::SetStart(std::function<void()> start)
    {
        if (start)
            this->start = start;
    }
    // En : Sets the update function.
    // `update` : Update function.
    // Tr : Güncelleme fonksiyonunu ayarlar.
    // `update` : Güncelleme fonksiyonu.
    void Window::SetStyle(std::function<void()> style)
    {
        this->style = style;
    }
    // En : Sets the style function.
    // `style` : Style function.
    // Tr : Stil fonksiyonunu ayarlar.
    // `style` : Stil fonksiyonu.
    void Window::SetDefaultShaders(std::vector<Shader *> shaders)
    {
        defaultShaders = shaders;
    }
}
#endif