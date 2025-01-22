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
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp)
{
  if (userp && contents)
  {
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
  }
  return 0;
}
int main()
{
  CURL *curl = curl_easy_init();

  if (!curl)
  {
    std::cout << "CURL initialization failed." << std::endl;
    return -1;
  }
  std::string response;
  std::string url = "https://nominatim.openstreetmap.org/search?q=Turkey&format=json&polygon_geojson=1";

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem");
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "Geopedia++/1.0");
  curl_easy_perform(curl);

  curl_easy_cleanup(curl);

  simdjson::dom::parser parser;
  simdjson::dom::element doc = parser.parse(response);
  std::cout << doc.at(0).at_key("place_id") << std::endl;
  return 0;
}