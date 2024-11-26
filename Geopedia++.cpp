#include "imgui/imgui.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/Window.h"
#include "src/Buffer.h"
#include "src/Shader.h"
#include "src/Camera.h"
#include "src/light/DirectLight.h"

int main()
{

    Window *win = new Window("Geopedia++", 1280, 720);

    glDisable(GL_CULL_FACE);

    Buffer *buffer = new Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    buffer->CreateVBO();
    buffer->CreateEBO();

    float *vertices = new float[27]{
        -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.45f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.1f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.75f, 0.75f};
    unsigned int *indices = new unsigned int[3]{0, 1, 2};

    buffer->SetVertexData(vertices, 27);
    buffer->SetIndexData(indices, 3);

    buffer->AddAttribute(3);
    buffer->AddAttribute(3);
    buffer->AddAttribute(3);

    buffer->ActivateAttributes();

    Shader *meshShader = new Shader("shaders/mesh.vs", "shaders/mesh.fs"),
           *lightShader = new Shader("shaders/lights/light.vs", "shaders/lights/pointLight.fs");

    Camera *camera = new Camera();
    camera->SetPosition(glm::vec3(0, 0.5f, -3.0f));
    camera->SetUniforms(meshShader);
    camera->SetUniforms(lightShader);
    lightShader->Use();
    lightShader->Set("lightSpaceMatrix", camera->GetOrthographicMatrix() * camera->GetViewMatrix());
    lightShader->Set("viewPos", camera->GetPosition());
    lightShader->Set("pointLight.position", glm::vec3(0));
    lightShader->Set("pointLight.ambient", glm::vec3(0.2f));
    lightShader->Set("pointLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    lightShader->Set("pointLight.range", 1.0f);
    lightShader->Set("pointLight.attenuation", 0.09f);

    win->SetDefaultShaders({meshShader, lightShader});

    win->SetUpdate([&]()
                   {
                       ImGui::Begin("Geopedia++");
                       ImGui::Text("Hello, world!");
                       bool change = false;
                       change |= ImGui::ColorEdit3("color A", &vertices[6]);
                       change |= ImGui::ColorEdit3("color B", &vertices[15]);
                       change |= ImGui::ColorEdit3("color C", &vertices[24]);
                       ImGui::End();

                       if (change)   
                       buffer->SetVertexData(vertices, 27);

                       camera->Rotate(glm::vec3(0, 0.1f, 0) * win->GetDeltaTime());
                       camera->SetUniforms(meshShader);
                       meshShader->Set("viewPos", camera->GetPosition()); });

    win->AddBuffer(buffer);

    win->Run();

    delete win;
}