#ifndef DATA_CPP
#include <curl/curl.h>
#include <glm/glm.hpp>
#include <cstring>

#include "Data.h"
static simdjson::dom::parser parser;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size * nmemb;
    size_t oldLength = s->size();
    try
    {
        s->resize(oldLength + newLength);
    }
    catch (std::bad_alloc &e)
    {
        return 0;
    }

    std::copy((char *)contents, (char *)contents + newLength, s->begin() + oldLength);
    return size * nmemb;
}

simdjson::dom::element GetElement(const char *path, const char *cert)
{
    CURL *curl = curl_easy_init();
    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, path);
    curl_easy_setopt(curl, CURLOPT_CAINFO, cert);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Geopedia++/1.0");
    curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    simdjson::dom::element doc = parser.parse(response);

    return doc;
}
geo::Polygon ExtractPolygon(simdjson::dom::element doc)
{
    simdjson::dom::element polygon = doc["coordinates"];
    geo::Polygon poly;
    const char *type = doc["type"].get_c_str().value();

    std::cout << type << std::endl;

    if (std::strcmp(type, "Multipolygon") == 0 || std::strcmp(type, "Polygon") == 0)
    {
        std::cout << "ok" << std::endl;
        for (auto o : polygon.get_array().value())
        {
            for (auto p : o.get_array().value())
            {
                glm::vec2 point = glm::vec2(p.at(0).get_double().value(), p.at(1).get_double().value());
                poly.surface.push_back(point);
            }
        }
    }

    return poly;
}
#endif