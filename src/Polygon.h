#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <glm/glm.hpp>
namespace geo
{
    class Model;
    typedef std::vector<glm::vec2> Surface;
    typedef std::vector<Surface> Holes;
    struct Polygon
    {
        Surface surface;
        Holes holes;
        void Order();
        void Data(float *&vertices, int &vSize, unsigned int *&indices, int &iSize);
        void MakeSimple(double distance);
        void Normalize(float right, float top, float left, float bottom);
    };
}
#endif
