#ifndef DATA_CPP
#include <curl/curl.h>

#include "Data.h"
static simdjson::dom::parser parser;

simdjson::dom::element GetDocuments(const char *path, const char *cert)
{
    CURL *curl = curl_easy_init();
    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, path);
    curl_easy_setopt(curl, CURLOPT_CAINFO, cert);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Geopedia++/1.0");
    curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    simdjson::dom::element doc = parser.parse(response);

    return doc;
}
GPPP::Polygon ExtractPolygon(simdjson::dom::element doc)
{
    simdjson::dom::element polygon = doc["geometry"]["coordinates"];
    GPPP::Polygon poly;
    const char *type = doc["type"].get_c_str().value();

    if (type == "MultiPolygon")
    {
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