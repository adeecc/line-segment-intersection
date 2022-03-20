#pragma once

#include <assert.h>

#include <ostream>
#include <point.hpp>
#include <utility>

namespace Geometry {

struct LineSegment {
    Point u, v;

    LineSegment() = default;

    // TODO: Remove this quirk. It breaks when u and v are reassigned
    LineSegment(Point _u, Point _v) : u(_u), v(_v) {
        if (u > v) {
            std::swap(u, v);
        }
    }

    LineSegment(double ux, double uy, double vx, double vy) : u(ux, uy), v(vx, vy) {
        if (u > v) {
            std::swap(u, v);
        }
    }

    Point& operator[](std::size_t idx) { return idx ? v : u; }
    const Point& operator[](std::size_t idx) const { return idx ? v : u; }

    friend std::ostream& operator<<(std::ostream& stream, const LineSegment& l) {
        stream << "[" << l.u << " " << l.v << "]";
        return stream;
    }

    static bool does_intersect(const LineSegment& l1, const LineSegment& l2);

    static Point compute_intersection(const LineSegment& l1, const LineSegment& l2);
    static Point compute_intersection(const Point& u, const Point& v, double y);
    static Point compute_intersection(const LineSegment& l1, double y);
};
}  // namespace Geometry
