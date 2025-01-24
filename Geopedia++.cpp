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
  simdjson::dom::element e = GetElement("https://nominatim.openstreetmap.org/search?q=Ankara&format=json&polygon_geojson=1", "cacert.pem");
  std::cout << e.at(0)["place_id"].get_uint64().value() << std::endl;
  return 0;
}