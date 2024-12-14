#include "imgui/imgui.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>

#include "src/Window.h"
#include "src/Shader.h"
#include "src/Camera.h"
#include "src/light/DirectLight.h"
#include "src/drawable/Model.h"
#include "src/Polygon.h"

int selected = 0;
const char **files = nullptr;
int fileCount = 0;
void FileDialog()
{
  ImGui::SetNextWindowSize(ImVec2(800, 600));
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::Begin("File Dialog", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
  if (files == nullptr)
  {
    std::vector<const char *> _files;
    for (auto entry : std::filesystem::directory_iterator("maps"))
    {
      char *path = new char[entry.path().string().size() + 1];
      strcpy(path, entry.path().string().c_str());
      _files.push_back(path);
    }
    files = new const char *[_files.size()];
    fileCount = _files.size();
    for (int i = 0; i < _files.size(); i++)
    {
      files[i] = _files[i];
    }
  }
  std::cout << fileCount << std::endl;
  std::cout << (files == nullptr) << std::endl;
  ImGui::ListBox("Files", &selected, files, fileCount);
  bool refresh = ImGui::Button("Refresh");
  if (refresh)
  {
    for (int i = 0; i < fileCount; i++)
    {
      delete[] files[i];
    }
    delete[] files;
    files = nullptr;
    fileCount = 0;
  }
  ImGui::End();
}

int main()
{
  std::cout << "test" << std::endl;
  Polygon poly = Polygon();
  poly.surface.push_back(glm::vec2(0, 0));
  poly.surface.push_back(glm::vec2(0, 1));
  poly.surface.push_back(glm::vec2(1, 1));
  poly.surface.push_back(glm::vec2(1, 0));
  poly.surface.push_back(glm::vec2(2, 0));
  poly.Order();

  float *pv = nullptr;
  unsigned int *pi = nullptr;
  int vSize, iSize;
  poly.Data(pv, vSize, pi, iSize);
  float *nv = new float[poly.surface.size() * 9];

  for (int i = 0, j = 0; i < poly.surface.size() * 9; i += 9, j += 3)
  {
    nv[i] = pv[j];
    nv[i + 1] = pv[j + 1];
    nv[i + 2] = pv[j + 2];

    nv[i + 3] = nv[i + 4] = nv[i + 5] = 1.0f;
    nv[i + 6] = nv[i + 7] = nv[i + 8] = 1.0f;
  }

  Window *fileWindow = new Window("Geopedia++", 800, 600);
  Camera *camera = new Camera();
  camera->SetPosition(glm::vec3(0, 0, -5));
  Model *model = new Model(nv, poly.surface.size() * 9, pi, iSize);
  Shader *shader = new Shader("shaders/mesh.vs", "shaders/mesh.fs");
  shader->Activate();
  camera->SetUniforms(shader);
  fileWindow->SetUpdate([&]()
                        { 
                          model->Draw(shader); 
                          camera->SetUniforms(shader); });
  fileWindow->Run();
  delete fileWindow;
}