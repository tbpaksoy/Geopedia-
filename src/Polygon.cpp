#ifndef POLYGON_CPP
#define POLYGON_CPP
#include "Polygon.h"
#include "drawable/Model.h"
#include <numeric>
#include <algorithm>
#include <cmath>
#include <glm/geometric.hpp>
#include <iostream>

namespace geo
{
    static bool IsLeft(glm::vec2 a0, glm::vec2 a1, glm::vec2 b)
    {
        return ((a1.x - a0.x) * (b.y - a0.y) - (b.x - a0.x) * (a1.y - a0.y)) > 0;
    }
    static float GetArea(glm::vec2 a, glm::vec2 b, glm::vec2 c)
    {
        return abs(0.5f * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)));
    }
    static bool IsPointInTriangle(glm::vec2 p, glm::vec2 a, glm::vec2 b, glm::vec2 c)
    {
        if (p == a || p == b || p == c)
            return false;
        float area = GetArea(a, b, c),
              area1 = GetArea(p, b, c),
              area2 = GetArea(a, p, c),
              area3 = GetArea(a, b, p);
        return abs(area - (area1 + area2 + area3)) < 1e-6;
    }
    static bool IsEar(Surface surface, int i, int j, int k)
    {
        int size = surface.size(),
            prev = i,
            current = j,
            next = k;
        glm::vec2 a = surface[prev],
                  b = surface[current],
                  c = surface[next];
        if (!IsLeft(a, b, c))
            return false;
        for (int l = 0; l < size; l++)
        {
            if (l == prev || l == current || l == next)
            {
                continue;
            }
            if (IsPointInTriangle(surface[l], a, b, c))
            {
                return false;
            }
        }

        return true;
    }
    static glm::vec2 FindIntersection(glm::vec2 a0, glm::vec2 a1, glm::vec2 b0, glm::vec2 b1)
    {
        float a0x = a0.x,
              a0y = a0.y,
              a1x = a1.x,
              a1y = a1.y,
              b0x = b0.x,
              b0y = b0.y,
              b1x = b1.x,
              b1y = b1.y;
        float denom = (a0x - a1x) * (b0y - b1y) - (a0y - a1y) * (b0x - b1x);
        float t = ((a0x - b0x) * (b0y - b1y) - (a0y - b0y) * (b0x - b1x)) / denom;
        return glm::vec2(a0x + t * (a1x - a0x), a0y + t * (a1y - a0y));
    }
    static bool Intersecting(Surface surfaceA, Surface surfaceB)
    {
        for (int i = 0; i < surfaceA.size(); i++)
        {
            glm::vec2 a0 = surfaceA[i],
                      a1 = surfaceA[(i + 1) % surfaceA.size()];
            for (int j = 0; j < surfaceB.size(); j++)
            {
                glm::vec2 b0 = surfaceB[j],
                          b1 = surfaceB[(j + 1) % surfaceB.size()];
                if (IsLeft(a0, a1, b0) != IsLeft(a0, a1, b1) && IsLeft(b0, b1, a0) != IsLeft(b0, b1, a1))
                {
                    return true;
                }
            }
        }
        return false;
    }
    static Surface Subtract(Surface a, Surface b)
    {
        Surface result = a;
        for (int i = 0; i < b.size(); i++)
        {
            Surface temp;
            glm::vec2 b0 = b[i],
                      b1 = b[(i + 1) % b.size()];
            for (int j = 0; j < result.size(); j++)
            {
                glm::vec2 a0 = result[j],
                          a1 = result[(j + 1) % result.size()];

                bool startIsLeft = IsLeft(b0, b1, a0),
                     endIsLeft = IsLeft(b0, b1, a1);

                if (startIsLeft && endIsLeft)
                    temp.push_back(a1);
                else if (startIsLeft && !endIsLeft)
                {
                    glm::vec2 intersection = FindIntersection(a0, a1, b0, b1);
                    if (!std::isnan(intersection.x) && !std::isnan(intersection.y))
                    {
                        temp.push_back(intersection);
                    }
                }
                else if (!startIsLeft && endIsLeft)
                {
                    glm::vec2 intersection = FindIntersection(a0, a1, b0, b1);
                    if (!std::isnan(intersection.x) && !std::isnan(intersection.y))
                    {
                        temp.push_back(intersection);
                    }
                    temp.push_back(a1);
                }
                result = temp;
            }
        }

        return result;
    }
    static unsigned int *Triangulate(Surface surface, int &size)
    {
        std::vector<unsigned int> indices;
        if (surface.size() < 3)
        {
            size = 0;
            return nullptr;
        }

        std::vector<unsigned int> remaining;
        for (int i = 0; i < surface.size(); i++)
        {
            remaining.push_back(i);
        }

        while (remaining.size() > 3)
        {
            bool earFound = false;
            for (int i = 0; i < remaining.size(); i++)
            {
                if (IsEar(surface, remaining[(i - 1 + remaining.size()) % remaining.size()], remaining[i], remaining[(i + 1) % remaining.size()]))
                {

                    earFound = true;

                    int size = remaining.size(),
                        prev = (i - 1 + size) % size,
                        current = i,
                        next = (i + 1) % size;

                    indices.push_back(remaining[prev]);
                    indices.push_back(remaining[current]);
                    indices.push_back(remaining[next]);

                    remaining.erase(remaining.begin() + current);
                    break;
                }
            }
            if (!earFound)
            {
                break;
            }
        }
        indices.push_back(remaining[0]);
        indices.push_back(remaining[1]);
        indices.push_back(remaining[2]);

        unsigned int *result = new unsigned int[indices.size()];
        for (int i = 0; i < indices.size(); i++)
            result[i] = indices[i];
        size = indices.size();
        return result;
    }
    static unsigned int *Triangulate(Surface surface, Holes holes, int &size)
    {
        return nullptr;
    }
    void Polygon::Data(float *&vertices, int &vSize, unsigned int *&indices, int &iSize)
    {
        iSize = vSize = 0;
        Surface surface = this->surface;
        Holes holes = this->holes;
        for (int i = 0; i < holes.size(); i++)
        {
            if (Intersecting(surface, holes[i]))
            {
                surface = Subtract(surface, holes[i]);
                holes.erase(holes.begin() + i);
                i--;
            }
        }
        Surface combined;
        combined.insert(combined.end(), surface.begin(), surface.end());
        for (Surface s : holes)
        {
            combined.insert(combined.end(), s.begin(), s.end());
        }
        vSize = combined.size() * 3;
        vertices = new float[vSize];
        for (int i = 0; i < combined.size(); i++)
        {
            vertices[i * 3] = combined[i].x;
            vertices[i * 3 + 1] = combined[i].y;
            vertices[i * 3 + 2] = 0.0f;
        }
        if (holes.size())
            indices = Triangulate(this->surface, holes, iSize);
        else
            indices = Triangulate(this->surface, iSize);
    }
    void Polygon::Order()
    {
        glm::vec2 center = std::accumulate(surface.begin(), surface.end(), glm::vec2(0, 0)) / (float)surface.size();
        std::sort(surface.begin(), surface.end(), [center](glm::vec2 a, glm::vec2 b)
                  { return atan2(a.y - center.y, a.x - center.x) < atan2(b.y - center.y, b.x - center.x); });
    }
    void Polygon::MakeSimple(double distance)
    {
        if (surface.size() <= 3)
            return;
        for (int i = 0; i < surface.size(); i++)
        {
            glm::vec2 current = surface[i];
            for (int j = i; j < surface.size(); j++)
            {
                glm::vec2 next = surface[(j + 1) % surface.size()];
                if (glm::distance(current, next) < distance)
                {
                    surface.erase(surface.begin() + j);
                    j--;
                }
            }
        }
    }
    void Polygon::Normalize(float right, float top, float left, float bottom)
    {
        /*         float minX = std::min(surface.begin(), surface.end(), [](glm::vec2 a, glm::vec2 b)
                                      { return a.x < b.x; })
                                 ->x,
                      minY = std::min(surface.begin(), surface.end(), [](glm::vec2 a, glm::vec2 b)
                                      { return a.y < b.y; })
                                 ->y,
                      maxX = std::max(surface.begin(), surface.end(), [](glm::vec2 a, glm::vec2 b)
                                      { return a.x < b.x; })
                                 ->x,
                      maxY = std::max(surface.begin(), surface.end(), [](glm::vec2 a, glm::vec2 b)
                                      { return a.y < b.y; })
                                 ->y;
                float width = maxX - minX,
                      height = maxY - minY;
                for (glm::vec2 &v : surface)
                {
                    v.x = (v.x - minX) / width * (right - left) + left;
                    v.y = (v.y - minY) / height * (top - bottom) + bottom;
                } */
    }
}
#endif