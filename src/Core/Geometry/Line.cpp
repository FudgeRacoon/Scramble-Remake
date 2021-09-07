#include "Core/Geometry/Line.hpp"
using namespace Scramble;

Line::Line(Vector3 start, Vector3 end)
    :start(start), end(end) {}
Line::Line(float x0, float y0, float x1, float y1)
    :start(Vector3(x0, y0, 0.0)), end(Vector3(x1, y1, 0.0)) {}