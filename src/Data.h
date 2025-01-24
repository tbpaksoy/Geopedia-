#ifndef DATA_H
#define DATA_H

#include <simdjson.h>
#include "Polygon.h"

simdjson::dom::element GetElement(const char *path, const char *cert);
geo::Polygon ExtractPolygon(simdjson::dom::element doc);

#endif