#pragma once

#include <limits>
#include <ostream>

namespace Geometry {

struct Point {
    double x, y;

    Point() : x(std::numeric_limits<int>::min()), y(std::numeric_limits<int>::min()) {}

    Point(double x, double y) : x(x), y(y) {}

    friend auto operator<=>(const Point& lhs, const Point& rhs) {
        if ((lhs.y > rhs.y) or (lhs.y == rhs.y and lhs.x < rhs.x))
            return -1;
        else if (lhs.x == rhs.x and lhs.y == rhs.y)
            return 0;
        else
            return 1;
    }

    friend bool operator==(const Point& lhs, const Point& rhs) {
        return lhs.x == rhs.x and lhs.y == rhs.y;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Point& pt) {
        stream << "(" << pt.x << ", " << pt.y << ")";
        return stream;
    }
};
}  // namespace Geometry
