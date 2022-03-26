#include <algorithm>
#include <iostream>
#include <line_segment.hpp>
#include <point.hpp>

namespace Geometry {

static inline double det(double a, double b, double c, double d) {
    // |a b|
    // |c d|
    return a * d - b * c;
}

inline int intersect1d(double l1, double r1, double l2, double r2) {
    if (l1 > r1) std::swap(l1, r1);
    if (l2 > r2) std::swap(l2, r2);

    return std::max(l1, l2) <= std::min(r1, r2) + LineSegment::EPS;
}

inline int vec(const Point& p, const Point& q, const Point& r) {
    double s = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);

    if (std::abs(s) < LineSegment::EPS) return 0;
    return s > 0 ? 1 : -1;
}

bool LineSegment::does_intersect(const LineSegment& l1, const LineSegment& l2) {
    return intersect1d(l1.u.x, l1.v.x, l2.u.x, l2.v.x) and
           intersect1d(l1.u.y, l1.v.y, l2.u.y, l2.v.y) and
           vec(l1.u, l1.v, l2.u) * vec(l1.u, l1.v, l2.v) <= 0 and
           vec(l2.u, l2.v, l1.u) * vec(l2.u, l2.v, l1.v) <= 0;
}

Point LineSegment::compute_intersection(const LineSegment& l1, const LineSegment& l2) {
    double a1 = l1.v.y - l1.u.y;
    double b1 = l1.u.x - l1.v.x;
    double c1 = -det(l1.u.x, l1.u.y, l1.v.x, l1.v.y);

    double a2 = l2.v.y - l2.u.y;
    double b2 = l2.u.x - l2.v.x;
    double c2 = -det(l2.u.x, l2.u.y, l2.v.x, l2.v.y);

    double dr = det(a1, b1, a2, b2);

    if (std::abs(dr) < LineSegment::EPS) {
        std::cout << "Assertion will fail @LineSegment::compute_intersection: " << l1 << " " << l2 << "\n";
    }

    assert(dr != 0);

    double x = det(b1, c1, b2, c2) / dr;
    double y = det(c1, a1, c2, a2) / dr;

    return {x, y};
}

Point LineSegment::compute_intersection(const Point& u, const Point& v, double y) {
    if (u.y == v.y)
        return u;

    double x = v.x + ((y - v.y) * (v.x - u.x) / (v.y - u.y));

    return {x, y};
}

Point LineSegment::compute_intersection(const LineSegment& l1, double y) {
    return LineSegment::compute_intersection(l1.u, l1.v, y);
}

}  // namespace Geometry