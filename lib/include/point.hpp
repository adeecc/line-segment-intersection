#pragma once

#include <limits>
#include <ostream>

namespace Geometry {

struct Point {
    static constexpr double EPS = std::numeric_limits<float>::epsilon();
    double x, y;

    constexpr Point() : x(std::numeric_limits<int>::min()), y(std::numeric_limits<int>::min()) {}

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
        return std::abs(lhs.x - rhs.x) < Point::EPS and
               std::abs(lhs.y - rhs.y) < Point::EPS;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Point& pt) {
        stream << "(" << pt.x << ", " << pt.y << ")";
        return stream;
    }
};
}  // namespace Geometry
