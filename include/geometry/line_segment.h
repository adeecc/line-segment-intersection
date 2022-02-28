#pragma once

#include <geometry/point.h>

namespace Geometry {

template <typename T>
struct LineSegment {
    Point<T> end_0, end_1;
};
}  // namespace Geometry
