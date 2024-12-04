#include "imgui/imgui.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/Window.h"
#include "src/Shader.h"
#include "src/Camera.h"
#include "src/light/DirectLight.h"
#include "src/drawable/Model.h"

int main()
{

    Window *win = new Window("Geopedia++", 1280, 720);

    glDisable(GL_CULL_FACE);

    float *vertices = new float[27]{
        -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.45f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.1f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.75f, 0.75f};
    unsigned int *indices = new unsigned int[3]{0, 1, 2};

    Model *model = new Model(vertices, 27, indices, 3);
    Shader *meshShader = new Shader("shaders/mesh.vs", "shaders/mesh.fs");
    meshShader->Activate();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Camera *camera = new Camera();
    camera->SetPosition(glm::vec3(0, 0.5f, -3.0f));
    camera->SetUniforms(meshShader);

    ImGuiIO &io = ImGui::GetIO();

    ImFontGlyphRangesBuilder builder;
    ImVector<ImWchar> ranges;
    builder.AddText("qwertyuıopğüasdfghjklşizxcvbnmöçQWERTYUIOPĞÜASDFGHJKLŞİZXCVBNMÖÇ0123456789.,-+*/=()[]{}<>!@#$%^&*;:|\\\"'`~_? \t\n");
    builder.BuildRanges(&ranges);
    io.Fonts->AddFontFromFileTTF("fonts/unifont-15.1.05.otf", 16.0f, nullptr, ranges.Data);
    io.Fonts->Build();

    win->SetDefaultShaders({meshShader});

    win->SetUpdate([&]()
                   {
                       ImGui::Begin("Geopedia++");

                       ImGui::Text("Merhaba Dünya!");

                       ImGui::End();

                       model->Draw(meshShader);

                       camera->Rotate(glm::vec3(0, 0.1f, 0) * win->GetDeltaTime());
                       camera->SetUniforms(meshShader);
                       meshShader->Set("viewPos", camera->GetPosition()); });

    win->Run();

    delete win;

    return 0;
}