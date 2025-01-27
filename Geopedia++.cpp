#include "imgui/imgui.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include <time.h>
#include <curl/curl.h>
#include <simdjson.h>

#include "src/Window.h"
#include "src/Shader.h"
#include "src/Camera.h"
#include "src/light/DirectLight.h"
#include "src/drawable/Model.h"
#include "src/Polygon.h"
#include "src/Data.h"

int main()
{
  geo::Window window("Geopedia++", 800, 600);
  std::string search, index;
  std::cin >> search;
  std::cout << std::endl;
  simdjson::dom::element e = GetElement(("https://nominatim.openstreetmap.org/search?q=" + search + "&format=json&polygon_geojson=1").c_str(), "cacert.pem");

  std::cin >> index;
  geo::Polygon p = ExtractPolygon(e.at(std::stoi(index))["geojson"]);
  p.MakeSimple(0.02);
  p.Normalize(1.0, 1.0, -1.0, -1.0);

  float *vertices;
  unsigned int *indices;
  int vSize, iSize;
  p.Data(vertices, vSize, indices, iSize, {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f});

  geo::Model model(vertices, vSize * 9, indices, iSize);
  geo::Shader shader("shaders/mesh.vs", "shaders/mesh.fs");
  shader.Activate();
  geo::Camera camera;
  camera.SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
  camera.SetOrthographic(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
  camera.SetUniforms(&shader, "model", "view", "projection", geo::CameraType::Orthographic);
  window.SetUpdate([&]()
                   { model.Draw(&shader); });
  window.Run();
  return 0;
}