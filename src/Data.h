#ifndef DATA_H
#define DATA_H

#include <simdjson.h>
#include "Polygon.h"

simdjson::dom::element GetDocuments(const char *path, const char *cert);
GPPP::Polygon ExtractPolygon(simdjson::dom::element doc);

#endif