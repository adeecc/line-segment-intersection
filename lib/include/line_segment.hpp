#pragma once

#include <assert.h>

#include <ostream>
#include <point.hpp>
#include <utility>

namespace Geometry {

struct LineSegment {
    Point u, v;

    LineSegment() = default;

    LineSegment(Point _u, Point _v) : u(_u), v(_v) {}
    LineSegment(double ux, double uy, double vx, double vy) : u(ux, uy), v(vx, vy) {}

    Point& top() { return (u < v) ? u : v; }
    const Point& top() const { return (u < v) ? u : v; }

    Point& bottom() { return (u < v) ? v : u; }
    const Point& bottom() const { return (u < v) ? v : u; }

    Point& operator[](std::size_t idx) { return idx ? bottom() : top(); }
    const Point& operator[](std::size_t idx) const { return idx ? bottom() : top(); }

    friend std::ostream& operator<<(std::ostream& stream, const LineSegment& l) {
        stream << "[" << l.top() << "->" << l.bottom() << "]";
        return stream;
    }

    static bool does_intersect(const LineSegment& l1, const LineSegment& l2);

    static Point compute_intersection(const LineSegment& l1, const LineSegment& l2);
    static Point compute_intersection(const Point& u, const Point& v, double y);
    static Point compute_intersection(const LineSegment& l1, double y);
};
}  // namespace Geometry
